#pragma once
#include <algorithm>
#include <cstring>
#include <map>
#include <sstream>
#include <string>
#include "Goods.hpp"
#include "User.hpp"
/**
 * @brief 平台类，用来展示信息以及选择操作
 *
 */
class Platform
{
  public:
    Platform()
    {
        server.serverInit();
        user = nullptr;
        goods = new Foods(server);
        goods->getGoods(allGoods);
        delete goods;
        goods = nullptr;
    }
    ~Platform()
    {
    }
    void show();                   // 展示基础界面
    void userCenter();             // 用户中心界面
    void userRegisterOrLog();      // 注册登录功能
    void userInformationChange();  // 修改用户信息
    void userQuit();               // 用户退出
    void purchaseGoods();          // 购买商品，实验二
    void goodsInformation();       // 商品信息
    void changeGoods();            // 修改商品信息
    void definiteType();           // 确定商品种类
    void freeUser();               // 释放用户指针
    void freeGoods();              // 释放商品指针
    void input(int &x);            // 检查输入
    void input(double &x);

    void input(std::string &x);
    bool isInt(const std::string &input) const;
    bool isDouble(const std::string &input) const;

    void initSock();

    /* void severInit();
    void clientInit(); */

  private:
    std::string name;  // 用户名
    User *user;        // 用户指针
    Goods *goods;      // 商品指针
    std::vector<GoodsInfo> allGoods;
    std::vector<GoodsInfo> showGoods;  // 展示的商品,用于实验二
    //保存订单数据
    std::map<std::string, std::vector<std::pair<GoodsInfo, int>>> shoppingCart, finalOrder;
    std::vector<std::pair<GoodsInfo, int>> changeInfo;

    std::stringstream output, inputStream;
    Server server;
};
