#include "Order.hpp"
#include <iostream>
#include <string>
#include <utility>
#include <vector>

// goods����ɾ����
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
    // showGoods.erase(); ���ò������
}
//�޸Ĳ��Ҳ���
void Order::chooseGoods(std::vector<GoodsInfo> &showGoods, GoodsInfo &good)
{
    std::string gname, merchant;
    std::cout << "������Ҫ�������Ʒ��\n";
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
            std::cout << "û�и���Ʒ��������������Ʒ\n";
        else
            break;
    }
    if (num > 1)
    {
        bool flg = false;
        while (!flg)
        {
            std::cout << "����Ʒ����̼����������������빺����̼���\n";
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
                std::cout << "û�и��̼ң������������̼�\n";
        }
    }
    if (good.merchant == name)
    {
        std::cout << "���ܹ����Լ�����Ʒ�����˳���\n";
        good.name.erase();
    }
}
void Order::chooseAmount(const GoodsInfo &good)
{
    std::cout << "������Ҫ���������(0��ʾȡ�����빺�ﳵ)��";
    int number;
    bool can = true;
    while (1)
    {
        input(number);
        if (number > good.amount)
        {
            std::cout << "��Ҫ����������������������������������\n";
        }
        else if (number < 0)
        {
            std::cout << "���������������Ʒ������������\n";
        }
        else if (number == 0)
        {
            std::cout << "���˳�\n";
            break;
        }
        else
        {
            std::cout << "����ӵ����ﳵ\n";
            //��ͬ��Ʒֻ�����һ�μ�¼
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
        std::cout << "���ﳵ����գ�\n";
        return;
    }
    std::cout << "���ﳵ���£�\n";
    std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�ּ�" << std::setw(8)
              << std::left << "��������" << std::setw(20) << std::left << "�̼�" << std::endl;
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
            std::cout << "����Ʒ���ﳵ���ж��֣��������빺����̼���\n";
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
                std::cout << "û�и��̼ң������������̼�\n";
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
        std::cout << "�����޸ģ����˳���\n";
        return;
    }
    std::string name;
    std::cout << "����Ҫ�޸���������Ʒ:\n";
    std::cin >> name;
    int pos = search(name);
    if (pos == -1)
    {
        std::cout << "û�и���Ʒ�����˳�\n";
        return;
    }
    std::cout << name << "����Ϊ" << shoppingCart[pos].second << std::endl;
    std::cout << "������Ҫ�޸ĵ�������������ʾ���ӣ�������ʾ��";
    int number;
    input(number);
    shoppingCart[pos].second += number;
}
void Order::generateOrder(std::vector<std::pair<GoodsInfo, int>> &finalOrder)
{
    showShoppingCart();
    if (shoppingCart.empty())
        return;
    std::cout << "������ÿ����ƷҪ���������\n";
    std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
              << std::left << "��������" << std::setw(8) << std::left << "�ۿ�" << std::setw(20) << std::left << "�̼�"
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
                std::cout << "���ܹ���������Ʒ������������\n";
            else if (amount > it->first.amount)
                std::cout << "�̼�û����ô����Ʒ������������\n";
            else if (amount > it->second)
                std::cout << "���ܳ������ﳵ������������������\n";
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
    std::cout << "���ն������£�\n";
    std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
              << std::left << "��������" << std::setw(8) << std::left << "�ۿ�" << std::setw(8) << std::left << "�ܼ�"
              << std::endl;
    for (auto it : finalOrder)
    {
        double total = it.first.price * it.first.discount * it.second;
        std::cout << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left << it.first.price
                  << std::setw(8) << std::left << it.second << std::setw(8) << std::left << it.first.discount
                  << std::setw(8) << std::left << total << std::endl;
        sum += total;
    }
    std::cout << "������Ʒ�ܼ۸�Ϊ" << sum << "Ԫ\n";
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
        std::cout << "��ѡ����Ʒ����\n"
                  << "1��ʾʳ�2��ʾ�·���3��ʾͼ��\n";
        input(type);
    }
    while (type < 1 || type > 3)
    {
        std::cout << "û�и�������Ʒ������������\n";
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
        std::cout << "���벻�Ϸ�������������\n";
        std::cin >> x;
        continue;
    }
}