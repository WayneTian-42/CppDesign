#include "MySocket.hpp"
#include <string.h>
#include <vector>

bool Server::serverInit()
{
    WORD w_req = MAKEWORD(2, 2);  //�汾��
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
    }
    if ((serverSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
        return 0;
    }
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
        return 0;
    }
    else
        printf("...OK!\n");
    if (listen(serverSock, SOMAXCONN) < 0)
    {
        std::cout << "����ʧ��\n";
        // WSACleanup();
        return 0;
    }
    std::cout << "����������...\n";

    int addrLen = sizeof(SOCKADDR);
    acceptSock = accept(serverSock, (SOCKADDR *)&acceptAddr, &addrLen);
    if (acceptSock == SOCKET_ERROR)
    {
        std::cout << "����ʧ�ܣ�\n";
        // WSACleanup();
        return 0;
    }
    std::cout << "���ӽ�����׼����������\n";
    return 1;
}
bool Server::sendMessage(std::stringstream &output)
{
    /* std::string message;
    std::vector<char> buff;
    buff.assign(message.cbegin(), message.cend()); */
    char buff[1024] = {0};
    output >> buff;
    std::cout << output.str();
    sendLength = send(acceptSock, output.str().c_str(), output.str().size(), 0);
    if (sendLength < 0)
    {
        std::cout << "����ʧ��" << WSAGetLastError() << std::endl;
        return false;
    }
    output.clear();
    return true;
}
bool Server::recvMessage(std::string &buff)
{
    buff.clear();
    char buffer[1024];
    recvLength = recv(acceptSock, buffer, sizeof(buffer), 0);
    if (recvLength < 0)
    {
        std::cout << "����ʧ��" << WSAGetLastError() << std::endl;
        return 0;
    }
    else
        buff.append(buffer[0], buffer[strlen(buffer) - 1]);
    return 1;
}
int Server::recvMessage()
{
    int num;
    char buffer[1024];
    recvLength = recv(acceptSock, buffer, sizeof(buffer), 0);
    if (recvLength < 0)
    {
        std::cout << "����ʧ��" << WSAGetLastError() << std::endl;
        return INT_MIN;
    }
    else
        memcpy(&num, buffer, sizeof(num));
    return ntohl(num);
}

bool Client::clientInit()
{
    WORD w_req = MAKEWORD(2, 2);  //�汾��
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
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //ͨ��ipconfig/all��ѯ
    serverAddr.sin_port = htons(PORT);

    if ((serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
        return false;
    }
    err = connect(serverSock, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
    if (err == SOCKET_ERROR)
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
    sendLength = send(serverSock, &buff[0], buff.size(), 0);
    if (sendLength < 0)
    {
        std::cout << "����ʧ��" << WSAGetLastError() << std::endl;
        return false;
    }
    message.clear();
    return true;
}
void Client::sendMessage(const int num)
{
    std::vector<char> buff;
    buff.push_back(htonl(num));
    sendLength = send(serverSock, &buff[0], buff.size(), 0);
    if (sendLength < 0)
    {
        std::cout << "����ʧ��" << WSAGetLastError() << std::endl;
        // return false;
    }
}
bool Client::recvMessage(std::string &buff)
{
    buff.clear();
    char buffer[1024];
    recvLength = recv(serverSock, buffer, sizeof(buffer), 0);
    if (recvLength < 0)
    {
        std::cout << "����ʧ��" << WSAGetLastError() << std::endl;
        return 0;
    }
    else
        buff.append(buffer[0], buffer[strlen(buffer) - 1]);
    return 1;
}
