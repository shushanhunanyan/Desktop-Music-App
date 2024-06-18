#include <iostream>
#include <set>
#include <thread>
#include <mutex>
#include <string>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

std::set<int> clients;
std::mutex clients_mutex;

void broadcastMessage(const std::string &message, int sender) {
    std::lock_guard<std::mutex> lock(clients_mutex);
    for (int client : clients) {
        if (client != sender) {
            send(client, message.c_str(), message.size(), 0);
        }
    }
}

void handleClient(int clientSocket) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            std::lock_guard<std::mutex> lock(clients_mutex);
            clients.erase(clientSocket);
            close(clientSocket);
            return;
        }
       //  std::string message = "Friend " + std::to_string(clientSocket) + ": " + buffer;
        std::string message = "Friend: " + std::string(buffer);;
	broadcastMessage(message, clientSocket);
    }
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(8080);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to bind socket" << std::endl;
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Failed to listen on socket" << std::endl;
        return 1;
    }

    std::cout << "Server listening on port 8080" << std::endl;

    while (true) {
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == -1) {
            std::cerr << "Failed to accept client" << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> lock(clients_mutex);
        clients.insert(clientSocket);

        std::thread(handleClient, clientSocket).detach();
    }

    close(serverSocket);
    return 0;
}

