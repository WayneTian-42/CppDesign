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
    void show();  // չʾ��������

  private:
    Client client;
};