#include "PlatformShow.hpp"
#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

void PlatformShow::show()
{
    // int action = 1;
    bool skip = false, encryption = false;
    while (1)
    {
        /* std::cout << "ѡ�������\n"
                  << "1. �û�����\n"
                  << "2. ��Ʒչʾ\n"
                  << "3. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
                  << "�������� �˳�ƽ̨" << std::endl; */

        std::string buff;
        client.recvMessage(buff);
        std::string tmp;

        /* if (*(buff.end() - 1) == '1')
        {
            buff.erase(buff.end() - 1);
            flg = 1;
        }
        else if (*(buff.end() - 1) == '0')
        {
            break;
        } */
        if (*(buff.end() - 1) == '0')
            break;
        switch (*(buff.end() - 1))
        {
            case '1':
                skip = true;
                break;
            case '2':
                encryption = true;
                break;
            default:
                break;
        }
        if (*(buff.end() - 1) != '\n')
            buff.erase(buff.end() - 1);
        std::cout << buff;
        if (skip)
        {
            skip = false;
            continue;
        }
        if (encryption)
        {
            encryption = false;
            inputPwd(tmp);
        }
        else
            std::getline(std::cin, tmp);
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
    }
    std::cout << "��лʹ�ã�" << std::endl;
}
void PlatformShow::inputPwd(std::string &tmpPwd)
{
    while (1)
    {
        char ch;
        ch = _getch();      //��ȡһ���ַ����Ҳ���ʾ����Ļ��
        if (ch == VK_BACK)  //����backspace
        {
            if (!tmpPwd.empty())
            {
                std::cout << "\b \b" << std::flush;
                tmpPwd.erase(tmpPwd.length() - 1);  // ������������һ���ַ�
            }
        }
        else if (ch == VK_RETURN)  // ����س�
        {
            std::cout << std::endl;
            // tmpPwd += '\n';  // �ͻ��˻�ɾ���س�
            break;
        }
        else
        {
            tmpPwd += ch;  // �����ַ�
            _putch('*');   // ���*
        }
    }
}