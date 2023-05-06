#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define RECV_ERROR -1
#define SOCKET_CLOSED 0

int connect_to_server(std::string IP, int port) {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Prepare the sockaddr_in structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP.c_str());
    server.sin_port = htons(port);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }
    return sock;
}

/**
 * Example method of converting different data types
 * into bytes we can send down a socket
*/
int send_net_msg(int socket) {
    int num = 1234;
    char buffer[sizeof(num)];
    std::memcpy(buffer, &num, sizeof(num));
    return send(socket, buffer, sizeof(buffer), 0);
}

/**
 * Minimal example of a client connecting, sending some data, 
 * receiving some data and disconnecting.
*/
int minimal_client_conn(int socket) {

    std::cout << "connected to server" << std::endl;

    // send welcome message
    if (send_net_msg(socket) < 0) {
        std::cerr << "Send failed" << std::endl;
        return 1;
    }

    // receive some data
    char buffer[1024];
    int status = recv(socket, buffer, sizeof(buffer), 0);
    switch (status) {
        case SOCKET_CLOSED: // closed
            std::cerr << "server closed socket" << std::endl;
            return SOCKET_CLOSED;

        case RECV_ERROR: //error
            std::cerr << "receive failed" << std::endl;
            return RECV_ERROR;
    }

    std::cout << "data received from server: " << buffer << std::endl;
 
    // Close the socket
    close(socket);
    return 0;
}

int main() {
    int port = 8080;
    std::string pi_ip = "192.168.0.41";
    std::string localhost = "127.0.0.1";
    int socket = connect_to_server(localhost, port);
    if (socket >= 0) {
        int status = minimal_client_conn(socket);
    }
}
