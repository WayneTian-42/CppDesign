#include "MySocket.hpp"
#include <vector>

bool Server::serverInit()
{
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
        return 0;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(sock, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        return 0;
    }
    else
        printf("...OK!\n");
    if (listen(sock, SOMAXCONN) < 0)
    {
        std::cout << "监听失败\n";
        WSACleanup();
        return 0;
    }
    std::cout << "监听连接中...\n";

    int addrLen = sizeof(sockaddr);
    acceptSock = accept(sock, (SOCKADDR *)&acceptAddr, &addrLen);
    if (acceptSock == SOCKET_ERROR)
    {
        std::cout << "连接失败！\n";
        WSACleanup();
        return 0;
    }
    std::cout << "连接建立，准备接受数据\n";
    return 1;
}
bool Server::sendMessage(std::string &message)
{
    std::vector<char> buff;
    buff.assign(message.cbegin(), message.cend());
    sendLength = recv(acceptSock, &buff[0], buff.size(), 0);
    if (sendLength < 0)
    {
        std::cout << "发送失败！\n";
        return false;
    }
    message.clear();
    return true;
}
bool Server::recvMessage(std::string &buff)
{
    buff.clear();
    std::vector<char> buffer(1024);
    recvLength = recv(acceptSock, &buffer[0], buffer.size(), 0);
    if (recvLength < 0)
    {
        std::cout << "接收失败\n";
        return 0;
    }
    else
        buff.append(buffer.cbegin(), buffer.cend());
    return 1;
}

bool Client::clientInit()
{
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //通过ipconfig/all查询
    serverAddr.sin_port = htons(PORT);

    if ((serverSock = socket(PF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
        return false;
    }

    if (connect(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr)))
    {
        printf("Connect failed:%d", WSAGetLastError());
        return false;
    }

    return true;
}

bool Client::sendMessage(std::string &message)
{
    std::vector<char> buff;
    buff.assign(message.cbegin(), message.cend());
    sendLength = recv(serverSock, &buff[0], buff.size(), 0);
    if (sendLength < 0)
    {
        std::cout << "发送失败！\n";
        return false;
    }
    message.clear();
    return true;
}
bool Client::recvMessage(std::string &buff)
{
    buff.clear();
    std::vector<char> buffer(1024);
    recvLength = recv(serverSock, &buffer[0], buffer.size(), 0);
    if (recvLength < 0)
    {
        std::cout << "接收失败\n";
        return 0;
    }
    else
        buff.append(buffer.cbegin(), buffer.cend());
    return 1;
}