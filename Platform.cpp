#include "Platform.hpp"

void Platform::show()
{
    int action;
    do
    {
        std::cout << "ѡ�������\n"
                  << "1. �û�ע��&��¼\n"
                  << "2. �û���Ϣ�鿴&�޸ģ���¼��\n"
                  << "3. ��Ʒ��Ϣ�鿴\n"
                  << "4. ��Ʒ��Ϣ�޸ģ�����̼ң�\n"
                  << "-1. �˳�ƽ̨" << std::endl;
        std::cin >> action;
        // system("clear");
        switch (action)
        {
            case 1:
                userRegisterOrLog();
                break;
            case 2:
                userInformationChange();
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                break;
        }
    } while (action != -1);
    std::cout << "��лʹ�ã�\n" << std::endl;
}
void Platform::userRegisterOrLog()
{
    std::cout << "ѡ�������\n"
              << "1. �û�ע��\n"
              << "2. �û���¼\n"
              << "-1. �˳�" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice != -1)
    {
        std::cout << "\n�����˻�����\n";
        std::cin >> name;
    }
    int type;
    switch (choice)
    {
        case 1:
            std::cout << "������ע����˻����ͣ�\n"
                      << "1��ʾ�˿ͣ�2��ʾ�̼�\n";
            std::cin >> type;
            switch (type)
            {
                case 1:
                    if (!user)
                        user = new Consumer(name);
                    user->userRegister(name);
                    break;
                case 2:
                    if (!user)
                        user = new Merchant(name);
                    user->userRegister(name);
                    break;
                default:
                    break;
            }
            break;
        case 2:
            std::cout << "�������¼���˻����ͣ�\n"
                      << "1��ʾ�˿ͣ�2��ʾ�̼ң�3��ʾϵͳ����Ա\n";
            std::cin >> type;
            switch (type)
            {
                case 1:
                    if (!user)
                        user = new Consumer(name);
                    user->login(name);
                    break;
                case 2:
                    if (!user)
                        user = new Merchant(name);
                    user->login(name);
                    break;
                case 3:
                    if (!user)
                        user = new Admin;
                    user->login("admin");
                    break;
            }
            break;
        default:
            break;
    }
    user->save();
}
void Platform::userInformationChange()
{
    if (name.empty())
    {
        std::cout << "\n���¼�����\n";
        return;
    }
    std::cout << name << ", ��ѡ�������\n"
              << "1. �޸�����\n"
              << "2. ����ѯ\n"
              << "3. ����ֵ\n"
              << "4. ����\n"
              << "-1. �˳�" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice == -1)
        return;
    switch (choice)
    {
        case 1:
            user->changePwd(name);
            break;
        case 2:
            user->queryBalance(name);
            break;
        case 3:

            break;
        default:
            break;
    }
    user->save();
}