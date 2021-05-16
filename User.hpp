#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "Goods.hpp"

struct AccInfo
{
    std::string name, pwd;
    double bala;
    int t;
    bool operator<(const AccInfo &ac) const;
};

class User
{
  public:
    User() : type(0), balance(0)
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
            if (accSet[num]->name.empty())
                delete accSet[num];
            else
            {
                accInfo.insert(*accSet[num]);
                num++;
            }
        }
    }
    virtual ~User()
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

    virtual int getUserType() = 0;
    bool search();
    void userRegister();
    void login(const int);
    void changePwd();
    void queryBalance();
    void buySth();
    void topUp();  //??
    int getAcc();  //??
    void save();

  protected:
    std::string name;
    int type;
    double balance;

  private:
    std::fstream accfp;
    AccInfo *accSet[1024];
    std::set<AccInfo> accInfo;
    std::set<AccInfo>::iterator acc;
    int num;
};

class Consumer : public User
{
  public:
    Consumer(const std::string s) : User()
    {
        name = s;
        type = 1;
    }
    virtual ~Consumer() override
    {
    }
    virtual int getUserType() override
    {
        return type;
    }

  private:
};
class Merchant : public User
{
  public:
    Merchant(const std::string s) : User()
    {
        name = s;
        type = 2;
    }
    virtual ~Merchant() override
    {
    }
    virtual int getUserType() override
    {
        return type;
    }
    void changeGoods();

  private:
    std::vector<Goods> goods;
};
class Admin : public User
{
  public:
    Admin()
    {
        name = "admin";
        type = 0;
    }
    virtual ~Admin() override
    {
    }
    virtual int getUserType() override
    {
        return type;
    }
};