#include "Goods.hpp"
#include <iostream>

bool GoodsInfo::operator<(const GoodsInfo &go) const
{
    if (name == go.name && type == go.type && merchant == go.merchant)
        return false;
    if (type != go.type)
        return type < go.type;
    else if (name != go.name)
        return name < go.name;
    else
        return merchant < go.merchant;
};

void Goods::addItems(const std::string &goodsName, const std::string &merchant)
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = goodsName;
    goodSet[num]->type = type;
    auto it = goodsInfo.find(*goodSet[num]);
    if (it != goodsInfo.end())
    {
        std::cout << "����Ʒ�Ѵ���\n";
        delete goodSet[num];
        return;
    }
    //����Ϊ�û���ѡ�޸���Щ����
    std::cout << "Please enter the new type, new name, new amount, new price, new discount:\n";
    std::cin >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price >>
        goodSet[num]->discount;
    goodSet[num]->merchant = merchant;
    goodsInfo.insert(*goodSet[num]);
    num++;
}
//�ĳɰѸ��̼���Ʒȫ����ʾ
void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = goodsName;
    goodSet[num]->type = type;
    goodSet[num]->merchant = merchant;
    auto it = goodsInfo.find(*goodSet[num]);
    if (it == goodsInfo.end())
    {
        std::cout << "����Ʒ������" << std::endl;
        delete goodSet[num];
        return;
    }
    if (it->merchant != merchant)
    {
        std::cout << "����Ʒ�������̼�" << merchant << std::endl;
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
void Goods::search(std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        // type > st.type�Ϳ���break��
        if (st.type == type)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "����" << std::setw(8)
                          << std::left << "�۸�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const std::string &name, std::vector<GoodsInfo> &showGoods)
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
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const double lowPrice, const double highPrice, std::vector<GoodsInfo> &showGoods)
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
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::search(const int lowAmount, std::vector<GoodsInfo> &showGoods)
{
    int flg = 0;
    for (auto st : goodsInfo)
    {
        if (st.type == type && st.amount >= lowAmount && st.amount <= INT_MAX)
        {
            if (!flg)
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "����" << std::setw(8)
                          << std::left << "�۸�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.amount << std::setw(8)
                      << std::left << st.price << std::endl;
            showGoods.emplace_back(st);
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
void Goods::solodOut(const std::string &gname, const std::string &merchant, const int amount)
{
    goodSet[num] = new GoodsInfo;
    goodSet[num]->name = gname;
    goodSet[num]->type = type;
    goodSet[num]->merchant = merchant;
    auto it = goodsInfo.find(*goodSet[num]);
    goodSet[num]->price = it->price;
    goodSet[num]->amount = it->amount;
    goodsInfo.erase(it);
    goodSet[num]->amount -= amount;
    goodsInfo.insert(*goodSet[num]);
    num++;
}

double Foods::getPrice(const std::string &name)
{
    GoodsInfo tmp;
    tmp.name = name;
    tmp.type = type;
    tmp.merchant = merchant;
    auto st = goodsInfo.find(tmp);
    return st->price * st->discount;
}
double Clothes::getPrice(const std::string &name)
{
    GoodsInfo tmp;
    tmp.name = name;
    tmp.merchant = merchant;
    auto st = goodsInfo.find(tmp);
    return st->price * st->discount;
}
double Books::getPrice(const std::string &name)
{
    GoodsInfo tmp;
    tmp.name = name;
    tmp.merchant = merchant;
    auto st = goodsInfo.find(tmp);
    return st->price * st->discount;
}
