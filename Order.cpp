#include "Order.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// goods可以删除掉
void Order::preAddGoods(std::vector<GoodsInfo> &showGoods)
{
    definiteType();
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
    std::cout << "输入想要购买的商品：\n";
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
            std::cout << "没有该商品，请重新输入商品\n";
        else
            break;
    }
    if (num > 1)
    {
        bool flg = false;
        while (!flg)
        {
            std::cout << "该商品多个商家在售卖，请输入想购买的商家名\n";
            std::cin >> merchant;
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
                std::cout << "没有该商家，请重新输入商家\n";
        }
    }
    if (good.merchant == name)
    {
        std::cout << "不能购买自己的商品，已退出！\n";
        good.name.erase();
    }
}
void Order::chooseAmount(const GoodsInfo &good)
{
    std::cout << "请输入要购买的数量(0表示取消加入购物车)：";
    int number;
    bool can = true;
    while (1)
    {
        input(number);
        if (number > good.amount)
        {
            std::cout << "想要购买的数量超过了最大数量，请重新输入\n";
        }
        else if (number < 0)
        {
            std::cout << "不能买非正数个商品，请重新输入\n";
        }
        else if (number == 0)
        {
            std::cout << "已退出\n";
            break;
        }
        else
        {
            std::cout << "已添加到购物车\n";
            //相同商品只会产生一次记录
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
        std::cout << "购物车已清空！\n";
        return;
    }
    std::cout << "购物车如下：\n";
    std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "现价" << std::setw(8)
              << std::left << "购买数量" << std::setw(20) << std::left << "商家" << std::endl;
    for (auto it : shoppingCart)
    {
        std::cout << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left
                  << it.first.price * it.first.discount << std::setw(8) << std::left << it.second << std::setw(20)
                  << std::left << it.first.merchant << std::endl;
    }
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
            std::cout << "该商品购物车内有多种，请输入想购买的商家名\n";
            std::cin >> merchant;
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
                std::cout << "没有该商家，请重新输入商家\n";
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
        std::cout << "不能修改，已退出！\n";
        return;
    }
    std::string name;
    std::cout << "输入要修改数量的商品:\n";
    std::cin >> name;
    int pos = search(name);
    if (pos == -1)
    {
        std::cout << "没有该商品，已退出\n";
        return;
    }
    std::cout << name << "数量为" << shoppingCart[pos].second << std::endl;
    std::cout << "请输入要修改的数量（正数表示增加，负数表示）";
    int number;
    input(number);
    shoppingCart[pos].second += number;
}
void Order::generateOrder(std::vector<std::pair<GoodsInfo, int>> &finalOrder)
{
    showShoppingCart();
    if (shoppingCart.empty())
        return;
    std::cout << "请输入每种商品要购买的数量\n";
    std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
              << std::left << "购买数量" << std::setw(8) << std::left << "折扣" << std::setw(20) << std::left << "商家"
              << std::endl;
    for (auto it = shoppingCart.begin(); !shoppingCart.empty() && it != shoppingCart.end(); it++)
    {
        int amount;
        bool flg = true;
        std::cout << std::setw(20) << std::left << it->first.name << std::setw(8) << std::left << it->first.price
                  << std::setw(8) << std::left << it->second << std::setw(8) << std::left << it->first.discount
                  << std::setw(20) << std::left << it->first.merchant << std::endl;
        while (flg)
        {
            input(amount);
            if (amount < 0)
                std::cout << "不能购买负数个商品，请重新输入\n";
            else if (amount > it->first.amount)
                std::cout << "商家没有这么多商品，请重新输入\n";
            else if (amount > it->second)
                std::cout << "不能超出购物车内数量，请重新输入\n";
            else
            {
                finalOrder.emplace_back(std::make_pair(it->first, amount));
                if (amount == it->second)
                {
                    shoppingCart.erase(it);
                    preorderGoods(it->first.name, it->first.merchant, amount);
                }
                else
                    it->second -= amount;
                flg = false;
            }
        }
    }
    std::cout << "****************************************************************\n";
    std::cout << "最终订单如下：\n";
    std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
              << std::left << "购买数量" << std::setw(8) << std::left << "折扣" << std::setw(8) << std::left << "总价"
              << std::endl;
    for (auto it : finalOrder)
    {
        double total = it.first.price * it.first.discount * it.second;
        std::cout << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left << it.first.price
                  << std::setw(8) << std::left << it.second << std::setw(8) << std::left << it.first.discount
                  << std::setw(8) << std::left << total << std::endl;
        sum += total;
    }
    std::cout << "所有商品总价格为" << sum << "元\n";
}
double Order::getToatalPrice()
{
    return sum;
}
void Order::clearPrice()
{
    sum = 0;
}
void Order::preorderGoods(const std::string &goodsName, const std::string &merchant, const int amount)
{
    freeGoods();
    goods = new Foods();
    goods->preorderGoods(goodsName, merchant, name, amount);
    freeGoods();
    goods = new Clothes();
    goods->preorderGoods(goodsName, merchant, name, amount);
    freeGoods();
    goods = new Books();
    goods->preorderGoods(goodsName, merchant, name, amount);
    freeGoods();
}
void Order::soldOut()
{
    freeGoods();
    goods = new Foods();
    goods->soldOut(name);
    freeGoods();
    goods = new Clothes();
    goods->soldOut(name);
    freeGoods();
    goods = new Books();
    goods->soldOut(name);
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
        std::cout << "请选择商品类型\n"
                  << "1表示食物，2表示衣服，3表示图书\n";
        input(type);
    }
    while (type < 1 || type > 3)
    {
        std::cout << "没有该类型商品，请重新输入\n";
        input(type);
    }
    freeGoods();
    switch (type)
    {
        case 1:
            goods = new Foods();
            break;
        case 2:
            goods = new Clothes();
            break;
        case 3:
            goods = new Books();
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
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
}