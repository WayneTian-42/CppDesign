#include "Order.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <regex>

// goods����ɾ����
void Order::preAddGoods(std::vector<GoodsInfo> &showGoods, std::vector<GoodsInfo> &goodsInfo)
{
    definiteType();
    goods->setGoods(goodsInfo);
    goods->search(showGoods);
    GoodsInfo good;
    chooseGoods(showGoods, good);
    if (!good.name.empty())
        chooseAmount(good);
    // std::vector<GoodsInfo> tmp;
    // showGoods.swap(tmp);
    // showGoods.erase(); ���ò������
}
//�޸Ĳ��Ҳ���
void Order::chooseGoods(std::vector<GoodsInfo> &showGoods, GoodsInfo &good)
{
    std::string gname, merchant;
    output << "������Ҫ�������Ʒ��\n";
    server->sendMessage(output);
    int flg = 1, num = 0;
    while (1)
    {
        // std::cin >> gname;
        server->recvMessage(gname);
        gname.erase(gname.end() - 1);
        for (auto it : showGoods)
        {
            if (it.name == gname)
            {
                good = it;
                merchant = it.merchant;
                num++;
            }
        }
        if (!num)
        {
            output << "û�и���Ʒ��������������Ʒ\n";
            server->sendMessage(output);
        }
        else
            break;
    }
    if (num > 1)
    {
        bool flg = false;
        while (!flg)
        {
            output << "����Ʒ����̼����������������빺����̼���\n";
            server->sendMessage(output);
            // std::cin >> merchant;
            server->recvMessage(merchant);
            for (auto it : showGoods)
            {
                if (it.name == gname && it.merchant == merchant)
                {
                    good = it;
                    flg = true;
                    break;
                }
            }
            if (!flg)
            {
                output << "û�и��̼ң������������̼�\n";
                server->sendMessage(output);
            }
        }
    }
    if (good.merchant == name)
    {
        output << "���ܹ����Լ�����Ʒ�����˳���\n1";
        server->sendMessage(output);
        good.name.erase();
    }
}
void Order::chooseAmount(const GoodsInfo &good)
{
    output << "������Ҫ���������(0��ʾȡ�����빺�ﳵ)��\n";
    server->sendMessage(output);
    int number;
    bool can = true;
    while (1)
    {
        input(number);
        if (number > good.amount)
        {
            output << "��Ҫ����������������������������������\n";
            server->sendMessage(output);
        }
        else if (number < 0)
        {
            output << "���������������Ʒ������������\n";
            server->sendMessage(output);
        }
        else if (number == 0)
        {
            output << "���˳�\n1";  //
            server->sendMessage(output);
            break;
        }
        else
        {
            output << "����ӵ����ﳵ\n1";  //
            //��ͬ��Ʒֻ�����һ�μ�¼
            server->sendMessage(output);
            addGoods(good, number);
            break;
        }
    }
}
void Order::addGoods(const GoodsInfo &good, const int num)
{
    bool flg = true;
    for (auto &it : shoppingCart)
    {
        // ����
        if (it.first.name == good.name && it.first.merchant == good.merchant)
        {
            it.second += num;
            flg = false;
            break;
        }
    }
    if (flg)
        shoppingCart.emplace_back(std::make_pair(good, num));
}
void Order::showShoppingCart()
{
    if (shoppingCart.empty())
    {
        output << "���ﳵ����գ�\n1";
        server->sendMessage(output);
        return;
    }
    output << "���ﳵ���£�\n";
    output << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�ּ�" << std::setw(8) << std::left
           << "��������" << std::setw(20) << std::left << "�̼�" << std::endl;
    for (auto it : shoppingCart)
    {
        output << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left
               << it.first.price * it.first.discount << std::setw(8) << std::left << it.second << std::setw(20)
               << std::left << it.first.merchant << std::endl;
    }
    output << '1';
    server->sendMessage(output);
}
int Order::search(const std::string &name)
{
    int pos;
    std::vector<int> num;
    for (int i = 0; i < shoppingCart.size(); i++)
    {
        if (shoppingCart[i].first.name == name)
        {
            pos = i;
            num.emplace_back(i);
        }
    }
    if (num.size() < 1)
        return -1;
    else if (num.size() > 1)
    {
        bool flg = false;
        output << "����Ʒ���ﳵ���ж��֣��������빺����̼���\n";
        server->sendMessage(output);
        while (!flg)
        {
            std::string merchant;
            /* output << "����Ʒ���ﳵ���ж��֣��������빺����̼���\n";
            server->sendMessage(output); */
            // std::cin >> merchant;
            server->recvMessage(merchant);
            for (int i = 0; i < num.size(); i++)
            {
                if (shoppingCart[num[i]].first.merchant == merchant)
                {
                    pos = i;
                    flg = true;
                    break;
                }
            }
            if (!flg)
            {
                output << "û�и��̼ң������������̼�\n";
                server->sendMessage(output);
            }
        }
    }
    return pos;
}
void Order::deleteGoods()
{
    definiteType();
    showShoppingCart();
    if (shoppingCart.empty())
    {
        output << "�����޸ģ����˳���\n1";
        server->sendMessage(output);
        return;
    }
    std::string name;
    output << "����Ҫ�޸���������Ʒ:\n";
    server->sendMessage(output);
    // std::cin >> name;
    server->recvMessage(name);
    name.erase(name.end() - 1);
    int pos = search(name);
    if (pos == -1)
    {
        output << "û�и���Ʒ�����˳�\n1";  //
        server->sendMessage(output);
        return;
    }
    output << name << "����Ϊ" << shoppingCart[pos].second << std::endl;
    output << "������Ҫ�޸ĵ�������������ʾ���ӣ�������ʾ���٣�\n";
    server->sendMessage(output);
    int number;
    // input(number);
    while (1)
    {
        input(number);
        if (shoppingCart[pos].second + number < 0)
        {
            output << "���ﳵ��������Ϊ��������������\n";
            server->sendMessage(output);
            continue;
        }
        else
            break;
    }
    shoppingCart[pos].second += number;
}
void Order::generateOrder(std::vector<std::pair<GoodsInfo, int>> &finalOrder, std::vector<GoodsInfo> &goodsInfo)
{
    showShoppingCart();
    if (shoppingCart.empty())
        return;
    output << "������ÿ����ƷҪ���������\n";
    output << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left
           << "��������" << std::setw(8) << std::left << "�ۿ�" << std::setw(20) << std::left << "�̼�" << std::endl;
    server->sendMessage(output);
    for (auto it = shoppingCart.begin(); !shoppingCart.empty() && it != shoppingCart.end(); it++)
    {
        int amount;
        bool flg = true;
        output << std::setw(20) << std::left << it->first.name << std::setw(8) << std::left << it->first.price
               << std::setw(8) << std::left << it->second << std::setw(8) << std::left << it->first.discount
               << std::setw(20) << std::left << it->first.merchant << std::endl;
        server->sendMessage(output);
        while (flg)
        {
            input(amount);
            if (amount < 0)
            {
                output << "���ܹ���������Ʒ������������\n";
                server->sendMessage(output);
            }
            else if (amount > it->first.amount)
            {
                output << "�̼�û����ô����Ʒ������������\n";
                server->sendMessage(output);
            }
            else if (amount > it->second)
            {
                output << "���ܳ������ﳵ������������������\n";
                server->sendMessage(output);
            }
            else
            {
                finalOrder.emplace_back(std::make_pair(it->first, amount));
                if (amount == it->second)
                    shoppingCart.erase(it);
                else
                    it->second -= amount;
                preorderGoods(goodsInfo, it->first.name, it->first.merchant, amount);
                flg = false;
            }
        }
    }
    output << "****************************************************************\n";
    output << "���ն������£�\n";
    output << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left
           << "��������" << std::setw(8) << std::left << "�ۿ�" << std::setw(8) << std::left << "�ܼ�" << std::endl;
    for (auto it : finalOrder)
    {
        double total = it.first.price * it.first.discount * it.second;
        output << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left << it.first.price
               << std::setw(8) << std::left << it.second << std::setw(8) << std::left << it.first.discount
               << std::setw(8) << std::left << total << std::endl;
        sum += total;
    }
    output << "������Ʒ�ܼ۸�Ϊ" << sum << "Ԫ\n1";
    server->sendMessage(output);
}
double Order::getToatalPrice()
{
    return sum;
}
void Order::clearPrice()
{
    sum = 0;
}
void Order::preorderGoods(std::vector<GoodsInfo> &goodsInfo, const std::string &goodsName, const std::string &merchant,
                          const int amount)
{
    freeGoods();
    goods = new Foods(*server);
    goods->setGoods(goodsInfo);
    goods->preorderGoods(goodsName, merchant, name, amount);
    goods->getGoods(goodsInfo);
    freeGoods();
    goods = new Clothes(*server);
    goods->setGoods(goodsInfo);
    goods->preorderGoods(goodsName, merchant, name, amount);
    goods->getGoods(goodsInfo);
    freeGoods();
    goods = new Books(*server);
    goods->setGoods(goodsInfo);
    goods->preorderGoods(goodsName, merchant, name, amount);
    goods->getGoods(goodsInfo);
    freeGoods();
}
void Order::soldOut(std::vector<GoodsInfo> &goodsInfo)
{
    freeGoods();
    goods = new Foods(*server);
    goods->setGoods(goodsInfo);
    goods->soldOut(name);
    goods->getGoods(goodsInfo);
    freeGoods();
    goods = new Clothes(*server);
    goods->setGoods(goodsInfo);
    goods->soldOut(name);
    goods->getGoods(goodsInfo);
    freeGoods();
    goods = new Books(*server);
    goods->setGoods(goodsInfo);
    goods->soldOut(name);
    goods->getGoods(goodsInfo);
    freeGoods();
}
void Order::setShoppingCart(std::vector<std::pair<GoodsInfo, int>> &tmp)
{
    shoppingCart = tmp;
}
void Order::getShoppingCart(std::vector<std::pair<GoodsInfo, int>> &tmp)
{
    tmp = shoppingCart;
}
/* void Order::transferPayments()
{
} */

void Order::setName(const std::string &name)
{
    this->name = name;
}
void Order::definiteType()
{
    int type;
    /* if (!type)
    {
        output << "��ѡ����Ʒ����\n"
               << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
        input(type);
    } */
    output << "��ѡ����Ʒ����\n"
           << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
    server->sendMessage(output);
    input(type);
    while (type < 1 || type > 3)
    {
        output << "û�и�������Ʒ������������\n";
        server->sendMessage(output);
        input(type);
    }
    freeGoods();
    switch (type)
    {
        case 1:
            goods = new Foods(*server);
            break;
        case 2:
            goods = new Clothes(*server);
            break;
        case 3:
            goods = new Books(*server);
            break;
        default:
            break;
    }
}
void Order::freeGoods()
{
    if (goods)
    {
        delete goods;
        goods = nullptr;
    }
}
void Order::input(int &x)
{
    std::string tmp;
    server->recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    if (tmp.empty())
    {
        x = -1;
        return;
    }
    while (!isInt(tmp))
    {
        output << "���벻�Ϸ�������������\n";
        server->sendMessage(output);
        server->recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stoi(tmp);
}
bool Order::isInt(const std::string &input) const
{
    std::regex rx("^\\-?\\d+$");  //+�ű�ʾ���ƥ��
    return std::regex_match(input, rx);
}