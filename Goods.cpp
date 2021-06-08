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
        output << "该商品已存在\n";
        server->sendMessage(output);
        return;
    }
    output << "请输入商品描述\n";
    server->sendMessage(output);
    // std::cin >> discription;
    server->recvMessage(discription);
    output << "请输入商品单价\n";
    server->sendMessage(output);

    std::string buff;
    while (1)
    {
        // input(price);
        server->recvMessage(buff);
        price = std::stoi(buff);
        if (price > 0)
            break;
        else
        {
            output << "请重新输入一个正数！\n";
            server->sendMessage(output);
        }
    }
    output << "请输入商品数量\n";
    server->sendMessage(output);
    while (1)
    {
        // input(amount);
        server->recvMessage(buff);
        amount = std::stoi(buff);
        if (amount > 0)
            break;
        else
        {
            output << "请重新输入一个正数！\n";
            server->sendMessage(output);
        }
    }
    output << "请输入商品折扣\n";
    server->sendMessage(output);
    while (1)
    {
        // input(discount);
        server->recvMessage(buff);
        discount = std::stod(buff);
        if (discount > 0 && discount <= 1)
            break;
        else
        {
            output << "请重新输入一个0至1之间的数！\n";
            server->sendMessage(output);
        }
    }
    output << "添加成功！\n";
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
    copyInfo(tmp);  // 当前信息拷贝到tmp中，然后查找
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it == goodsInfo.end())
    {
        output << "该商品不存在" << std::endl;
        server->sendMessage(output);
        return;
    }
    if (it->merchant != merchant)
    {
        output << "该商品不属于商家" << merchant << std::endl;
        server->sendMessage(output);
        return;
    }
    copyInfo(it);
    getchar();  // 读入上一次输入的回车，防止干扰下面的输入
    std::string change;
    output << "请修改商品信息：\n"
           << "名称（输入回车表示不修改）\n";
    server->sendMessage(output);
    // std::getline(std::cin, change);
    server->recvMessage(change);
    if (!change.empty())
        name = change;
    output << "描述（输入回车表示不修改）\n";
    server->sendMessage(output);
    // std::getline(std::cin, change);
    server->recvMessage(change);
    if (!change.empty())
        discription = change;
    output << "种类（输入回车表示不修改）\n";
    server->sendMessage(output);
    while (1)
    {
        int t = type;
        if (changeInt(t))
        {
            if (t > 3 || t < 1)
            {
                output << "没有该种类商品，请重新输入\n";
                continue;
            }
            else
            {
                type = t;
                break;
            }
        }
    }
    output << "单价（输入回车表示不修改）\n";
    server->sendMessage(output);
    while (!changeDouble(price))
    {
    }
    output << "数量（输入回车表示不修改）\n";
    server->sendMessage(output);
    while (!changeInt(amount))
    {
    }
    output << "折扣（输入回车表示不修改）\n";
    server->sendMessage(output);
    while (1)
    {
        double dis = discount;
        if (changeDouble(dis))
        {
            if (dis > 1.0)
            {
                output << "折扣不合理，请重新输入\n";
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
            int sum = 0;
            for (auto mt : st.sold)
                sum += mt.second;
            // 格式化输出
            if (!flg)
                output << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述" << std::setw(8)
                       << std::left << "原价" << std::setw(8) << std::left << "折扣" << std::setw(8) << std::left
                       << "现价" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left << "商家"
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
        output << "没有满足要求的商品，请更换筛选条件。\n";
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
                output << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述" << std::setw(8)
                       << std::left << "原价" << std::setw(8) << std::left << "折扣" << std::setw(8) << std::left
                       << "现价" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left << "商家"
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
        output << "没有满足要求的商品，请更换筛选条件。\n";
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
                output << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述" << std::setw(8)
                       << std::left << "原价" << std::setw(8) << std::left << "折扣" << std::setw(8) << std::left
                       << "现价" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left << "商家"
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
        output << "没有满足要求的商品，请更换筛选条件。\n";
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
                output << std::setw(20) << std::left << "名称" << std::setw(20) << std::left << "描述" << std::setw(8)
                       << std::left << "原价" << std::setw(8) << std::left << "折扣" << std::setw(8) << std::left
                       << "现价" << std::setw(8) << std::left << "数量" << std::setw(20) << std::left << "商家"
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
        output << "没有满足要求的商品，请更换筛选条件。\n";
    server->sendMessage(output);
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
void Goods::updateInfo(std::vector<std::pair<GoodsInfo, int>> &preorder)
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
    if (tmp.empty())
        return true;
    if (isInt(tmp))
    {
        int t = std::stoi(tmp);
        /* if (t < 0)
        {
            output << "输入不合法，请输入正数！\n";
            return false;
        } */
        number = t;
        return true;
    }
    else
    {
        output << "输入不合法，请输入正数！\n";
        server->sendMessage(output);
        return false;
    }
}
bool Goods::changeDouble(double &number)
{
    std::string tmp;
    // std::getline(std::cin, tmp);
    server->recvMessage(tmp);
    if (tmp.empty())
        return true;
    if (isFloat(tmp))
    {
        double t = std::stod(tmp);
        /* if (t < 0.0)
        {
            output << "输入不合法，请输入正数！\n";
            return false;
        } */
        number = t;
        return true;
    }
    else
    {
        output << "输入不合法，请输入数字！\n";
        server->sendMessage(output);
        return false;
    }
}
bool Goods::isInt(const std::string &input) const
{
    std::regex rx("^[0-9]+$");  //+号表示多次匹配
    return std::regex_match(input, rx);
}
bool Goods::isFloat(const std::string &input) const
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
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
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
