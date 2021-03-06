#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>
#include "MySocket.hpp"
// #include <set>

/**
 * @brief 存储商品信息，重载相等运算符，实现std::find函数
 *
 */
struct GoodsInfo
{
    std::string name, merchant, discription;
    double price, discount;
    int type, amount;
    std::map<std::string, int> sold;
    bool operator==(const GoodsInfo &) const;
};
/**
 * @brief 商品类，实现有关商品的各种操作
 *
 */
class Goods  // 构造函数，读入商品数据
{
  public:
    Goods(Client c, Server s) : client(c), server(s)
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
            // goodTemp.sold = 0;
            goofp >> goodTemp.type >> goodTemp.name >> goodTemp.discription >> goodTemp.amount >> goodTemp.price >>
                goodTemp.discount >> goodTemp.merchant;
            if (goodTemp.name.empty())  // 略过空行
                continue;
            else
                goodsInfo.emplace_back(goodTemp);
        }
    }
    virtual ~Goods()  // 析构函数，将商品数据存入文件
    {
        goofp.close();
        goofp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\GoodsInfo.txt", std::ios::out | std::ios::trunc);
        goofp.seekg(0, std::fstream::beg);
        for (auto st : goodsInfo)
            goofp << st.type << " " << st.name << " " << st.discription << " " << st.amount << " " << st.price << " "
                  << st.discount << " " << st.merchant << std::endl;
        goofp.close();
    }

    virtual double getPrice() const = 0;                         // 纯虚函数，返回商品价格
    void addItems(const std::string &, const std::string &);     // 加入商品
    void changeItems(const std::string &, const std::string &);  // 修改商品信息
    bool changeInt(int &) const;                                 // 判断修改int类型是否合法
    bool changeDouble(double &) const;                           // 判断修改double类型是否合法
    void search(std::vector<GoodsInfo> &) const;                 // 查找商品，并存入vector中，实验二中用
    void search(const std::string &, std::vector<GoodsInfo> &) const;         // 重载，按名称查找商品
    void search(const double, const double, std::vector<GoodsInfo> &) const;  // 重载，按价格查找商品
    void search(const int, std::vector<GoodsInfo> &) const;                   // 重载，按数量查找商品
    void atDiscount(const double);                                            // 对某种类商品打折
    void preorderGoods(const std::string &, const std::string &, const std::string &, const int);
    void soldOut(const std::string &);
    //更新订单内商品剩余数量
    void updateInfo(std::vector<std::pair<GoodsInfo, int>> &);
    bool isInt(const std::string &) const;                    // 正则表达式判断输入是否为int类型
    bool isFloat(const std::string &) const;                  // 正则表达式判断输入是否为double类型
    template <typename T> void input(T &) const;              //检测非法输入
    void copyInfo(GoodsInfo &) const;                         //将类中数据成员信息拷贝到临时变量中
    void copyInfo(const std::vector<GoodsInfo>::iterator &);  //将数组中数据成员信息拷贝到数据成员中
    void getGoods(std::vector<GoodsInfo> &) const;
    void setGoods(const std::vector<GoodsInfo> &);

  protected:
    std::string name, merchant, discription;
    int type, amount;
    double price, discount;
    std::vector<GoodsInfo> goodsInfo;
    std::map<std::string, int> consumerBuy;  //保存被订单锁住的数量

    Client client;
    Server server;

  private:
    std::fstream goofp;
    int num;
};

class Foods : public Goods
{
  public:
    Foods(Client c, Server s) : Goods(c, s)
    {
        type = 1;
    }
    Foods(const std::string &tname, Client c, Server s) : Goods(c, s)
    {
        merchant = tname;
        type = 1;
    }
    virtual ~Foods() override
    {
    }
    virtual double getPrice() const override;

  private:
};

class Clothes : public Goods
{
  public:
    Clothes(Client c, Server s) : Goods(c, s)
    {
        type = 2;
    }
    Clothes(const std::string &tname, Client c, Server s) : Goods(c, s)
    {
        merchant = tname;
        type = 2;
    }
    virtual ~Clothes() override
    {
    }
    virtual double getPrice() const override;

  private:
};

class Books : public Goods
{
  public:
    Books(Client c, Server s) : Goods(c, s)
    {
        type = 3;
    }
    Books(const std::string &tname, Client c, Server s) : Goods(c, s)
    {
        merchant = tname;
        type = 3;
    }
    virtual ~Books() override
    {
    }
    virtual double getPrice() const override;

  private:
};
