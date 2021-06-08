#include "PlatformShow.hpp"
#include <string>

void PlatformShow::show()
{
    int action = 1;
    do
    {
        /* std::cout << "选择操作：\n"
                  << "1. 用户中心\n"
                  << "2. 商品展示\n"
                  << "3. 商品信息修改（针对商家）\n"
                  << "其他数字 退出平台" << std::endl; */

        std::string buff;
        client.recvMessage(buff);
        std::cout << buff;
        /* client.input(action);
        std::string tmp = std::to_string(action); */
        std::string tmp;
        std::cin >> tmp;
        client.sendMessage(tmp);
        /* switch (action)
        {
            case 1:
                userCenter();
                break;
            case 2:
                goodsInformation();
                break;
            case 3:
                changeGoods();
                break;
            default:
                break;
        } */
    } while (action > 0 && action < 4);
    std::cout << "感谢使用！" << std::endl;
}
