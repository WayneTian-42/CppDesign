#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "Goods.hpp"

/**
 * @brief 存储用户信息，重载相等运算符，实现std::find函数
 *
 */
struct AccInfo
{
    std::string name, pwd;
    double bala;
    int t;
    bool operator==(const AccInfo &ac) const;
};

/**
 * @brief 用户类，实现有关用户的各种操作
 *
 */
class User
{
  public:
    User() : type(0), balance(0)  // 构造函数，读入用户数据
    {
        num = 0;
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt");
        if (!accfp)
        {
            std::cout << "打开文件失败！\n";
            return;
        }
        while (accfp.peek() != EOF)
        {
            AccInfo accTemp;
            accfp >> accTemp.name >> accTemp.pwd >> accTemp.t >> accTemp.bala;
            if (accTemp.name.empty())  // 略过空行
                continue;
            else
                accInfo.emplace_back(accTemp);
        }
    }
    virtual ~User()  // 析构函数，将用户数据存入文件
    {
        accfp.close();
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt", std::ios::out | std::ios::trunc);
        accfp.seekg(0, std::fstream::beg);
        for (auto st : accInfo)
            accfp << st.name << " " << st.pwd << " " << st.t << " " << st.bala << std::endl;
        accfp.close();
    }

    virtual int getUserType() const = 0;            // 纯虚函数，返回用户类型
    int search(const std::string &userName) const;  // 查找用户名是否存在，若存在返回在数组中位置
    void userRegister();                            // 用户注册
    bool login(const int userType);                 // 用户登录
    void changePwd();                               // 修改密码
    void confirmPwd(std::string &tmpPwd) const;     // 确认密码是否正确
    double queryBalance() const;                    // 查询余额
    void topUpAndDown();                            // 修改余额
    template <typename T> void input(T &x) const;   // 检测输入

    //修改为set get
  protected:
    std::string name, password;  // 用户名与密码
    // bool logged;
    int type;        // 用户类型
    double balance;  // 用户余额

  private:
    std::fstream accfp;            // 文件指针
    std::vector<AccInfo> accInfo;  // 所有用户信息的数组
    int num;                       // 该用户在数组中下标
};

/**
 * @brief 消费者类型
 *
 */
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
    virtual int getUserType() const override
    {
        return type;
    }

  private:
};
/**
 * @brief 商人类型
 *
 */
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
    virtual int getUserType() const override
    {
        return type;
    }

  private:
};
/**
 * @brief 管理员类型，实现对某种类型商品打折
 *
 */
class Admin : public User
{
  public:
    Admin(const std::string s) : User()
    {
        name = s;
        type = 0;
    }
    virtual ~Admin() override
    {
    }
    virtual int getUserType() const override
    {
        return type;
    }
};