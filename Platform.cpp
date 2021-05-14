#include "Platform.hpp"

void Platform::show()
{
    int action;
    do
    {
        std::cout << "选择操作：\n"
                  << "1. 用户注册&登录\n"
                  << "2. 用户信息查看&修改（登录后）\n"
                  << "3. 商品信息查看\n"
                  << "4. 商品信息修改（针对商家）\n"
                  << "-1. 退出平台" << std::endl;
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
    std::cout << "感谢使用！\n" << std::endl;
}
void Platform::userRegisterOrLog()
{
    std::cout << "选择操作：\n"
              << "1. 用户注册\n"
              << "2. 用户登录\n"
              << "-1. 退出" << std::endl;
    int choice;
    std::cin >> choice;
    if (choice != -1)
    {
        std::cout << "\n输入账户名：\n";
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
    std::cout << "选择操作：\n"
              << "1. 修改密码\n"
              << "2. 余额查询\n"
              << "3. 余额充值\n"
              << "4. 消费\n"
              << "-1. 退出" << std::endl;
    int choice;
    std::cin >> choice;
    if (name.empty() && choice != -1)
    {
        std::cout << "\n输入账户名：\n";
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