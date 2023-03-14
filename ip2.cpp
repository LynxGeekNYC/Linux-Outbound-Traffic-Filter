#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

int main()
{
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return 1;
    }

    // Create a socket
    SOCKET outboundSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (outboundSocket == INVALID_SOCKET) {
        std::cout << "Error creating socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Connect to the remote server
    sockaddr_in remoteAddress;
    remoteAddress.sin_family = AF_INET;
    remoteAddress.sin_addr.s_addr = inet_addr("192.168.1.1");
    remoteAddress.sin_port = htons(80);
    iResult = connect(outboundSocket, (sockaddr*)&remoteAddress, sizeof(remoteAddress));
    if (iResult == SOCKET_ERROR) {
        std::cout << "Connect failed: " << WSAGetLastError() << std::endl;
        closesocket(outboundSocket);
        WSACleanup();
        return 1;
    }

    // Obtain the IP address of the remote server
    char ipAddress[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &remoteAddress.sin_addr, ipAddress, INET_ADDRSTRLEN);
    std::cout << "Connection established with IP address: " << ipAddress << std::endl;

    // Cleanup
    closesocket(outboundSocket);
    WSACleanup();

    return 0;
}
