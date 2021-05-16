#include "Goods.hpp"
#include <iostream>

bool GoodsInfo::operator<(const GoodsInfo &go) const
{
    if (name == go.name && type == go.type)
        return false;
    if (type != go.type)
        return type < go.type;
    else
        return name < go.name;
};

void Goods::addItems(const std::string &goodsName, const std::string &merchant)
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = goodsName;
    goodSet[num]->type = type;
    auto it = goodsInfo.find(*goodSet[num]);
    if (it != goodsInfo.end())
    {
        std::cout << "该商品已存在\n";
        delete goodSet[num];
        return;
    }
    //更改为用户可选修改哪些内容
    std::cout << "Please enter the new type, new name, new amount, new price, new discount:\n";
    std::cin >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price >>
        goodSet[num]->discount;
    goodSet[num]->merchant = merchant;
    goodsInfo.insert(*goodSet[num]);
    num++;
}
//改成把该商家商品全部显示
void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = goodsName;
    goodSet[num]->type = type;
    auto it = goodsInfo.find(*goodSet[num]);
    if (it == goodsInfo.end())
    {
        std::cout << "该商品不存在" << std::endl;
        delete goodSet[num];
        return;
    }
    if (it->merchant != merchant)
    {
        std::cout << "该商品不属于商家" << merchant << std::endl;
        delete goodSet[num];
        return;
    }
    // goodSet[num]并未释放掉
    goodsInfo.erase(it);
    //更改为用户可选修改哪些内容
    std::cout << "Please enter the new type, new name, new amount, new price:\n";
    std::cin >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price >>
        goodSet[num]->merchant;

    goodsInfo.insert(*goodSet[num]);
    num++;
}
void Goods::search()
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "数量" << std::setw(8)
                          << std::left << "价格" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
}
void Goods::search(const std::string &name)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "数量" << std::setw(8)
                          << std::left << "价格" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
}
void Goods::search(const double lowPrice, const double highPrice)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "数量" << std::setw(8)
                          << std::left << "价格" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
}
void Goods::search(const int lowAmount, const int highAmount)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= highAmount)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "数量" << std::setw(8)
                          << std::left << "价格" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "没有满足要求的商品，请更换筛选条件。\n";
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
