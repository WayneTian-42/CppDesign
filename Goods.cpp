#include "Goods.hpp"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <regex>

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
        std::cout << "����Ʒ�Ѵ���\n";
        return;
    }
    std::cout << "��������Ʒ����\n";
    std::cin >> discount;
    std::cout << "��������Ʒ����\n";
    while (1)
    {
        input(price);
        if (price > 0)
            break;
        else
            std::cout << "����������һ��������\n";
    }
    std::cout << "��������Ʒ����\n";
    while (1)
    {
        input(amount);
        if (amount > 0)
            break;
        else
            std::cout << "����������һ��������\n";
    }
    std::cout << "��������Ʒ�ۿ�\n";
    while (1)
    {
        input(discount);
        if (discount > 0)
            break;
        else
            std::cout << "����������һ��������\n";
    }
    copyInfo(tmp);
    goodsInfo.emplace_back(tmp);
}
//�ĳɰѸ��̼���Ʒȫ����ʾ
void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    name = goodsName;
    this->merchant = merchant;
    GoodsInfo tmp;
    copyInfo(tmp);
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it == goodsInfo.end())
    {
        std::cout << "����Ʒ������" << std::endl;
        return;
    }
    if (it->merchant != merchant)
    {
        std::cout << "����Ʒ�������̼�" << merchant << std::endl;
        return;
    }
    copyInfo(it);
    //����Ϊ�û���ѡ�޸���Щ���ݣ�û�м��Ƿ�����
    getchar();
    std::string change;
    std::cout << "���޸���Ʒ��Ϣ��\n"
              << "���ƣ�����س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.empty())
        name = change;
    std::cout << "����������س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.empty())
        discription = change;
    std::cout << "���ࣨ����س���ʾ���޸ģ�\n";
    while (!changeInt(type))
    {
    }
    /* std::getline(std::cin, change);
    if (!change.empty())
        type = std::stoi(change); */
    std::cout << "���ۣ�����س���ʾ���޸ģ�\n";
    while (!changeDouble(price))
    {
    }
    /* std::getline(std::cin, change);
    if (!change.empty())
        price = std::stod(change); */
    std::cout << "����������س���ʾ���޸ģ�\n";
    while (!changeInt(amount))
    {
    }
    /* std::getline(std::cin, change);
    if (!change.empty())
        amount = std::stoi(change); */
    std::cout << "�ۿۣ�����س���ʾ���޸ģ�\n";
    while (1)
    {
        double dis = discount;
        if (changeDouble(dis))
        {
            if (dis > 1.0)
                continue;
            else
            {
                discount = dis;
                break;
            }
        }
    }
    /* std::getline(std::cin, change);
    if (!change.empty())
        discount = std::stod(change); */
    copyInfo(tmp);
    *it = tmp;
}
void Goods::search(std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        // type > st.type�Ϳ���break��
        if (st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����"
                          << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left << "�ۿ�" << std::setw(8)
                          << std::left << "����" << std::setw(20) << std::left << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const std::string &name, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����"
                          << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left << "�ۿ�" << std::setw(8)
                          << std::left << "����" << std::setw(20) << std::left << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const double lowPrice, const double highPrice, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����"
                          << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left << "�ۿ�" << std::setw(8)
                          << std::left << "����" << std::setw(20) << std::left << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const int lowAmount, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= INT_MAX)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(20) << std::left << "����"
                          << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left << "�ۿ�" << std::setw(8)
                          << std::left << "����" << std::setw(20) << std::left << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
            auto vt = std::find(showGoods.begin(), showGoods.end(), st);
            if (vt == showGoods.end())
                showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::atDiscount(const double dis)
{
    int begin = num;
    for (auto &st : goodsInfo)
    {
        if (st.type == type)
        {
            st.discount = dis;
        }
    }
}
void Goods::changeAmountOfGoods(const std::string &name, const std::string &merchant, const int type, const int amount)
{
    GoodsInfo tmp;
    tmp.name = name;
    tmp.merchant = merchant;
    tmp.type = type;
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it == goodsInfo.end())
        std::cout << "fuk\n";
    it->amount -= amount;
}
void Goods::updateInfo(std::vector<std::pair<GoodsInfo, int>> &preorder)
{
    for (auto &vt : preorder)
    {
        auto gt = std::find(goodsInfo.begin(), goodsInfo.end(), vt.first);
        vt.first = *gt;
    }
}
// template <typename T> void Goods::input(T &x, bool mode) const

bool Goods::changeInt(int &type)
{
    std::string tmp;
    std::getline(std::cin, tmp);
    if (tmp.empty())
        return true;
    if (isInt(tmp))
    {
        int t = std::stoi(tmp);
        if (t < 1 || t > 3)
        {
            std::cout << "���벻�Ϸ���û�и�������Ʒ��\n";
            return false;
        }
        type = t;
        return true;
    }
    else
    {
        std::cout << "���벻�Ϸ������������֣�\n";
        return false;
    }
}
bool Goods::changeDouble(double &type)
{
    std::string tmp;
    std::getline(std::cin, tmp);
    if (tmp.empty())
        return true;
    if (isFloat(tmp))
    {
        double t = std::stod(tmp);
        if (t < 0.0)
        {
            std::cout << "���벻�Ϸ���������������\n";
            return false;
        }
        type = t;
        return true;
    }
    else
    {
        std::cout << "���벻�Ϸ������������֣�\n";
        return false;
    }
}
bool Goods::isInt(const std::string &input)
{
    std::regex rx("^[0-9]+$");  //+�ű�ʾ���ƥ��
    return std::regex_match(input, rx);
}
bool Goods::isFloat(const std::string &input)
{
    std::regex rx("^[0-9]+(.[0-9]+)?$");
    return std::regex_match(input, rx);
}
template <typename T> void Goods::input(T &x) const
{
    std::cin >> x;
    /* if (mode)
        if (std::cin.get() == '\n')
            return; */
    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "���벻�Ϸ�������������\n";
        std::cin >> x;
        continue;
    }
}
void Goods::copyInfo(GoodsInfo &des)
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
//���ڻ�û��
double Foods::getPrice(const std::string &name)
{
    return price * discount;
}
double Clothes::getPrice(const std::string &name)
{
    return price * discount;
}
double Books::getPrice(const std::string &name)
{
    return price * discount;
}
