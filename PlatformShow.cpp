#include "PlatformShow.hpp"
#include <string>

void PlatformShow::show()
{
    while (1)
    {
        /* std::cout << "ѡ�������\n"
                  << "1. �û�����\n"
                  << "2. ��Ʒչʾ\n"
                  << "3. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
                  << "�������� �˳�ƽ̨" << std::endl; */

        std::string buff;
        client.recvMessage(buff);
        std::cout << buff;
        int action;
        client.input(action);
        client.sendMessage(action);
    }
}
