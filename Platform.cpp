#include "Platform.hpp"
#include <iostream>
#include <string>

void Platform::show()
{
    int action;
    do
    {
        std::cout << "ѡ�������\n"
                  << "1. �û�ע��&��¼\n"
                  << "2. �û���Ϣ�鿴&�޸ģ���¼��\n"
                  << "3. ��Ʒ��Ϣ�鿴\n"
                  << "4. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
                  << "-1. �˳�ƽ̨" << std::endl;
        std::cin >> action;
        // system("clear");
        switch (action)
        {
            case 1:
                userRegisterOrLog();
                break;
            case 2:
                userInformationChange();
                break;
            case 3:
                goodsInformation();
                break;
            case 4:
                changeGoods();
                break;
            default:
                break;
        }
    } while (action != -1);
    std::cout << "��лʹ�ã�\n" << std::endl;
}
void Platform::userRegisterOrLog()
{
    std::cout << "ѡ�������\n"
              << "1. �û�ע��\n"
              << "2. �û���¼\n"
              << "-1. �˳�" << std::endl;
    int choice, type;
    std::cin >> choice;
    std::string operation[2] = {"ע��", "��¼"};
    if (choice != -1)
    {
        std::cout << "������" << operation[choice - 1] << "���˻����ͣ�\n"
                  << "1��ʾ�˿ͣ�2��ʾ�̼�\n";
        std::cin >> type;
        std::cout << "\n�����˻�����\n";
        std::cin >> name;
        freeUser();
        switch (type)
        {
            case 1:
                user = new Consumer(name);
                break;
            case 2:
                user = new Merchant(name);
                break;
            default:
                break;
        }
    }
    switch (choice)
    {
        case 1:
            user->userRegister();
            freeUser();
            name.clear();
            break;
        case 2:
            if (!user->login(type))
            {
                freeUser();
                name.clear();
            }
            break;
        default:
            break;
    }
    // user->save();
}
void Platform::userInformationChange()
{
    if (name.empty())
    {
        std::cout << "\n���¼�����\n";
        return;
    }
    std::cout << name << ", ��ѡ�������\n"
              << "1. �޸�����\n"
              << "2. ����ѯ\n"
              << "3. ����ֵ\n"
              << "4. ����\n"
              << "-1. �˳�" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == -1)
        return;
    switch (choice)
    {
        case 1:
            user->changePwd();
            break;
        case 2:
            user->queryBalance();
            break;
        case 3:
            user->topUp();
            break;
        default:
            break;
    }
    freeUser();
}
void Platform::goodsInformation()
{
    std::cout << "��ѡ��ɸѡ����\n"
              << "0. չʾ������Ʒ\n"
              << "1. ������ɸѡ\n"
              << "2. ���۸�ɸѡ\n"
              << "3. ������ɸѡ\n"
              << "-1. �˳�\n";
    int choice, amount;
    double priceLow, priceHigh;
    std::cin >> choice;
    std::string goodsName;
    if (choice != -1)
        definiteType();
    switch (choice)
    {
        case 0:
            goods->search();
            break;
        case 1:
            std::cout << "��������Ʒ����";
            std::cin >> goodsName;
            goods->search(goodsName);
            break;
        case 2:
            std::cout << "��������Ʒ��ͼ۸�����߼۸�";
            std::cin >> priceLow >> priceHigh;
            //��С�Ƚ�
            goods->search(priceLow, priceHigh);
            break;
        case 3:
            std::cout << "��������Ʒ��С����";
            std::cin >> amount;
            goods->search(amount);
            break;
        default:
            break;
    }
    freeGoods();
}
void Platform::changeGoods()
{
    if (name.empty() || user->getUserType() == 1)
    {
        std::cout << "������̼��˺ź���иò�����\n";
        return;
    }
    int choice;
    std::cout << "��ѡ��Ҫ���еĲ���\n"
              << "1. �޸�������Ʒ\n"
              << "2. �����Ʒ\n"
              << "-1. �˳�\n";
    std::cin >> choice;
    std::string goodsName;
    if (choice != -1)
    {
        definiteType();
        std::cout << "������Ʒ����";
        std::cin >> goodsName;
    }
    switch (choice)
    {
        case 1:
            goods->changeItems(goodsName, name);
            break;
        case 2:
            goods->addItems(goodsName, name);
        default:
            break;
    }
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    std::cout << "��ѡ����Ʒ����\n"
              << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
    std::cin >> type;
    freeGoods();
    switch (type)
    {
        case 1:
            goods = new Foods(name);
            break;
        case 2:
            goods = new Clothes(name);
            break;
        case 3:
            goods = new Books(name);
            break;
        default:
            break;
    }
}
void Platform::freeUser()
{
    if (user)
    {
        delete user;
        user = nullptr;
    }
}
void Platform::freeGoods()
{
    if (goods)
    {
        delete goods;
        goods = nullptr;
    }
}
