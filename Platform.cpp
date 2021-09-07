#include "Platform.hpp"
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>
#include <limits>
//#include <utility>
// #include <WinSock2.h>

//test
void Platform::show()
{
    int action;
    do
    {
        output << "ѡ�������\n"
               << "1. �û�����\n"
               << "2. ��Ʒչʾ\n"
               << "3. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
               << "�������� �˳�ƽ̨" << std::endl;
        input(action);
        switch (action)
        {
            case 1:
                userCenter();
                break;
            case 2:
                goodsInformation();
                break;
            case 3:
                changeGoods();
                break;
            default:
                break;
        }
        output << std::endl;
    } while (action > 0 && action < 4);
    output << "��лʹ�ã�" << std::endl;
}
void Platform::userCenter()
{
    if (name.empty())  // δ��¼�����ֻ��ע����¼
        userRegisterOrLog();
    else  // �ѵ�¼
    {
        int choice;
        do
        {
            output << "ѡ�������\n"
                   << "1. �û���Ϣ��ѯ���޸�\n"
                   << "2. ע����¼\n"
                   << "3. ���ﳵ����\n"
                   << "�������� �˳�" << std::endl;
            input(choice);
            switch (choice)
            {
                case 1:
                    userInformationChange();
                    break;
                case 2:
                    userQuit();
                    return;
                case 3:
                    user->orderManagement(showGoods, allGoods);
                    break;
                default:
                    break;
            }
        } while (choice > 0 && choice < 4);
    }
}
void Platform::userRegisterOrLog()
{
    output << "ѡ�������\n"
           << "1. �û�ע��\n"
           << "2. �û���¼\n"
           << "�������� �˳�" << std::endl;
    int choice, type;
    input(choice);
    std::string operation[2] = {"ע��", "��¼"};
    if (choice == 1 || choice == 2)
    {
        output << "������" << operation[choice - 1] << "���û����ͣ�\n"
               << "1��ʾ�˿ͣ�2��ʾ�̼�\n";
        input(type);
        if (type > 2 || type < 0 || (type == 0 && choice == 1))  // ֻ�е�¼ʱ��ѡ�����Ա����
        {
            output << "û�и������û������˳�\n";
            return;
        }
        output << "�����û�����\n";
        std::cin >> name;
        freeUser();
        switch (type)
        {
            case 0:
                user = new Admin(name, client, server);
                break;
            case 1:
                user = new Consumer(name, client, server);
                break;
            case 2:
                user = new Merchant(name, client, server);
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
            if (!user->login(type))  // ��¼ʧ�������
            {
                freeUser();
                name.clear();
            }
            else
            {
                auto mt = shoppingCart.find(name);
                // auto st =
                if (mt != shoppingCart.end())
                    user->setShoppingCart(mt->second);
                mt = finalOrder.find(name);
                if (mt != finalOrder.end())
                    user->setFinalOrder(mt->second);
            }
            break;
        default:
            break;
    }
}
void Platform::userInformationChange()
{
    int choice;
    std::string hh;
    do
    {
        /* char tmp[15];
        std::strcpy(tmp, name.c_str()); */
        output << name << ", ��ѡ�������\n"
               << "1. �޸�����\n"
               << "2. ����ѯ\n"
               << "3. ����ֵ������\n"
               << "�������� �˳�" << std::endl;
        input(choice);
        switch (choice)
        {
            case 1:
                user->changePwd();
                break;
            case 2:
                output << name << "������ǰ�˻����Ϊ" << user->queryBalance() << "Ԫ\n";
                break;
            case 3:
                user->topUpAndDown();
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 4);
}
void Platform::userQuit()
{
    output << "���˳���\n";
    std::vector<std::pair<GoodsInfo, int>> shoppingcart, order;
    user->getShoppingCart(shoppingcart);
    shoppingCart.insert(std::make_pair(name, shoppingcart));
    user->getFinalOrder(order);
    finalOrder.insert(std::make_pair(name, order));
    name.clear();
    showGoods.clear();
    freeUser();
}
void Platform::goodsInformation()
{
    int choice;
    output << "��ѡ��ɸѡ����\n"
           << "0. չʾĳ����Ʒ\n"
           << "1. ������ɸѡ\n"
           << "2. ���۸�ɸѡ\n"
           << "3. ������ɸѡ\n"
           << "�������� �˳�\n";
    int amount;
    double priceLow, priceHigh;
    input(choice);
    std::string goodsName;
    if (choice >= 0 && choice < 4)
        definiteType();
    else
        return;
    goods->setGoods(allGoods);
    goods->getGoods(allGoods);
    switch (choice)
    {
        case 0:
            goods->search(showGoods);
            break;
        case 1:
            output << "��������Ʒ����\n";
            std::cin >> goodsName;
            goods->search(goodsName, showGoods);
            break;
        case 2:
            while (1)
            {
                output << "��������Ʒ��ͼ۸�\n";
                input(priceLow);
                output << "��������Ʒ��߼۸�\n";
                input(priceHigh);
                //��С�Ƚ�
                if (priceLow > priceHigh || priceLow < 0 || priceHigh < 0)
                    output << "����������������룡\n";
                else
                {
                    goods->search(priceLow, priceHigh, showGoods);
                    break;
                }
            }
            break;
        case 3:
            output << "��������Ʒ��С����";
            input(amount);
            goods->search(amount, showGoods);
            break;
        default:
            break;
    }
    if (!name.empty())
    {
        output << "��ѡ�������\n "
               << "1. ��ת�����ﳵ����\n"
               << "�������� �˳�\n"
               << std::endl;
        std::cin >> choice;
        if (choice == 1)
            user->orderManagement(showGoods, allGoods);
    }
    // ʵ���
    /*  output << "��ѡ�������\n "
               << "1. ������Ʒ\n"
               << "�������� �˳�\n"
               << std::endl;
     std::cin >> choice;
     if (choice == 1)
         purchaseGoods(); */
    goods->getGoods(allGoods);
    freeGoods();
    //���vector
    std::vector<GoodsInfo> tmp;
    showGoods.swap(tmp);
}
void Platform::changeGoods()
{
    // δ��¼�����
    if (name.empty() || user->getUserType() == 1)
    {
        output << "������̼��˺ź���иò�����\n";
        return;
    }
    int choice;
    do
    {
        double dis;
        output << "��ѡ��Ҫ���еĲ���\n"
               << "1. �޸�������Ʒ\n"
               << "2. �����Ʒ\n"
               << "�������� �˳�\n";
        input(choice);
        std::string goodsName;
        if ((choice > 0 && choice < 3) || (choice == 0 && user->getUserType() == 0))
        {
            definiteType();
            goods->setGoods(allGoods);
            goods->getGoods(allGoods);
            if (choice)
            {
                output << "������Ʒ����\n";
                std::cin >> goodsName;
            }
        }
        switch (choice)
        {
            case 0:
                if (user->getUserType())
                {
                    output << "û��Ȩ��!\n";
                    break;
                }
                output << "������Ҫ�������ۿ�(��С����ʾ��0-1֮��):\n";
                input(dis);
                if (dis < 0 || dis > 1)
                {
                    output << "�ۿ۲��������˳���\n";
                    return;
                }
                goods->atDiscount(dis);
                output << "���۳ɹ�";
                break;
            case 1:
                goods->changeItems(goodsName, name);
                break;
            case 2:
                goods->addItems(goodsName, name);
            default:
                break;
        }
    } while (choice > 0 && choice < 3);
    goods->getGoods(allGoods);
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    output << "��ѡ����Ʒ����\n"
           << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
    input(type);
    freeGoods();
    while (type < 1 || type > 3)
    {
        output << "û�и�������Ʒ������������\n";
        input(type);
    }
    switch (type)
    {
        case 1:
            goods = new Foods(name, client, server);
            break;
        case 2:
            goods = new Clothes(name, client, server);
            break;
        case 3:
            goods = new Books(name, client, server);
            break;
        default:
            break;
    }
}
template <typename T> void Platform::input(T &x)
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
    inputStream >> x;
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
