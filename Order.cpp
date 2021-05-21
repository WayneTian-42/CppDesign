#include "Order.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

void Order::preAddGoods(std::vector<GoodsInfo> &showGoods, int type)
{
    definiteType(type);
    if (!type)
        goods->search(showGoods);
    GoodsInfo good;
    chooseGoods(showGoods, good);
    chooseAmount(good);
}
//修改查找策略
void Order::chooseGoods(std::vector<GoodsInfo> &showGoods, GoodsInfo &good)
{
    std::cout << "输入购买的商品名称：\n";
    std::string gname, merchant;
    std::cout << "输入想要购买的货物：\n";
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
}
void Order::chooseAmount(const GoodsInfo &good)
{
    std::cout << "请输入要购买的数量(0表示取消加入购物车)：";
    int number;
    bool can = true;
    input(number);
    while (1)
    {
        if (number > good.amount)
        {
            std::cout << "想要购买的数量超过了最大数量！";
        }
        else if (number < 0)
        {
            std::cout << "不能买非正数个商品";
        }
        else if (number == 0)
        {
            std::cout << "已退出\n";
            break;
        }
        else
        {
            std::cout << "已添加到购物车\n";
            preorder.emplace_back(std::make_pair(good, number));
            break;
        }
    }
}
void Order::showOrder()
{
    if (preorder.empty())
    {
        std::cout << "购物车已清空！\n";
        return;
    }
    std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
              << std::left << "数量" << std::setw(8) << std::left << "折扣" << std::setw(20) << std::left << "商家"
              << std::endl;
    for (auto it : preorder)
    {
        std::cout << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left << it.first.price
                  << std::setw(8) << std::left << it.second << std::setw(8) << std::left << it.first.discount
                  << std::setw(20) << std::left << it.first.merchant << std::endl;
    }
}
int Order::search(const std::string &name)
{
    int pos;
    std::vector<int> num;
    for (int i = 0; i < preorder.size(); i++)
    {
        if (preorder[i].first.name == name)
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
                if (preorder[num[i]].first.merchant == merchant)
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
    definiteType(0);
    showOrder();
    std::string name;
    std::cout << "输入要修改数量的商品:\n";
    std::cin >> name;
    int pos = search(name);
    if (pos == -1)
    {
        std::cout << "没有该商品，已退出\n";
        return;
    }
    std::cout << name << "数量为" << preorder[pos].second << std::endl;
}

void Order::definiteType(int type)
{
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