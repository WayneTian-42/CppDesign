#pragma once
#include <string>
#include <sstream>

#include "MySocket.hpp"

class PlatformShow
{
  public:
    PlatformShow()
    {
        client.clientInit();
    }
    ~PlatformShow()
    {
    }
    void show();  // 展示基础界面

  private:
    Client client;
};