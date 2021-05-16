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
    int type;
    switch (choice)
    {
        case 1:
            std::cout << "请输入注册的账户类型：\n"
                      << "1表示顾客，2表示商家\n";
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
            std::cout << "请输入登录的账户类型：\n"
                      << "1表示顾客，2表示商家，3表示系统管理员\n";
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
        std::cout << "\n请登录后操作\n";
        return;
    }
    std::cout << name << ", 请选择操作：\n"
              << "1. 修改密码\n"
              << "2. 余额查询\n"
              << "3. 余额充值\n"
              << "4. 消费\n"
              << "-1. 退出" << std::endl;
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