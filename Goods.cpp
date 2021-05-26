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
        std::cout << "该商品已存在\n";
        return;
    }
    std::cout << "请输入商品描述\n";
    std::cin >> discount;
    std::cout << "请输入商品单价\n";
    while (1)
    {
        input(price);
        if (price > 0)
            break;
        else
            std::cout << "请重新输入一个正数！\n";
    }
    std::cout << "请输入商品数量\n";
    while (1)
    {
        input(amount);
        if (amount > 0)
            break;
        else
            std::cout << "请重新输入一个正数！\n";
    }
    std::cout << "请输入商品折扣\n";
    while (1)
    {
        input(discount);
        if (discount > 0)
            break;
        else
            std::cout << "请重新输入一个正数！\n";
    }
    copyInfo(tmp);
    goodsInfo.emplace_back(tmp);
}

void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    name = goodsName;
    this->merchant = merchant;
    GoodsInfo tmp;
    copyInfo(tmp);  // 当前信息拷贝到tmp中，然后查找
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
    getchar();  // 读入上一次输入的回车，防止干扰下面的输入
    std::string change;
    std::cout << "请修改商品信息：\n"
              << "名称（输入回车表示不修改）\n";
    std::getline(std::cin, change);
    if (!change.empty())
        name = change;
    std::cout << "描述（输入回车表示不修改）\n";
    std::getline(std::cin, change);
    if (!change.empty())
        discription = change;
    std::cout << "种类（输入回车表示不修改）\n";
    while (1)
    {
        int t = type;
        if (changeInt(t))
        {
            if (t > 3 || t < 1)
            {
                std::cout << "没有该种类商品，请重新输入\n";
                continue;
            }
            else
            {
                type = t;
                break;
            }
        }
    }
    std::cout << "单价（输入回车表示不修改）\n";
    while (!changeDouble(price))
    {
    }
    std::cout << "数量（输入回车表示不修改）\n";
    while (!changeInt(amount))
    {
    }
    std::cout << "折扣（输入回车表示不修改）\n";
    while (1)
    {
        double dis = discount;
        if (changeDouble(dis))
        {
            if (dis > 1.0)
            {
                std::cout << "折扣不合理，请重新输入\n";
                continue;
            }
            else
            {
                discount = dis;
                break;
            }
        }
    }
    copyInfo(tmp);  //将内容更新回数组
    *it = tmp;
}
void Goods::search(std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type)
        {
            // 格式化输出
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述"
                          << std::setw(8) << std::left << "价格" << std::setw(8) << std::left << "折扣" << std::setw(8)
                          << std::left << "数量" << std::setw(20) << std::left << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
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
                std::cout << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述"
                          << std::setw(8) << std::left << "价格" << std::setw(8) << std::left << "折扣" << std::setw(8)
                          << std::left << "数量" << std::setw(20) << std::left << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
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
                std::cout << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述"
                          << std::setw(8) << std::left << "价格" << std::setw(8) << std::left << "折扣" << std::setw(8)
                          << std::left << "数量" << std::setw(20) << std::left << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
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
                std::cout << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述"
                          << std::setw(8) << std::left << "价格" << std::setw(8) << std::left << "折扣" << std::setw(8)
                          << std::left << "数量" << std::setw(20) << std::left << "商家" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(20) << std::left << st.discription
                      << std::setw(8) << std::left << st.price << std::setw(8) << std::left << st.discount
                      << std::setw(8) << std::left << st.amount << std::setw(20) << std::left << st.merchant
                      << std::endl;
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
        if (st.type == type)
            st.discount = dis;
}

bool Goods::changeInt(int &number)
{
    std::string tmp;
    std::getline(std::cin, tmp);
    if (tmp.empty())
        return true;
    if (isInt(tmp))
    {
        int t = std::stoi(tmp);
        /* if (t < 0)
        {
            std::cout << "输入不合法，请输入正数！\n";
            return false;
        } */
        number = t;
        return true;
    }
    else
    {
        std::cout << "输入不合法，请输入正数！\n";
        return false;
    }
}
bool Goods::changeDouble(double &number)
{
    std::string tmp;
    std::getline(std::cin, tmp);
    if (tmp.empty())
        return true;
    if (isFloat(tmp))
    {
        double t = std::stod(tmp);
        /* if (t < 0.0)
        {
            std::cout << "输入不合法，请输入正数！\n";
            return false;
        } */
        number = t;
        return true;
    }
    else
    {
        std::cout << "输入不合法，请输入数字！\n";
        return false;
    }
}
bool Goods::isInt(const std::string &input)
{
    std::regex rx("^[0-9]+$");  //+号表示多次匹配
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
    while (std::cin.fail())
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
//现在还没用
double Foods::getPrice()
{
    return price * discount;
}
double Clothes::getPrice()
{
    return price * discount;
}
double Books::getPrice()
{
    return price * discount;
}
