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
    void inputPwd(std::string &pwd) const;

  private:
    Client client;
};