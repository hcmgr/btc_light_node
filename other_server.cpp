#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080
#define MAX_CONNECTIONS 5

int main() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "Socket creation error" << std::endl;
        return -1;
    }

    // Set socket options to allow reuse of address and port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        std::cout << "Setsockopt error" << std::endl;
        return -1;
    }

    // Set server address and port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cout << "Bind error" << std::endl;
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        std::cout << "Listen error" << std::endl;
        return -1;
    }

    // Accept incoming connections and send message back to client
    while (true) {
        if ((new_socket = accept(server_fd, 0, 0)) < 0) {
            std::cout << "Accept error" << std::endl;
            continue;
        }

        valread = read(new_socket, buffer, 1024);
        std::cout << "Message received from client: " << buffer << std::endl;

        std::string msg = "hello";
        send(new_socket, msg.c_str(), msg.length(), 0);
        std::cout << "Message sent to client" << std::endl;

        close(new_socket);
    }

    return 0;
}

