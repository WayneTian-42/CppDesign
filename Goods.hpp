#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
// #include <set>

struct GoodsInfo
{
    std::string name, merchant;
    double price, discount;
    int type, amount;
    bool operator==(const GoodsInfo &ac) const;
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
            GoodsInfo goodTemp;
            goofp >> goodTemp.type >> goodTemp.name >> goodTemp.amount >> goodTemp.price >> goodTemp.discount >>
                goodTemp.merchant;
            if (goodTemp.name.empty())
                continue;
            else
            {
                goodsInfo.emplace_back(goodTemp);
            }
        }
    }
    virtual ~Goods()
    {
        goofp.close();
        goofp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\GoodsInfo.txt", std::ios::out | std::ios::trunc);
        goofp.seekg(0, std::fstream::beg);
        for (auto st : goodsInfo)
            goofp << st.type << " " << st.name << " " << st.amount << " " << st.price << " " << st.discount << " "
                  << st.merchant << std::endl;
        goofp.close();
    }

    virtual double getPrice(const std::string &) = 0;
    void addItems(const std::string &, const std::string &);
    void changeItems(const std::string &, const std::string &);
    void search(std::vector<GoodsInfo> &);
    void search(const std::string &, std::vector<GoodsInfo> &);
    void search(const double, const double, std::vector<GoodsInfo> &);
    void search(const int, std::vector<GoodsInfo> &);
    void atDiscount(const double);
    void changeAmountOfGoods(const std::string &, const std::string &, const int, const int);
    // void solodOut(const std::string &, const std::string &, const int);
    template <typename T> void input(T &) const;
    void copyInfo(GoodsInfo &);
    void copyInfo(const std::vector<GoodsInfo>::iterator &);

  protected:
    std::string name, merchant;
    int type, amount;
    double price, discount;

  private:
    std::fstream goofp;
    std::vector<GoodsInfo> goodsInfo;
    int num;
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
