#pragma once
#include <algorithm>
#include <cstring>
#include <map>
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
    void userRegisterOrLog();
    void userInformationChange();
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
    //保存订单数据
    std::map<std::string, std::vector<std::pair<GoodsInfo, int>>> orderInformation;
    std::vector<std::pair<GoodsInfo, int>> changeInformation;
};
