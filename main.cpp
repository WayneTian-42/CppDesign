#include <iostream>
#include <stdio.h>
#include "Platform.hpp"
#include "PlatformShow.hpp"
// #include "MySocket.hpp"

int main()
{
    std::cout << "���������(����0)���߿ͻ���(����1)\n";
    int choice;
    std::cin >> choice;
    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "���벻�Ϸ�������������\n";
        std::cin >> choice;
        continue;
    }
    if (choice == 0)
    {
        Platform sys;
        sys.show();
        sys.freeUser();
        sys.freeGoods();
    }
    else if (choice == 1)
    {
        // getchar();
        PlatformShow sysc;
        sysc.show();
    }
    else
        std::cout << "ѡ��������˳�\n";
    return 0;
}