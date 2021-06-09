#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <sstream>

// #    define PORT 300

class Server
{
  public:
    Server() : serverSock(INVALID_SOCKET), acceptSock(INVALID_SOCKET)
    {
        /* WORD w_req = MAKEWORD(2, 2);  //版本号
        WSADATA wsadata;
        int err;
        err = WSAStartup(w_req, &wsadata);
        if (err != 0)
        {
            std::cout << "初始化套接字库失败！" << std::endl;
        }
        else
        {
            std::cout << "初始化套接字库成功！" << std::endl;
        }
        //检测版本号
        if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
        {
            std::cout << "套接字库版本号不符！" << std::endl;
            // WSACleanup();
        }
        else
        {
            std::cout << "套接字库版本正确！" << std::endl;
        } */
    }
    ~Server()
    {
        closesocket(serverSock);
        closesocket(acceptSock);
        // WSACleanup();
    }
    bool serverInit();
    bool sendMessage(std::stringstream &message);
    bool recvMessage(std::string &buff);
    // int recvMessage();

  private:
    SOCKET serverSock, acceptSock;
    SOCKADDR_IN serverAddr, acceptAddr;
    std::stringstream error;
    int sendLength, recvLength;
    const int PORT = 8889;
};

class Client
{
  public:
    Client() : serverSock(INVALID_SOCKET)
    {
        /* WORD w_req = MAKEWORD(2, 2);  //版本号
        WSADATA wsadata;
        int err;
        err = WSAStartup(w_req, &wsadata);
        if (err != 0)
        {
            std::cout << "初始化套接字库失败！" << std::endl;
        }
        else
        {
            std::cout << "初始化套接字库成功！" << std::endl;
        }
        //检测版本号
        if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
        {
            std::cout << "套接字库版本号不符！" << std::endl;
            // WSACleanup();
        }
        else
        {
            std::cout << "套接字库版本正确！" << std::endl;
        } */
    }
    ~Client()
    {
        closesocket(serverSock);
        // WSACleanup();
    }
    bool clientInit();
    bool sendMessage(std::string &message);
    // void sendMessage(const int num);
    bool recvMessage(std::string &buff);

    template <typename T> void input(T &x)
    {
        std::cin >> x;

        while (std::cin.fail() || std::cin.get() != '\n')
        {
            std::cin.clear();
            std::cin.ignore(LLONG_MAX, '\n');
            std::cout << "输入不合法，请输入数字\n";
            std::cin >> x;
            continue;
        }
    };

  private:
    SOCKET serverSock;
    SOCKADDR_IN serverAddr;
    std::stringstream error;
    int sendLength, recvLength;
    const int PORT = 8889;
};