#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Ex1.hpp"

bool AccInfo::operator<(const AccInfo &ac) const
{
    if (this->name == ac.name)
        return false;
    if (this->name < ac.name)
        return true;
    else
        return false;
};

bool GoodsInfo::operator<(const GoodsInfo &go) const
{
    if (this->name == go.name && this->type == go.type)
        return false;
    if (this->type < go.type)
        return true;
    else if (this->type == go.type)
    {
        if (this->name < go.name)
            return true;
        else
            return false;
    }
    else
        return false;
};

bool Account::registerAcc()
{
    accSet[num] = new AccInfo;
    accSet[num]->name = userName;
    auto it = accInfo.find(*accSet[num]);
    if (it != accInfo.end())
        return false;

    std::cout << "Please enter the password:\n";
    std::cin >> accSet[num]->pwd;
    std::cout << "Please enter the type of the account, "
              << "0 for merchants and 1 for customers\n";
    std::cin >> accSet[num]->t;
    accSet[num]->bala = 0;
    accInfo.insert(*accSet[num]);
    std::cout << "Register Succeed!\n";
    num++;
    return true;
}
void Account::changePwd()  // set容器修改元素，先删除再插入
{
    accSet[num] = new AccInfo;
    accSet[num]->name = userName;
    auto it = accInfo.find(*accSet[num]);
    if (it == accInfo.end())
    {
        std::cout << "This account doesn't exist.";
        delete accSet[num];
        return;
    }
    accSet[num]->bala = it->bala;
    accSet[num]->t = it->t;
    // accSet[num]并未释放掉
    accInfo.erase(it);
    std::cout << "Please enter the new password:\n";
    std::cin >> accSet[num]->pwd;
    accInfo.insert(*accSet[num]);
    num++;
}

void Goods::addItems()
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = name;
    auto it = goodsInfo.find(*goodSet[num]);
    if (it != goodsInfo.end())
    {
        std::cout << "This account has existed.\n";
        delete goodSet[num];
        return;
    }
    //更改为用户可选修改哪些内容
    std::cout << "Please enter the new type, new name, new amount, new price, new discount:\n";
    std::cin >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price >>
        goodSet[num]->discount;

    goodsInfo.insert(*goodSet[num]);
    num++;
}
void Goods::changeItems()
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = name;
    auto it = goodsInfo.find(*goodSet[num]);
    if (it == goodsInfo.end())
    {
        std::cout << "This account hasn't existed.";
        delete goodSet[num];
        return;
    }
    // goodSet[num]并未释放掉
    goodsInfo.erase(it);
    //更改为用户可选修改哪些内容
    std::cout << "Please enter the new type, new name, new amount, new price:\n";
    std::cin >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price;

    goodsInfo.insert(*goodSet[num]);
    num++;
}
void Goods::search(const std::string &name)
{
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.type == type)
        {
            std::cout << st.name << " " << st.amount << " " << st.price << std::endl;
        }
    }
}
void Goods::search(const double lowPrice, const double highPrice)
{
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            std::cout << st.name << " " << st.amount << " " << st.price << " " << st.discount << std::endl;
        }
    }
}
void Goods::search(const int lowAmount, const int highAmount)
{
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= highAmount)
        {
            std::cout << st.name << " " << st.amount << " " << st.price << std::endl;
        }
    }
}
void Goods::discount(const int dis)
{
    for (auto st : goodsInfo)
    {
        if (st.type == type)
        {
            st.discount = dis;
        }
    }
}

double Foods::getPrice()
{
    GoodsInfo tmp;
    tmp.name = name;
    tmp.type = type;
    auto st = goodsInfo.find(tmp);
    return st->price * st->discount;
}
double Clothes::getPrice()
{
    GoodsInfo tmp;
    tmp.name = name;
    auto st = goodsInfo.find(tmp);
    return st->price * st->discount;
}
double Books::getPrice()
{
    GoodsInfo tmp;
    tmp.name = name;
    auto st = goodsInfo.find(tmp);
    return st->price * st->discount;
}
