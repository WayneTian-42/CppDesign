#include <iostream>
#include "Platform.hpp"
// #include "MySocket.hpp"

int main()
{
    Server server;
    Client client;

    std::cout << "请输入建立客户端还是服务端\n";
    int choice;
    std::cin >> choice;
    if (choice == 0)
    {
        if (!server.serverInit())
            return -1;
    }
    else if (choice == 1)
    {
        if (!client.clientInit())
            return -1;
    }
    Platform sys(client, server);
    sys.show();
    sys.freeUser();
    sys.freeGoods();

    /* std::string name;
    std::cout << "Please enter your name:\n";
    std::cin >> name;
    if (!name.size())
        std::cout << "No input!";
    else
    {
        Account test{name};
        if (!test.registerAcc())
            std::cout << "The name has been used!\n";
        test.changePwd();
    } */
    /* std::string iname;
    int type;
    std::cout << "Please enter item name:\n";
    std::cin >> iname;
    std::cout << "type:  ";
    std::cin >> type;
    if (type == 1)
    {
        Foods gtest1(iname);
        gtest1.addItems();
        std::cout << gtest1.getPrice();
    }
    else if (type == 2)
        Clothes gtest2(iname);
    else if (type == 3)
        Books gtest3(iname); */
    // system("pause");
    return 0;
}