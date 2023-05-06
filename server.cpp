#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>

int open_socket(int port, int max_conns) {
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "socket creation error" << std::endl;
        return -1;
    }

    // Set socket options to allow reuse of address and port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cout << "setsockopt error" << std::endl;
        return -1;
    }

    // Set server address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "bind error" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, max_conns) < 0) {
        std::cout << "listen error" << std::endl;
        return -1;
    }
    return server_fd;
}

void handle_connections(int server_fd) {
    int new_socket;
    int status;
    char buffer[1024];

    while (true) {
        if ((new_socket = accept(server_fd, 0, 0)) < 0) {
            std::cout << "accept error" << std::endl;
            continue;
        }
        std::cout << "client connected" << std::endl;

        int num_bytes = recv(new_socket, buffer, sizeof(buffer), 0);
        int num;
        std::memcpy(&num, buffer, sizeof(int));
        std::cout << "received: " << num << std::endl;

        // close(new_socket); // non-persistent
    }
}

int main() {
    int max_conns = 1;
    int servFd = open_socket(8080, max_conns);
    if (servFd >= 0) {
        handle_connections(servFd);
    }
}
