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

typedef struct
{
    std::string name;
    double price;
    int type, amount;
} GoodsInfo;

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
            num++;
        }
    }
    ~Account();
    void init();
    bool registerAcc();
    void changePwd();

  private:
    std::string userName;
    std::fstream accfp;
    AccInfo *accSet[1024];
    int num;
};

class Goods
{
  public:
    Goods()
    {
    }
    ~Goods()
    {
    }

    virtual int getPrice() = 0;
    void search();
    void search(std::string &, double &, int &);
};

class Foods : public Goods
{
  public:
    Foods() : Goods()
    {
        search(name, price, amount);
    }
    ~Foods()
    {
    }

  private:
    std::string name;
    int type = 0, amount;
    double price;
};

class Clothes : public Goods
{
  public:
    Clothes() : Goods()
    {
        search(name, price, amount);
    }
    ~Clothes()
    {
    }

  private:
    std::string name;
    int type = 1, amount;
    double price;
};

class Books : public Goods
{
  public:
    Books() : Goods()
    {
        search(name, price, amount);
    }
    ~Books()
    {
    }

  private:
    std::string name;
    int type = 2, amount;
    double price;
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
