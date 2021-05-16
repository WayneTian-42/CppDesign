#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

struct GoodsInfo
{
    std::string name, merchant;
    double price, discount;
    int type, amount;
    bool operator<(const GoodsInfo &ac) const;
};

class Goods
{
  public:
    Goods()
    {
        num = 0;
        goofp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\GoodsInfo.txt");
        if (!goofp)
        {
            std::cout << "Open file error!\n";
            return;
        }
        while (goofp.peek() != EOF)
        {
            goodSet[num] = new GoodsInfo;
            goofp >> goodSet[num]->type >> goodSet[num]->name >> goodSet[num]->amount >> goodSet[num]->price >>
                goodSet[num]->discount;
            goodsInfo.insert(*goodSet[num]);
            num++;
        }
    }
    ~Goods()
    {
        for (int i = 0; i < num; i++)
            delete goodSet[i];
        goofp.close();
        goofp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\GoodsInfo.txt", std::ios::out | std::ios::trunc);
        goofp.seekg(0, std::fstream::beg);
        for (auto st : goodsInfo)
            goofp << st.type << " " << st.name << " " << st.amount << " " << st.price << " " << st.discount << " "
                  << st.merchant << std::endl;
        goofp.close();
    }

    virtual double getPrice() = 0;
    bool existGoods();  //还没实现，忘了为什么要有这个函数
    void addItems();
    void changeItems();
    void search();
    void search(const std::string &);
    void search(const double, const double);
    void search(const int, const int = 100000005);
    void discount(const int);

  protected:
    std::string name;
    GoodsInfo *goodSet[1024];
    std::set<GoodsInfo> goodsInfo;
    int type, num;  //商品数量
    double price;

  private:
    std::fstream goofp;
};

class Foods : public Goods
{
  public:
    Foods(const std::string &tname) : Goods()
    {
        name = tname;
        type = 1;
    }
    ~Foods()
    {
    }
    virtual double getPrice() override;

  private:
};

class Clothes : public Goods
{
  public:
    Clothes(const std::string &tname) : Goods()
    {
        name = tname;
        type = 2;
    }
    ~Clothes()
    {
    }
    virtual double getPrice() override;

  private:
};

class Books : public Goods
{
  public:
    Books(const std::string &tname) : Goods()
    {
        name = tname;
        type = 3;
    }
    ~Books()
    {
    }
    virtual double getPrice() override;

  private:
};
