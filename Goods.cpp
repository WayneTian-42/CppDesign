#include "Goods.hpp"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <regex>
#include <utility>

bool GoodsInfo::operator==(const GoodsInfo &go) const
{
    return ((name == go.name) && (type == go.type) && (merchant == go.merchant));
};

void Goods::addItems(const std::string &goodsName, const std::string &merchant)
{
    name = goodsName;
    this->merchant = merchant;
    GoodsInfo tmp;
    copyInfo(tmp);
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it != goodsInfo.end())
    {
        output << "����Ʒ�Ѵ���\n1";
        server->sendMessage(output);
        return;
    }
    output << "��������Ʒ����\n";
    server->sendMessage(output);
    // std::cin >> discription;
    server->recvMessage(discription);
    discription.erase(discription.end() - 1);
    output << "��������Ʒ����\n";
    server->sendMessage(output);

    std::string buff;
    while (1)
    {
        input(price);
        if (price > 0)
            break;
        else
        {
            output << "����������һ��������\n";
            server->sendMessage(output);
        }
    }
    output << "��������Ʒ����\n";
    server->sendMessage(output);
    while (1)
    {
        input(amount);
        if (amount > 0)
            break;
        else
        {
            output << "����������һ��������\n";
            server->sendMessage(output);
        }
    }
    output << "��������Ʒ�ۿ�\n";
    server->sendMessage(output);
    while (1)
    {
        input(discount);
        if (discount > 0 && discount <= 1)
            break;
        else
        {
            output << "����������һ��0��1֮�������\n";
            server->sendMessage(output);
        }
    }
    output << "��ӳɹ���\n1";
    server->sendMessage(output);
    copyInfo(tmp);
    // tmp.sold = 0;
    goodsInfo.emplace_back(tmp);
}

void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    name = goodsName;
    this->merchant = merchant;
    GoodsInfo tmp;
    copyInfo(tmp);  // ��ǰ��Ϣ������tmp�У�Ȼ�����
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it == goodsInfo.end())
    {
        output << "����Ʒ������" << std::endl << '1';
        server->sendMessage(output);
        return;
    }
    if (it->merchant != merchant)
    {
        output << "����Ʒ�������̼�" << merchant << std::endl << '1';
        server->sendMessage(output);
        return;
    }
    copyInfo(it);
    getchar();  // ������һ������Ļس�����ֹ�������������
    std::string change;
    output << "���޸���Ʒ��Ϣ��\n"
           << "���ƣ�����س���ʾ���޸ģ�\n3";
    server->sendMessage(output);
    // std::getline(std::cin, change);
    server->recvMessage(change);
    change.erase(change.end() - 1);
    if (change.size())
        name = change;
    output << "����������س���ʾ���޸ģ�\n3";
    server->sendMessage(output);
    // std::getline(std::cin, change);
    server->recvMessage(change);
    change.erase(change.end() - 1);
    if (change.size())
        discription = change;
    output << "���ࣨ����س���ʾ���޸ģ�\n3";
    server->sendMessage(output);
    while (1)
    {
        int t = type;
        if (changeInt(t))
        {
            if (t > 3 || t < 1)
            {
                output << "û�и�������Ʒ������������\n";
                continue;
            }
            else
            {
                type = t;
                break;
            }
        }
    }
    output << "���ۣ�����س���ʾ���޸ģ�\n3";
    server->sendMessage(output);
    while (!changeDouble(price))
    {
    }
    output << "����������س���ʾ���޸ģ�\n3";
    server->sendMessage(output);
    while (!changeInt(amount))
    {
    }
    output << "�ۿۣ�����س���ʾ���޸ģ�\n3";
    server->sendMessage(output);
    while (1)
    {
        double dis = discount;
        if (changeDouble(dis))
        {
            if (dis > 1.0)
            {
                output << "�ۿ۲���������������\n3";
                server->sendMessage(output);
                continue;
            }
            else
            {
                discount = dis;
                break;
            }
        }
    }
    copyInfo(tmp);  //�����ݸ��»�����
    *it = tmp;
}
void Goods::search(std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type)
        {
            int sum = 0;
            for (auto mt : st.sold)
                sum += mt.second;
            // ��ʽ�����
            if (!flg)
                output << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����" << std::setw(8)
                       << std::left << "ԭ��" << std::setw(8) << std::left << "�ۿ�" << std::setw(8) << std::left
                       << "�ּ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left << "�̼�"
                       << std::endl;
            flg++;
            output << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                   << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount << std::setw(8)
                   << std::left << st.price * st.discount << std::setw(8) << std::left << st.amount - sum
                   << std::setw(20) << std::left << st.merchant << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        output << "û������Ҫ�����Ʒ�������ɸѡ������\n";
    output << '1';
    server->sendMessage(output);
}
void Goods::search(const std::string &name, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.type == type)
        {
            int sum = 0;
            for (auto mt : st.sold)
                sum += mt.second;
            if (!flg)
                output << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����" << std::setw(8)
                       << std::left << "ԭ��" << std::setw(8) << std::left << "�ۿ�" << std::setw(8) << std::left
                       << "�ּ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left << "�̼�"
                       << std::endl;
            flg++;
            output << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                   << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount << std::setw(8)
                   << std::left << st.price * st.discount << std::setw(8) << std::left << st.amount - sum
                   << std::setw(20) << std::left << st.merchant << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        output << "û������Ҫ�����Ʒ�������ɸѡ������\n";
    output << '1';
    server->sendMessage(output);
}
void Goods::search(const double lowPrice, const double highPrice, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            int sum = 0;
            for (auto mt : st.sold)
                sum += mt.second;
            if (!flg)
                output << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����" << std::setw(8)
                       << std::left << "ԭ��" << std::setw(8) << std::left << "�ۿ�" << std::setw(8) << std::left
                       << "�ּ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left << "�̼�"
                       << std::endl;
            flg++;
            output << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                   << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount << std::setw(8)
                   << std::left << st.price * st.discount << std::setw(8) << std::left << st.amount - sum
                   << std::setw(20) << std::left << st.merchant << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        output << "û������Ҫ�����Ʒ�������ɸѡ������\n";
    output << '1';
    server->sendMessage(output);
}
void Goods::search(const int lowAmount, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= INT_MAX)
        {
            int sum = 0;
            for (auto mt : st.sold)
                sum += mt.second;
            if (!flg)
                output << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����" << std::setw(8)
                       << std::left << "ԭ��" << std::setw(8) << std::left << "�ۿ�" << std::setw(8) << std::left
                       << "�ּ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left << "�̼�"
                       << std::endl;
            flg++;
            output << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                   << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount << std::setw(8)
                   << std::left << st.price * st.discount << std::setw(8) << std::left << st.amount - sum
                   << std::setw(20) << std::left << st.merchant << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        output << "û������Ҫ�����Ʒ�������ɸѡ������\n";
    output << '1';
    server->sendMessage(output);
}
int Goods::searchAmount(const std::string &name, const std::string &merchant, const int type) const
{
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.merchant == merchant && st.type == type)
        {
            return st.amount;
        }
    }
    return -1;
}
void Goods::atDiscount(const double dis)
{
    int begin = num;
    for (auto &st : goodsInfo)
        if (st.type == type)
            st.discount = dis;
}
void Goods::preorderGoods(const std::string &name, const std::string &merchant, const std::string &consumer,
                          const int amount)
{
    GoodsInfo tmp;
    tmp.name = name;
    tmp.merchant = merchant;
    tmp.type = type;
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it != goodsInfo.end())
        it->sold[consumer] = amount;
}
void Goods::soldOut(const std::string &consumer)
{
    for (auto &gt : goodsInfo)
    {
        gt.amount -= gt.sold[consumer];
        gt.sold.erase(consumer);
    }
}
void Goods::updateInfo(std::vector<std::pair<GoodsInfo, int>> &preorder) const
{
    for (auto &vt : preorder)
    {
        auto gt = std::find(goodsInfo.begin(), goodsInfo.end(), vt.first);
        vt.first = *gt;
    }
}
// template <typename T> void Goods::input(T &x, bool mode) const

bool Goods::changeInt(int &number)
{
    std::string tmp;
    // std::getline(std::cin, tmp);
    server->recvMessage(tmp);
    if (tmp.size() == 1)
        return true;
    tmp.erase(tmp.end() - 1);
    if (isInt(tmp))
    {
        int t = std::stoi(tmp);
        /* if (t < 0)
        {
            output << "���벻�Ϸ���������������\n";
            return false;
        } */
        number = t;
        return true;
    }
    else
    {
        output << "���벻�Ϸ���������������\n";
        server->sendMessage(output);
        return false;
    }
}
bool Goods::changeDouble(double &number)
{
    std::string tmp;
    // std::getline(std::cin, tmp);
    server->recvMessage(tmp);
    if (tmp.size() == 1)
        return true;
    tmp.erase(tmp.end() - 1);
    if (isDouble(tmp))
    {
        double t = std::stod(tmp);
        /* if (t < 0.0)
        {
            output << "���벻�Ϸ���������������\n";
            return false;
        } */
        number = t;
        return true;
    }
    else
    {
        output << "���벻�Ϸ������������֣�\n";
        server->sendMessage(output);
        return false;
    }
}
bool Goods::isInt(const std::string &input) const
{
    std::regex rx("^\\-?\\d+$");  //+�ű�ʾ���ƥ��
    return std::regex_match(input, rx);
}
bool Goods::isDouble(const std::string &input) const
{
    std::regex rx("^\\d+(.\\d+)?$");
    return std::regex_match(input, rx);
}
void Goods::input(int &x)
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
void Goods::input(double &x)
{
    std::string tmp;
    server->recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    if (tmp.empty())
    {
        x = -1;
        return;
    }
    while (!isDouble(tmp))
    {
        output << "���벻�Ϸ�������������\n";
        server->sendMessage(output);
        server->recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stod(tmp);
}
void Goods::copyInfo(GoodsInfo &des) const
{
    des.name = name;
    des.merchant = merchant;
    des.discription = discription;
    des.type = type;
    des.amount = amount;
    des.price = price;
    des.discount = discount;
}
void Goods::copyInfo(const std::vector<GoodsInfo>::iterator &sou)
{
    amount = sou->amount;
    price = sou->price;
    discount = sou->discount;
    discription = sou->discription;
}
void Goods::getGoods(std::vector<GoodsInfo> &des) const
{
    des = goodsInfo;
}
void Goods::setGoods(const std::vector<GoodsInfo> &sou)
{
    for (int i = 0; i < sou.size(); i++)
    {
        goodsInfo[i].sold = sou[i].sold;
    }
}
double Foods::getPrice() const
{
    return price * discount;
}
double Clothes::getPrice() const
{
    return price * discount;
}
double Books::getPrice() const
{
    return price * discount;
}
