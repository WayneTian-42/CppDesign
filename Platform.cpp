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
    switch (choice)
    {
        case 1:
            user->userRegister(name);
            break;
        case 2:
            user->login(name);
            break;
        default:
            break;
    }
}
void Platform::userInformationChange()
{
    std::cout << "ѡ�������\n"
              << "1. �޸�����\n"
              << "2. ����ѯ\n"
              << "3. ����ֵ\n"
              << "4. ����\n"
              << "-1. �˳�" << std::endl;
    int choice;
    std::cin >> choice;
    if (name.empty() && choice != -1)
    {
        std::cout << "\n�����˻�����\n";
        std::cin >> name;
    }
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
}