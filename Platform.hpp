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
    void userRegisterOrLog();
    void userInformationChange();
    void goodsInformation();
    void freeUser();
    void freeGoods();

  private:
    std::string name;
    User *user;
    Goods *goods;
};
