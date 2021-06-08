#include "PlatformShow.hpp"
#include <string>

void PlatformShow::show()
{
    while (1)
    {
        /* std::cout << "选择操作：\n"
                  << "1. 用户中心\n"
                  << "2. 商品展示\n"
                  << "3. 商品信息修改（针对商家）\n"
                  << "其他数字 退出平台" << std::endl; */

        std::string buff;
        client.recvMessage(buff);
        std::cout << buff;
        int action;
        client.input(action);
        client.sendMessage(action);
    }
}
