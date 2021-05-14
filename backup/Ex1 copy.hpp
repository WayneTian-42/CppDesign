#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

struct AccInfo
{
    std::string name, pwd;
    double bala;
    int t;
    bool operator<(const AccInfo &ac) const;
};

struct GoodsInfo
{
    std::string name;
    double price, discount;
    int type, amount;
    bool operator<(const GoodsInfo &ac) const;
};

class Account
{
  public:
    Account()
    {
    }
    Account(const std::string name) : userName(name)
    {
        num = 0;
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt");
        if (!accfp)
        {
            std::cout << "Open file error!\n";
            return;
        }
        while (accfp.peek() != EOF)
        {
            accSet[num] = new AccInfo;
            accfp >> accSet[num]->name >> accSet[num]->pwd >> accSet[num]->t >> accSet[num]->bala;
            accInfo.insert(*accSet[num]);
            num++;
        }
    }
    ~Account()
    {
        for (int i = 0; i < num; i++)
            delete accSet[i];
        accfp.close();
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt", std::ios::out | std::ios::trunc);
        accfp.seekg(0, std::fstream::beg);
        for (auto st : accInfo)
            accfp << st.name << " " << st.pwd << " " << st.t << " " << st.bala << std::endl;
        accfp.close();
    }
    void init();  //好像不用实现？
    bool registerAcc();
    void changePwd();

  private:
    std::string userName;
    std::fstream accfp;
    AccInfo *accSet[1024];
    std::set<AccInfo> accInfo;
    int num;
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
            goofp << st.type << " " << st.name << " " << st.amount << " " << st.price << " " << st.discount
                  << std::endl;
        goofp.close();
    }

    virtual double getPrice() = 0;
    bool existGoods();  //还没实现，忘了为什么要有这个函数
    void addItems();
    void changeItems();
    void search(const std::string &);
    void search(const double, const double = 100000005);
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
    }
    ~Books()
    {
    }
    virtual double getPrice() override;

  private:
};

class User
{
  public:
    User()
    {
    }
    ~User()
    {
    }

    virtual int getUserType() = 0;
    bool search(const std::string &);
    Account &login(const std::string &);
    void buySth();
    void topUp();
    int getAcc();
};

class Consumer : public User
{
  public:
    Consumer(const std::string s) : User(), name(s)
    {
        /* if (search(name))
            acc = login(name);
        else
            acc.registerAcc(); */
    }
    ~Consumer()
    {
    }
    int getUserType() override;

  private:
    std::string name;
    Account acc;
};
class Merchant : public User
{
  public:
    Merchant(const std::string s) : name(s)
    {
        /* if (search(name))
            acc = login(name);
        else
            acc.registerAcc(); */
    }
    ~Merchant()
    {
    }
    void changeGoods();

  private:
    std::string name;
    Account acc;
    std::vector<Goods> goods;
};
