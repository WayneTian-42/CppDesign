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
        /* WORD w_req = MAKEWORD(2, 2);  //�汾��
        WSADATA wsadata;
        int err;
        err = WSAStartup(w_req, &wsadata);
        if (err != 0)
        {
            std::cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << std::endl;
        }
        else
        {
            std::cout << "��ʼ���׽��ֿ�ɹ���" << std::endl;
        }
        //���汾��
        if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
        {
            std::cout << "�׽��ֿ�汾�Ų�����" << std::endl;
            // WSACleanup();
        }
        else
        {
            std::cout << "�׽��ֿ�汾��ȷ��" << std::endl;
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
    int sendLength, recvLength;
    const int PORT = 8888;
};

class Client
{
  public:
    Client() : serverSock(INVALID_SOCKET)
    {
        /* WORD w_req = MAKEWORD(2, 2);  //�汾��
        WSADATA wsadata;
        int err;
        err = WSAStartup(w_req, &wsadata);
        if (err != 0)
        {
            std::cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << std::endl;
        }
        else
        {
            std::cout << "��ʼ���׽��ֿ�ɹ���" << std::endl;
        }
        //���汾��
        if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2)
        {
            std::cout << "�׽��ֿ�汾�Ų�����" << std::endl;
            // WSACleanup();
        }
        else
        {
            std::cout << "�׽��ֿ�汾��ȷ��" << std::endl;
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
            std::cout << "���벻�Ϸ�������������\n";
            std::cin >> x;
            continue;
        }
    };

  private:
    SOCKET serverSock;
    SOCKADDR_IN serverAddr;
    int sendLength, recvLength;
    const int PORT = 8888;
};
