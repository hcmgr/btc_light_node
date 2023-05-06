#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

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
        return 1;
    }
    return sock;
}

/**
 * Minimal example of a client connecting, sending some data, 
 * receiving some data and disconnecting.
*/
int minimal_client_conn(int socket) {

    std::cout << "connected to server" << std::endl;
    std::string message = "I HAVE CONNECTED";

    // welcome message to server
    if (send(socket, message.c_str(), strlen(message.c_str()), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
        return 1;
    }

    char buffer[1024];
    if (recv(socket, buffer, sizeof(buffer), 0) < 0) {
        std::cerr << "receive failed" << std::endl;
        return 1;
    }
    std::cout << "data received from server: " << buffer << std::endl;
 
    // Close the socket
    close(socket);
    return 0;
}

int main() {
    int port = 8080;
    std::string ip = "192.168.0.41";
    int socket = connect_to_server(ip, port);
    int status = minimal_client_conn(socket);
}