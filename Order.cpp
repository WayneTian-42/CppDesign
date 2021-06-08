#include "Order.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// goods可以删除掉
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
    // showGoods.erase(); 引用不能清空
}
//修改查找策略
void Order::chooseGoods(std::vector<GoodsInfo> &showGoods, GoodsInfo &good)
{
    std::string gname, merchant;
    output << "输入想要购买的商品：\n";
    server->sendMessage(output);
    int flg = 1, num = 0;
    while (1)
    {
        std::cin >> gname;
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
            output << "没有该商品，请重新输入商品\n";
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
            output << "该商品多个商家在售卖，请输入想购买的商家名\n";
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
                output << "没有该商家，请重新输入商家\n";
                server->sendMessage(output);
            }
        }
    }
    if (good.merchant == name)
    {
        output << "不能购买自己的商品，已退出！\n";
        server->sendMessage(output);
        good.name.erase();
    }
}
void Order::chooseAmount(const GoodsInfo &good)
{
    output << "请输入要购买的数量(0表示取消加入购物车)：";
    server->sendMessage(output);
    int number;
    bool can = true;
    while (1)
    {
        // input(number);
        std::string buff;
        server->recvMessage(buff);
        number = std::stoi(buff);
        if (number > good.amount)
        {
            output << "想要购买的数量超过了最大数量，请重新输入\n";
        }
        else if (number < 0)
        {
            output << "不能买非正数个商品，请重新输入\n";
        }
        else if (number == 0)
        {
            output << "已退出\n";
            break;
        }
        else
        {
            output << "已添加到购物车\n";
            //相同商品只会产生一次记录
            addGoods(good, number);
            break;
        }
        server->sendMessage(output);
    }
}
void Order::addGoods(const GoodsInfo &good, const int num)
{
    bool flg = true;
    for (auto &it : shoppingCart)
    {
        // 种类
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
        output << "购物车已清空！\n";
        server->sendMessage(output);
        return;
    }
    output << "购物车如下：\n";
    output << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "现价" << std::setw(8) << std::left
           << "购买数量" << std::setw(20) << std::left << "商家" << std::endl;
    for (auto it : shoppingCart)
    {
        output << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left
               << it.first.price * it.first.discount << std::setw(8) << std::left << it.second << std::setw(20)
               << std::left << it.first.merchant << std::endl;
    }
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
        while (!flg)
        {
            std::string merchant;
            output << "该商品购物车内有多种，请输入想购买的商家名\n";
            server->sendMessage(output);
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
                output << "没有该商家，请重新输入商家\n";
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
        output << "不能修改，已退出！\n";
        server->sendMessage(output);
        return;
    }
    std::string name;
    output << "输入要修改数量的商品:\n";
    server->sendMessage(output);
    // std::cin >> name;
    server->recvMessage(name);
    int pos = search(name);
    if (pos == -1)
    {
        output << "没有该商品，已退出\n";
        server->sendMessage(output);
        return;
    }
    output << name << "数量为" << shoppingCart[pos].second << std::endl;
    output << "请输入要修改的数量（正数表示增加，负数表示）";
    server->sendMessage(output);
    int number;
    // input(number);
    std::string buff;
    server->recvMessage(buff);
    number = std::stoi(buff);
    shoppingCart[pos].second += number;
}
void Order::generateOrder(std::vector<std::pair<GoodsInfo, int>> &finalOrder, std::vector<GoodsInfo> &goodsInfo)
{
    showShoppingCart();
    if (shoppingCart.empty())
        return;
    output << "请输入每种商品要购买的数量\n";
    output << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8) << std::left
           << "购买数量" << std::setw(8) << std::left << "折扣" << std::setw(20) << std::left << "商家" << std::endl;
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
            // input(amount);
            std::string buff;
            server->recvMessage(buff);
            amount = std::stoi(buff);
            if (amount < 0)
            {
                output << "不能购买负数个商品，请重新输入\n";
                server->sendMessage(output);
            }
            else if (amount > it->first.amount)
            {
                output << "商家没有这么多商品，请重新输入\n";
                server->sendMessage(output);
            }
            else if (amount > it->second)
            {
                output << "不能超出购物车内数量，请重新输入\n";
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
    output << "最终订单如下：\n";
    output << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8) << std::left
           << "购买数量" << std::setw(8) << std::left << "折扣" << std::setw(8) << std::left << "总价" << std::endl;
    for (auto it : finalOrder)
    {
        double total = it.first.price * it.first.discount * it.second;
        output << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left << it.first.price
               << std::setw(8) << std::left << it.second << std::setw(8) << std::left << it.first.discount
               << std::setw(8) << std::left << total << std::endl;
        sum += total;
    }
    output << "所有商品总价格为" << sum << "元\n";
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
    if (!type)
    {
        output << "请选择商品类型\n"
               << "1表示食物，2表示衣服，3表示图书\n";
        input(type);
    }
    while (type < 1 || type > 3)
    {
        output << "没有该类型商品，请重新输入\n";
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
template <typename T> void Order::input(T &x) const
{
    std::cin >> x;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
}