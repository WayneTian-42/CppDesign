#include "Platform.hpp"
#include <iostream>
#include <string>

void Platform::show()
{
    int action;
    do
    {
        std::cout << "ѡ�������\n"
                  << "1. �û�����\n"
                  << "2. ��Ʒչʾ\n"
                  << "3. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
                  << "�������� �˳�ƽ̨" << std::endl;
        input(action);
        // system("clear");
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
        std::cout << std::endl;
    } while (action > 0 && action < 4);
    std::cout << "��лʹ�ã�\n" << std::endl;
}
void Platform::userCenter()
{
    if (name.empty())
        userRegisterOrLog();
    else
    {
        int choice;
        do
        {
            std::cout << "ѡ�������\n"
                      << "1. �û���Ϣ��ѯ���޸�\n"
                      << "2. ע����¼\n"
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
                default:
                    break;
            }
        } while (choice > 0 && choice < 3);
    }
}
void Platform::userRegisterOrLog()
{
    std::cout << "ѡ�������\n"
              << "1. �û�ע��\n"
              << "2. �û���¼\n"
              << "�������� �˳�" << std::endl;
    int choice, type;
    input(choice);
    std::string operation[2] = {"ע��", "��¼"};
    if (choice == 1 || choice == 2)
    {
        std::cout << "������" << operation[choice - 1] << "���˻����ͣ�\n"
                  << "1��ʾ�˿ͣ�2��ʾ�̼�\n";
        input(type);
        if (type > 2 || type < 0 || (type == 0 && choice == 1))
        {
            std::cout << "û�и������˻������˳�\n";
            return;
        }
        std::cout << "�����˻�����\n";
        std::cin >> name;
        freeUser();
        switch (type)
        {
            case 0:
                user = new Admin(name);
                break;
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
    /* if (name.empty())
    {
        std::cout << "���¼�����\n";
        return;
    } */
    int choice;
    do
    {
        std::cout << name << ", ��ѡ�������\n"
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
                std::cout << name << "������ǰ�˻����Ϊ" << user->queryBalance() << "Ԫ\n";
                break;
            case 3:
                user->topUp();
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 4);
    // freeUser();
}
void Platform::userQuit()
{
    name.clear();
    std::cout << "���˳���\n";
    freeUser();
}
void Platform::goodsInformation()
{
    int choice;
    std::cout << "��ѡ��ɸѡ����\n"
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
    switch (choice)
    {
        case 0:
            goods->search(showGoods);
            break;
        case 1:
            std::cout << "��������Ʒ����";
            std::cin >> goodsName;
            goods->search(goodsName, showGoods);
            break;
        case 2:
            std::cout << "��������Ʒ��ͼ۸�����߼۸�";
            input(priceLow);
            input(priceHigh);
            //��С�Ƚ�
            goods->search(priceLow, priceHigh, showGoods);
            break;
        case 3:
            std::cout << "��������Ʒ��С����";
            input(amount);
            goods->search(amount, showGoods);
            break;
        default:
            break;
    }
    /*  std::cout << "��ѡ�������\n "
               << "1. ������Ʒ\n"
               << "�������� �˳�\n"
               << std::endl;
     std::cin >> choice;
     if (choice == 1)
         purchaseGoods(); */
    freeGoods();
    //���vector
    std::vector<GoodsInfo> tmp;
    showGoods.swap(tmp);
}
void Platform::changeGoods()
{
    if (/* name.empty() ||  */ user->getUserType() == 1)
    {
        std::cout << "������̼��˺ź���иò�����\n";
        return;
    }
    int choice;
    do
    {
        double dis;
        std::cout << "��ѡ��Ҫ���еĲ���\n"
                  << "1. �޸�������Ʒ\n"
                  << "2. �����Ʒ\n"
                  << "�������� �˳�\n";
        input(choice);
        std::string goodsName;
        if (choice >= 0 && choice < 3)
        {
            definiteType();
            if (choice)
            {
                std::cout << "������Ʒ����";
                std::cin >> goodsName;
            }
        }
        switch (choice)
        {
            case 0:
                if (user->getUserType())
                {
                    std::cout << "û��Ȩ��!\n";
                    return;
                }
                std::cout << "������Ҫ�������ۿ�(��С����ʾ��0-1֮��):\n";
                input(dis);
                if (dis < 0 || dis > 1)
                {
                    std::cout << "�ۿ۲��������˳���\n";
                    return;
                }
                goods->atDiscount(dis);
                std::cout << "���۳ɹ�";
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
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    std::cout << "��ѡ����Ʒ����\n"
              << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
    input(type);
    freeGoods();
    while (type < 1 || type > 3)
    {
        std::cout << "û�и�������Ʒ������������\n";
        input(type);
    }
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
template <typename T> void Platform::input(T &x) const
{
    std::cin >> x;

    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "���벻�Ϸ�����������������\n";
        std::cin >> x;
        continue;
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