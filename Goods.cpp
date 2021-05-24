#include "Goods.hpp"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>

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
        std::cout << "该商品已存在\n";
        return;
    }

    std::cout << "请输入商品单价\n";
    input(price);
    std::cout << "请输入商品数量\n";
    input(amount);
    std::cout << "请输入商品折扣\n";
    input(discount);
    copyInfo(tmp);
    goodsInfo.emplace_back(tmp);
}
//改成把该商家商品全部显示
void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    name = goodsName;
    this->merchant = merchant;
    GoodsInfo tmp;
    copyInfo(tmp);
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it == goodsInfo.end())
    {
        std::cout << "该商品不存在" << std::endl;
        return;
    }
    if (it->merchant != merchant)
    {
        std::cout << "该商品不属于商家" << merchant << std::endl;
        return;
    }
    copyInfo(it);
    //更改为用户可选修改哪些内容，没有检测非法输入
    getchar();
    std::string change;
    std::cout << "请修改商品信息：\n"
              << "名称（输入回车表示不修改）\n";
    std::getline(std::cin, change);
    if (!change.empty())
        name = change;
    int temp;
    double temp2;
    std::cout << "种类（输入回车表示不修改）\n";
    temp = type;
    input(temp, true);
    type = temp;
    std::cout << "单价（输入回车表示不修改）\n";
    temp2 = price;
    input(temp2, true);
    price = temp2;
    std::cout << "数量（输入回车表示不修改）\n";
    temp = amount;
    input(temp, true);
    amount = temp;
    std::cout << "折扣（输入回车表示不修改）\n";
    temp2 = discount;
    input(temp2, true);
    discount = temp2;
    copyInfo(tmp);
    *it = tmp;
}
void Goods::search(std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        // type > st.type就可以break了
        if (st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
                          << std::left << "折扣" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left
                          << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
}
void Goods::search(const std::string &name, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
                          << std::left << "折扣" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left
                          << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
}
void Goods::search(const double lowPrice, const double highPrice, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
                          << std::left << "折扣" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left
                          << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
}
void Goods::search(const int lowAmount, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= INT_MAX)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
                          << std::left << "折扣" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left
                          << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
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

template <typename T> void Goods::input(T &x, bool mode) const
{
    std::cin >> x;
    if (mode)
        if (std::cin.get() == '\n')
            return;
    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
}
void Goods::copyInfo(GoodsInfo &des)
{
    des.name = name;
    des.merchant = merchant;
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
}
//现在还没用
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
