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
                goodsInformation();
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
    int choice, type;
    std::cin >> choice;
    std::string operation[2] = {"注册", "登录"};
    if (choice != -1)
    {
        std::cout << "请输入" << operation[choice - 1] << "的账户类型：\n"
                  << "1表示顾客，2表示商家\n";
        std::cin >> type;
        std::cout << "\n输入账户名：\n";
        std::cin >> name;
        switch (type)
        {
            if (user)
                freeUser();
            case 1:
                user = new Consumer(name);
                break;
            case 2:
                user = new Merchant(name);
                break;
            default:
                break;
        }
    }
    switch (choice)
    {
        case 1:
            user->userRegister();
            freeUser();
            name.clear();
            break;
        case 2:
            if (!user->login(type))
            {
                freeUser();
                name.clear();
            }
            break;
        default:
            break;
    }
    // user->save();
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
            user->changePwd();
            break;
        case 2:
            user->queryBalance();
            break;
        case 3:
            user->topUp();
            break;
        default:
            break;
    }
    freeUser();
}
void Platform::goodsInformation()
{
    std::cout << "请选择筛选条件\n"
              << "0. 展示所有商品\n"
              << "1. 按名称筛选\n"
              << "2. 按类型筛选\n"
              << "3. 按价格筛选\n"
              << "4. 按数量筛选\n"
              << "-1. 退出\n";
    int choice, type, amount;
    double priceLow, priceHigh;
    std::cin >> choice;
    std::string goodsName;
    if (choice != -1)
    {
        std::cout << "请输入查看的货物类型：\n"
                  << "1表示食物，2表示衣服，3表示\n";
        std::cin >> type;
        std::cout << "\n输入账户名：\n";
        std::cin >> name;
        switch (type)
        {
            if (user)
                freeUser();
            case 1:
                user = new Consumer(name);
                break;
            case 2:
                user = new Merchant(name);
                break;
            default:
                break;
        }
    }
    switch (choice)
    {
        case 0:
            goods->search(0.0);
            break;
        case 1:
            std::cout << "请输入商品名称";
            std::cin >> goodsName;
            goods->search(goodsName);
            break;
        case 2:
            std::cout << "请输入商品类型";
            std::cin >> type;
            break;
        case 3:
            std::cout << "请输入商品最低价格与最高价格";
            std::cin >> priceLow >> priceHigh;
            //大小比较
            goods->search(priceLow, priceHigh);
            break;
        case 4:
            std::cout << "请输入商品最小数量";
            std::cin >> amount;
            goods->search(amount);
            break;
    }
}
void Platform::freeUser()
{
    if (user)
    {
        delete user;
        user = nullptr;
    }
}
