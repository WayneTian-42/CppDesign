#include "Goods.hpp"
#include <algorithm>
#include <iostream>
#include <string>

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
        std::cout << "����Ʒ�Ѵ���\n";
        return;
    }

    std::cout << "��������Ʒ����\n";
    input(price);
    std::cout << "��������Ʒ����\n";
    input(amount);
    std::cout << "��������Ʒ�ۿ�\n";
    input(discount);
    copyInfo(tmp);
    goodsInfo.emplace_back(tmp);
}
//�ĳɰѸ��̼���Ʒȫ����ʾ
void Goods::changeItems(const std::string &goodsName, const std::string &merchant)
{
    name = goodsName;
    this->merchant = merchant;
    GoodsInfo tmp;
    copyInfo(tmp);
    auto it = std::find(goodsInfo.begin(), goodsInfo.end(), tmp);
    if (it == goodsInfo.end())
    {
        std::cout << "����Ʒ������" << std::endl;
        return;
    }
    if (it->merchant != merchant)
    {
        std::cout << "����Ʒ�������̼�" << merchant << std::endl;
        return;
    }
    //����Ϊ�û���ѡ�޸���Щ���ݣ�û�м��Ƿ�����
    std::string change;
    std::cout << "���޸���Ʒ��Ϣ��\n"
              << "���ƣ�����س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.size())
        name = change;
    std::cout << "���ࣨ����س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.size())
        type = std::stoi(change);
    std::cout << "���ۣ�����س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.size())
        price = std::stod(change);
    std::cout << "����������س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.size())
        amount = std::stoi(change);
    std::cout << "�ۿۣ�����س���ʾ���޸ģ�\n";
    std::getline(std::cin, change);
    if (!change.size())
        discount = std::stod(change);
    copyInfo(tmp);
    *it = tmp;
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
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
                          << std::left << "�ۿ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left
                          << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
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
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
                          << std::left << "�ۿ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left
                          << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
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
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
                          << std::left << "�ۿ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left
                          << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
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
                std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
                          << std::left << "�ۿ�" << std::setw(8) << std::left << "����" << std::setw(20) << std::left
                          << "�̼�" << std::endl;
            flg++;
            std::cout << std::setw(20) << std::left << st.name << std::setw(8) << std::left << st.price << std::setw(8)
                      << std::left << st.discount << std::setw(8) << std::left << st.amount << std::setw(20)
                      << std::left << st.merchant << std::endl;
            showGoods.emplace_back(st);
        }
    }
    if (!flg)
        std::cout << "û������Ҫ�����Ʒ�������ɸѡ������\n";
}
void Goods::atDiscount(const double dis)
{
    int begin = num;
    for (auto &st : goodsInfo)
    {
        if (st.type == type)
        {
            st.discount = dis;
        }
    }
}
/* void Goods::solodOut(const std::string &gname, const std::string &merchant, const int amount)
{
    GoodsInfo tmp;

    tmp.name = gname;
    tmp.type = type;
    tmp.merchant = merchant;
    auto it = goodsInfo.find(*goodSet[num]);
    tmp.price = it->price;
    tmp.amount = it->amount;
    goodsInfo.erase(it);
    tmp.amount -= amount;
    goodsInfo.insert(*goodSet[num]);
    num++;
} */
template <typename T> void Goods::input(T &x) const
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
void Goods::copyInfo(GoodsInfo &des)
{
    des.name = name;
    des.merchant = merchant;
    des.type = type;
    des.amount = amount;
    des.price = price;
    des.discount = discount;
}

double Foods::getPrice(const std::string &name)
{
    return price * discount;
}
double Clothes::getPrice(const std::string &name)
{
    return price * discount;
}
double Books::getPrice(const std::string &name)
{
    return price * discount;
}
