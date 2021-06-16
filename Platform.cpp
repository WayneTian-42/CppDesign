#include "Platform.hpp"
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>
#include <limits>
#include <regex>
//#include <utility>
// #include <WinSock2.h>

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
        server.sendMessage(output);
        /* client.recvMessage(); */
        /* std::string tmp;
        server.recvMessage(tmp);
        action = std::stoi(tmp); */
        input(action);
        // std::cout << action;
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
        // output << std::endl;
    } while (action > 0 && action < 4);
    if (action != -1)
    {
        output << "��лʹ�ã�" << std::endl << "0";
        server.sendMessage(output);
    }
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
            // input(choice);
            server.sendMessage(output);
            /* std::string tmp;
            server.recvMessage(tmp);
            choice = std::stoi(tmp); */
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
    /* output << "1";
    server.sendMessage(output); */
}
void Platform::userRegisterOrLog()
{
    output << "ѡ�������\n"
           << "1. �û�ע��\n"
           << "2. �û���¼\n"
           << "�������� �˳�" << std::endl;
    int choice, type;
    server.sendMessage(output);
    input(choice);
    std::string operation[2] = {"ע��", "��¼"};
    if (choice == 1 || choice == 2)
    {
        output << "������" << operation[choice - 1] << "���û����ͣ�\n"
               << "1��ʾ�˿ͣ�2��ʾ�̼�\n";
        server.sendMessage(output);
        input(type);
        if (type > 2 || type < 0 || (type == 0 && choice == 1))  // ֻ�е�¼ʱ��ѡ�����Ա����
        {
            output << "û�и������û������˳�\n1";  //
            server.sendMessage(output);
            return;
        }
        output << "�����û�����\n";
        server.sendMessage(output);
        input(name);
        if (name.empty())
            return;
        freeUser();
        switch (type)
        {
            case 0:
                user = new Admin(name, server);
                break;
            case 1:
                user = new Consumer(name, server);
                break;
            case 2:
                user = new Merchant(name, server);
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
        server.sendMessage(output);
        input(choice);
        switch (choice)
        {
            case 1:
                user->changePwd();
                break;
            case 2:
                output << name << "������ǰ�˻����Ϊ" << user->queryBalance() << "Ԫ\n1";
                server.sendMessage(output);
                break;
            case 3:
                user->topUpAndDown();
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 4);
    /*  output << "1";
     server.sendMessage(output); */
}
void Platform::userQuit()
{
    output << "���˳���\n1";
    server.sendMessage(output);
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
    server.sendMessage(output);
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
            server.sendMessage(output);
            // std::cin >> goodsName;
            input(goodsName);
            goods->search(goodsName, showGoods);
            break;
        case 2:
            while (1)
            {
                output << "��������Ʒ��ͼ۸�\n";
                server.sendMessage(output);
                input(priceLow);
                output << "��������Ʒ��߼۸�\n";
                server.sendMessage(output);
                input(priceHigh);
                //��С�Ƚ�
                if (priceLow > priceHigh || priceLow < 0 || priceHigh < 0)
                {
                    output << "����������������룡\n";
                    server.sendMessage(output);
                }
                else
                {
                    goods->search(priceLow, priceHigh, showGoods);
                    break;
                }
            }
            break;
        case 3:
            output << "��������Ʒ��С����";
            server.sendMessage(output);
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
        server.sendMessage(output);
        input(choice);
        // std::cin >> choice;
        if (choice == 1)
            user->orderManagement(showGoods, allGoods);
    }
    output << "1";
    server.sendMessage(output);
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
        output << "������̼��˺ź���иò�����\n1";
        server.sendMessage(output);
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
        server.sendMessage(output);
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
                server.sendMessage(output);
                input(goodsName);
                // std::cin >> goodsName;
            }
        }
        switch (choice)
        {
            case 0:
                if (user->getUserType())
                {
                    output << "1";
                    server.sendMessage(output);
                    break;
                }
                output << "������Ҫ�������ۿ�(��С����ʾ��0-1֮��):\n";
                server.sendMessage(output);
                input(dis);
                if (dis < 0 || dis > 1)
                {
                    output << "�ۿ۲��������˳���\n1";
                    server.sendMessage(output);
                    return;
                }
                goods->atDiscount(dis);
                output << "���۳ɹ�\n1";
                server.sendMessage(output);
                break;
            case 1:
                goods->changeItems(goodsName, name);
                break;
            case 2:
                goods->addItems(goodsName, name);
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 3);
    /* output << "1";
    server.sendMessage(output); */
    if (goods != nullptr)
        goods->getGoods(allGoods);
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    output << "��ѡ����Ʒ����\n"
           << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
    server.sendMessage(output);
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
            goods = new Foods(name, server);
            break;
        case 2:
            goods = new Clothes(name, server);
            break;
        case 3:
            goods = new Books(name, server);
            break;
        default:
            break;
    }
}

/* void Platform::initSock()
{
    server.serverInit();
} */
void Platform::input(int &x)
{
    /* std::cin >> x;

    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "���벻�Ϸ�������������\n";
        std::cin >> x;
        continue;
    }
    inputStream >> x; */
    std::string tmp;
    server.recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    if (tmp.empty())
    {
        x = -1;
        return;
    }
    while (!isInt(tmp))
    {
        output << "���벻�Ϸ�������������\n";
        server.sendMessage(output);
        server.recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stoi(tmp);
}
void Platform::input(double &x)
{
    std::string tmp;
    server.recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    while (!isDouble(tmp))
    {
        output << "���벻�Ϸ�������������\n";
        server.sendMessage(output);
        server.recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stod(tmp);
}
void Platform::input(std::string &x)
{
    server.recvMessage(x);
    if (!x.empty())
        x.erase(x.end() - 1);
}
bool Platform::isInt(const std::string &input) const
{
    std::regex rx("^\\-?\\d+$");  //+�ű�ʾ���ƥ��
    return std::regex_match(input, rx);
}
bool Platform::isDouble(const std::string &input) const
{
    std::regex rx("^\\d+(.\\d+)?$");
    return std::regex_match(input, rx);
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
