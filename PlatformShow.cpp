#include "PlatformShow.hpp"
#include <string>

void PlatformShow::show()
{
    int action = 1;
    do
    {
        /* std::cout << "ѡ�������\n"
                  << "1. �û�����\n"
                  << "2. ��Ʒչʾ\n"
                  << "3. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
                  << "�������� �˳�ƽ̨" << std::endl; */

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
    std::cout << "��лʹ�ã�" << std::endl;
}
