#include "Platform.hpp"
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>
#include <limits>
//#include <utility>
// #include <WinSock2.h>

void Platform::show()
{
    int action;
    do
    {
        output << "选择操作：\n"
               << "1. 用户中心\n"
               << "2. 商品展示\n"
               << "3. 商品信息修改（针对商家）\n"
               << "其他数字 退出平台" << std::endl;
        server.sendMessage(output);
        /* client.recvMessage(); */
        action = server.recvMessage();
        switch (action)
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
        }
        // output << std::endl;
    } while (action > 0 && action < 4);
    output << "感谢使用！" << std::endl;
    server.sendMessage(output);
}
void Platform::userCenter()
{
    if (name.empty())  // 未登录情况下只能注册或登录
        userRegisterOrLog();
    else  // 已登录
    {
        int choice;
        do
        {
            output << "选择操作：\n"
                   << "1. 用户信息查询与修改\n"
                   << "2. 注销登录\n"
                   << "3. 购物车管理\n"
                   << "其他数字 退出" << std::endl;
            input(choice);
            switch (choice)
            {
                case 1:
                    userInformationChange();
                    break;
                case 2:
                    userQuit();
                    return;
                case 3:
                    user->orderManagement(showGoods, allGoods);
                    break;
                default:
                    break;
            }
        } while (choice > 0 && choice < 4);
    }
}
void Platform::userRegisterOrLog()
{
    output << "选择操作：\n"
           << "1. 用户注册\n"
           << "2. 用户登录\n"
           << "其他数字 退出" << std::endl;
    int choice, type;
    input(choice);
    std::string operation[2] = {"注册", "登录"};
    if (choice == 1 || choice == 2)
    {
        output << "请输入" << operation[choice - 1] << "的用户类型：\n"
               << "1表示顾客，2表示商家\n";
        input(type);
        if (type > 2 || type < 0 || (type == 0 && choice == 1))  // 只有登录时能选择管理员类型
        {
            output << "没有该类型用户，已退出\n";
            return;
        }
        output << "输入用户名：\n";
        std::cin >> name;
        freeUser();
        switch (type)
        {
            case 0:
                user = new Admin(name, server);
                break;
            case 1:
                user = new Consumer(name, server);
                break;
            case 2:
                user = new Merchant(name, server);
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
            if (!user->login(type))  // 登录失败情况下
            {
                freeUser();
                name.clear();
            }
            else
            {
                auto mt = shoppingCart.find(name);
                // auto st =
                if (mt != shoppingCart.end())
                    user->setShoppingCart(mt->second);
                mt = finalOrder.find(name);
                if (mt != finalOrder.end())
                    user->setFinalOrder(mt->second);
            }
            break;
        default:
            break;
    }
}
void Platform::userInformationChange()
{
    int choice;
    std::string hh;
    do
    {
        /* char tmp[15];
        std::strcpy(tmp, name.c_str()); */
        output << name << ", 请选择操作：\n"
               << "1. 修改密码\n"
               << "2. 余额查询\n"
               << "3. 余额充值与消费\n"
               << "其他数字 退出" << std::endl;
        input(choice);
        switch (choice)
        {
            case 1:
                user->changePwd();
                break;
            case 2:
                output << name << "，您当前账户余额为" << user->queryBalance() << "元\n";
                break;
            case 3:
                user->topUpAndDown();
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 4);
}
void Platform::userQuit()
{
    output << "已退出！\n";
    std::vector<std::pair<GoodsInfo, int>> shoppingcart, order;
    user->getShoppingCart(shoppingcart);
    shoppingCart.insert(std::make_pair(name, shoppingcart));
    user->getFinalOrder(order);
    finalOrder.insert(std::make_pair(name, order));
    name.clear();
    showGoods.clear();
    freeUser();
}
void Platform::goodsInformation()
{
    int choice;
    output << "请选择筛选条件\n"
           << "0. 展示某类商品\n"
           << "1. 按名称筛选\n"
           << "2. 按价格筛选\n"
           << "3. 按数量筛选\n"
           << "其他数字 退出\n";
    int amount;
    double priceLow, priceHigh;
    input(choice);
    std::string goodsName;
    if (choice >= 0 && choice < 4)
        definiteType();
    else
        return;
    goods->setGoods(allGoods);
    goods->getGoods(allGoods);
    switch (choice)
    {
        case 0:
            goods->search(showGoods);
            break;
        case 1:
            output << "请输入商品名称\n";
            std::cin >> goodsName;
            goods->search(goodsName, showGoods);
            break;
        case 2:
            while (1)
            {
                output << "请输入商品最低价格\n";
                input(priceLow);
                output << "请输入商品最高价格\n";
                input(priceHigh);
                //大小比较
                if (priceLow > priceHigh || priceLow < 0 || priceHigh < 0)
                    output << "输入错误，请重新输入！\n";
                else
                {
                    goods->search(priceLow, priceHigh, showGoods);
                    break;
                }
            }
            break;
        case 3:
            output << "请输入商品最小数量";
            input(amount);
            goods->search(amount, showGoods);
            break;
        default:
            break;
    }
    if (!name.empty())
    {
        output << "请选择操作：\n "
               << "1. 跳转到购物车界面\n"
               << "其他数字 退出\n"
               << std::endl;
        std::cin >> choice;
        if (choice == 1)
            user->orderManagement(showGoods, allGoods);
    }
    // 实验二
    /*  output << "请选择操作：\n "
               << "1. 购买商品\n"
               << "其他数字 退出\n"
               << std::endl;
     std::cin >> choice;
     if (choice == 1)
         purchaseGoods(); */
    goods->getGoods(allGoods);
    freeGoods();
    //清空vector
    std::vector<GoodsInfo> tmp;
    showGoods.swap(tmp);
}
void Platform::changeGoods()
{
    // 未登录情况下
    if (name.empty() || user->getUserType() == 1)
    {
        output << "请登入商家账号后进行该操作！\n";
        return;
    }
    int choice;
    do
    {
        double dis;
        output << "请选择要进行的操作\n"
               << "1. 修改已有商品\n"
               << "2. 添加商品\n"
               << "其他数字 退出\n";
        input(choice);
        std::string goodsName;
        if ((choice > 0 && choice < 3) || (choice == 0 && user->getUserType() == 0))
        {
            definiteType();
            goods->setGoods(allGoods);
            goods->getGoods(allGoods);
            if (choice)
            {
                output << "输入商品名称\n";
                std::cin >> goodsName;
            }
        }
        switch (choice)
        {
            case 0:
                if (user->getUserType())
                {
                    output << "没有权限!\n";
                    break;
                }
                output << "请输入要给出的折扣(用小数表示，0-1之间):\n";
                input(dis);
                if (dis < 0 || dis > 1)
                {
                    output << "折扣不合理，已退出！\n";
                    return;
                }
                goods->atDiscount(dis);
                output << "打折成功";
                break;
            case 1:
                goods->changeItems(goodsName, name);
                break;
            case 2:
                goods->addItems(goodsName, name);
            default:
                break;
        }
    } while (choice > 0 && choice < 3);
    goods->getGoods(allGoods);
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    output << "请选择商品类型\n"
           << "1表示食物，2表示衣服，3表示图书\n";
    input(type);
    freeGoods();
    while (type < 1 || type > 3)
    {
        output << "没有该类型商品，请重新输入\n";
        input(type);
    }
    switch (type)
    {
        case 1:
            goods = new Foods(name, server);
            break;
        case 2:
            goods = new Clothes(name, server);
            break;
        case 3:
            goods = new Books(name, server);
            break;
        default:
            break;
    }
}

void Platform::initSock()
{
    server.serverInit();
}
template <typename T> void Platform::input(T &x)
{
    std::cin >> x;

    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
    inputStream >> x;
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
