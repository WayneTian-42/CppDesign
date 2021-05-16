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
    //����Ϊ�û���ѡ�޸���Щ����
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
    // goodSet[num]��δ�ͷŵ�
    goodsInfo.erase(it);
    //����Ϊ�û���ѡ�޸���Щ����
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
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "����" << std::setw(8)
                          << std::left << "�۸�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const std::string &name)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.name == name && st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "����" << std::setw(8)
                          << std::left << "�۸�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const double lowPrice, const double highPrice)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.price * st.discount >= lowPrice && st.price * st.discount <= highPrice)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "����" << std::setw(8)
                          << std::left << "�۸�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const int lowAmount, const int highAmount)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= highAmount)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "����" << std::setw(8)
                          << std::left << "�۸�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
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
