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
    }
    ~Platform()
    {
    }
    void show();
    void userRegisterOrLog();
    void userInformationChange();

  private:
    std::string name;
    User *user;
};
