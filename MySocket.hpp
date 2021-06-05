#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>

// #    define PORT 300

class Server
{
  public:
    Server()
    {
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  //
        {
            std::cout << "Failed. Error Code : " << WSAGetLastError();
            return;
        }
    }
    ~Server()
    {
        closesocket(sock);
        WSACleanup();
    }
    bool serverInit();
    bool sendMessage(std::string &message);
    bool recvMessage(std::string &buff);

  private:
    SOCKET sock, acceptSock;
    SOCKADDR_IN serverAddr, acceptAddr;
    int sendLength, recvLength;
    const int PORT = 3080;
};

class Client
{
  public:
    Client()
    {
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)  //
        {
            std::cout << "Failed. Error Code : " << WSAGetLastError();
            return;
        }
    }
    ~Client()
    {
        closesocket(serverSock);
        WSACleanup();
    }
    bool clientInit();
    bool sendMessage(std::string &message);
    bool recvMessage(std::string &buff);

  private:
    SOCKET serverSock;
    SOCKADDR_IN serverAddr;
    int sendLength, recvLength;
    const int PORT = 3080;
};
