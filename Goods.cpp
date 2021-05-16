#include "Goods.hpp"

bool GoodsInfo::operator<(const GoodsInfo &go) const
{
    if (name == go.name && type == go.type)
        return false;
    if (type != go.type)
        return type < go.type;
    else
        return name < go.name;
};

void Goods::addItems()
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = name;
    goodSet[num]->type = type;
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
        goodSet[num]->discount >> goodSet[num]->merchant;

    goodsInfo.insert(*goodSet[num]);
    num++;
}
void Goods::changeItems()
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = name;
    goodSet[num]->type = type;
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
    std::cin >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price >>
        goodSet[num]->merchant;

    goodsInfo.insert(*goodSet[num]);
    num++;
}
void Goods::search()
{
    for (auto st : goodsInfo)
    {
        if (st.type == type)
        {
            std::cout << st.name << " " << st.amount << " " << st.price << std::endl;
        }
    }
}
void Goods::search(const std::string &name)
{
    for (auto st : goodsInfo)
    {
        if (st.name == name)
        {
            std::cout << st.name << " " << st.amount << " " << st.price << std::endl;
        }
    }
}
void Goods::search(const double lowPrice, const double highPrice)
{
    for (auto st : goodsInfo)
    {
        if (st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            std::cout << st.name << " " << st.amount << " " << st.price << " " << st.discount << std::endl;
        }
    }
}
void Goods::search(const int lowAmount, const int highAmount)
{
    for (auto st : goodsInfo)
    {
        if (st.amount >= lowAmount && st.amount <= highAmount)
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
