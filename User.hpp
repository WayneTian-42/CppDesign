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
    bool operator==(const AccInfo &ac) const;
};

class User
{
  public:
    User() : /* logged(false), */ type(0), balance(0)
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
            AccInfo accTemp;
            accfp >> accTemp.name >> accTemp.pwd >> accTemp.t >> accTemp.bala;
            if (accTemp.name.empty())
                continue;
            else
            {
                accInfo.emplace_back(accTemp);
                // num++;
            }
        }
    }
    virtual ~User()
    {
        accfp.close();
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt", std::ios::out | std::ios::trunc);
        accfp.seekg(0, std::fstream::beg);
        for (auto st : accInfo)
            accfp << st.name << " " << st.pwd << " " << st.t << " " << st.bala << std::endl;
        accfp.close();
    }

    virtual int getUserType() = 0;
    int search(const std::string &);
    void userRegister();
    bool login(const int);
    void changePwd();
    void confirmPwd(std::string &);
    double queryBalance(const double = 0.0);
    void topUp();
    // void exchangeMoney(const std::string &, const double);
    // void save();

    //�޸�Ϊset get
  protected:
    std::string name, password;
    // bool logged;
    int type;
    double balance;

  private:
    std::fstream accfp;
    std::vector<AccInfo> accInfo;
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
    // void changeGoods();

  private:
    // std::vector<Goods> goods;
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