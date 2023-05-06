#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    // Server details
    string ip = "127.0.0.1";
    int port = 8080;

    // Prepare the sockaddr_in structure
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_port = htons(port);

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        cerr << "Connection failed" << endl;
        return 1;
    }

    cout << "connected to server" << endl;
    std::string message = "I HAVE CONNECTED";

    // welcome message to server
    if (send(sock, message.c_str(), message.length(), 0) < 0) {
        cerr << "Send failed" << endl;
        return 1;
    }

    char buffer[1024];
    if (recv(sock, buffer, sizeof(buffer), 0) < 0) {
        cerr << "receive failed" << endl;
        return 1;
    }
    cout << "data received from server: " << buffer << endl;
 
    // Close the socket
    close(sock);

    return 0;
}
