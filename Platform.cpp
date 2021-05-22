#include "Platform.hpp"
#include <iostream>
#include <string>
#include <limits>

void Platform::show()
{
    int action;
    do
    {
        std::cout << "选择操作：\n"
                  << "1. 用户注册&登录\n"
                  << "2. 用户信息查看&修改（登录后）\n"
                  << "3. 商品展示与购买（购买需登录）\n"
                  << "4. 商品信息修改（针对商家）\n"
                  << "其他数字 退出平台" << std::endl;
        input(action);
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
                changeGoods();
                break;
            default:
                break;
        }
    } while (action > 0 && action < 5);
    std::cout << "感谢使用！\n" << std::endl;
}
void Platform::userRegisterOrLog()
{
    std::cout << "选择操作：\n"
              << "1. 用户注册\n"
              << "2. 用户登录\n"
              << "其他数字 退出" << std::endl;
    int choice, type;
    input(choice);
    std::string operation[2] = {"注册", "登录"};
    if (choice != -1)
    {
        std::cout << "请输入" << operation[choice - 1] << "的账户类型：\n"
                  << "1表示顾客，2表示商家\n";
        input(type);
        if (type > 2 || type < 0 || (type == 0 && choice == 1))
        {
            std::cout << "没有该类型账户，已退出\n";
            return;
        }
        std::cout << "输入账户名：\n";
        std::cin >> name;
        freeUser();
        switch (type)
        {
            case 0:
                user = new Admin();
                break;
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
        std::cout << "请登录后操作\n";
        return;
    }
    std::cout << name << ", 请选择操作：\n"
              << "1. 修改密码\n"
              << "2. 余额查询\n"
              << "3. 余额充值\n"
              << "4. 购物车管理\n"
              << "其他数字 退出" << std::endl;
    int choice;
    input(choice);
    if (choice < 1 || choice > 4)
        return;
    switch (choice)
    {
        case 1:
            user->changePwd();
            break;
        case 2:
            std::cout << name << "，您当前账户余额为" << user->queryBalance() << "元\n";
            break;
        case 3:
            user->topUp();
            break;
        case 4:
            user->orderManagement(showGoods);
            break;
        default:
            break;
    }
    // freeUser();
}
void Platform::goodsInformation()
{
    std::cout << "请选择筛选条件\n"
              << "0. 展示某类商品\n"
              << "1. 按名称筛选\n"
              << "2. 按价格筛选\n"
              << "3. 按数量筛选\n"
              << "其他数字 退出\n";
    int choice, amount;
    double priceLow, priceHigh;
    input(choice);
    std::string goodsName;
    if (choice >= 0 && choice < 4)
        definiteType();
    else
        return;
    switch (choice)
    {
        case 0:
            goods->search(showGoods);
            break;
        case 1:
            std::cout << "请输入商品名称";
            std::cin >> goodsName;
            goods->search(goodsName, showGoods);
            break;
        case 2:
            std::cout << "请输入商品最低价格与最高价格";
            input(priceLow);
            input(priceHigh);
            //大小比较
            goods->search(priceLow, priceHigh, showGoods);
            break;
        case 3:
            std::cout << "请输入商品最小数量";
            input(amount);
            goods->search(amount, showGoods);
            break;
        default:
            break;
    }
    if (!name.empty())
    {
        std::cout << "请选择操作：\n "
                  << "1. 跳转到购物车界面\n"
                  << "其他数字 退出\n"
                  << std::endl;
        std::cin >> choice;
        if (choice == 1)
            user->orderManagement(showGoods);
    }
    freeGoods();
    //清空vector
    std::vector<GoodsInfo> tmp;
    showGoods.swap(tmp);
}
void Platform::changeGoods()
{
    if (name.empty() || user->getUserType() == 1)
    {
        std::cout << "请登入商家账号后进行该操作！\n";
        return;
    }
    int choice;
    double dis;
    std::cout << "请选择要进行的操作\n"
              << "1. 修改已有商品\n"
              << "2. 添加商品\n"
              << "其他数字 退出\n";
    input(choice);
    std::string goodsName;
    if (choice >= 0 && choice < 3)
    {
        definiteType();
        if (choice)
        {
            std::cout << "输入商品名称";
            std::cin >> goodsName;
        }
    }
    switch (choice)
    {
        case 0:
            if (user->getUserType())
            {
                std::cout << "没有权限!\n";
                return;
            }
            std::cout << "请输入要给出的折扣(用小数表示，0-1之间):\n";
            input(dis);
            if (dis < 0 || dis > 1)
            {
                std::cout << "折扣不合理，已退出！\n";
                return;
            }
            goods->atDiscount(dis);
            std::cout << "打折成功";
            break;
        case 1:
            goods->changeItems(goodsName, name);
            break;
        case 2:
            goods->addItems(goodsName, name);
        default:
            break;
    }
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    std::cout << "请选择商品类型\n"
              << "1表示食物，2表示衣服，3表示图书\n";
    input(type);
    freeGoods();
    while (type < 1 || type > 3)
    {
        std::cout << "没有该类型商品，请重新输入\n";
        input(type);
    }
    switch (type)
    {
        case 1:
            goods = new Foods(name);
            break;
        case 2:
            goods = new Clothes(name);
            break;
        case 3:
            goods = new Books(name);
            break;
        default:
            break;
    }
}
template <class T> void Platform::input(T &x) const
{
    std::cin >> x;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
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
void Platform::freeGoods()
{
    if (goods)
    {
        delete goods;
        goods = nullptr;
    }
}