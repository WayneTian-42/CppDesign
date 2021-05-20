#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
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
                goodSet[num]->discount >> goodSet[num]->merchant;
            if (goodSet[num]->name.empty())
                delete goodSet[num];
            else
            {
                goodsInfo.insert(*goodSet[num]);
                num++;
            }
        }
    }
    virtual ~Goods()
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

    virtual double getPrice(const std::string &) = 0;
    bool existGoods();  //还没实现，忘了为什么要有这个函数
    void addItems(const std::string &, const std::string &);
    void changeItems(const std::string &, const std::string &);
    void search(std::vector<GoodsInfo> &);
    void search(const std::string &, std::vector<GoodsInfo> &);
    void search(const double, const double, std::vector<GoodsInfo> &);
    void search(const int, std::vector<GoodsInfo> &);
    void discount(const double);
    void solodOut(const std::string &, const std::string &, const int);

  protected:
    std::string merchant;
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
    Foods() : Goods()
    {
        type = 1;
    }
    Foods(const std::string &tname) : Goods()
    {
        merchant = tname;
        type = 1;
    }
    virtual ~Foods() override
    {
    }
    virtual double getPrice(const std::string &) override;

  private:
};

class Clothes : public Goods
{
  public:
    Clothes() : Goods()
    {
        type = 2;
    }
    Clothes(const std::string &tname) : Goods()
    {
        merchant = tname;
        type = 2;
    }
    virtual ~Clothes() override
    {
    }
    virtual double getPrice(const std::string &) override;

  private:
};

class Books : public Goods
{
  public:
    Books() : Goods()
    {
        type = 3;
    }
    Books(const std::string &tname) : Goods()
    {
        merchant = tname;
        type = 3;
    }
    virtual ~Books() override
    {
    }
    virtual double getPrice(const std::string &) override;

  private:
};
