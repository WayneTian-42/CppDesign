#pragma once
#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Goods.hpp"
#include "User.hpp"

class Platform
{
  public:
    Platform()
    {
        user = nullptr;
        goods = nullptr;
    }
    ~Platform()
    {
    }
    void show();
    void userCenter();
    void userRegisterOrLog();
    void userInformationChange();
    void userQuit();
    void purchaseGoods();
    void goodsInformation();
    void changeGoods();
    void definiteType();
    void refreshUser();
    void freeUser();
    void refreshGoods();
    void freeGoods();
    template <typename T> void input(T &x) const;

  private:
    std::string name;
    User *user;
    Goods *goods;
    std::vector<GoodsInfo> showGoods;
};
