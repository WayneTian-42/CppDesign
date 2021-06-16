#include "Platform.hpp"
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>
#include <limits>
#include <regex>
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
        /* std::string tmp;
        server.recvMessage(tmp);
        action = std::stoi(tmp); */
        input(action);
        // std::cout << action;
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
    if (action != -1)
    {
        output << "感谢使用！" << std::endl << "0";
        server.sendMessage(output);
    }
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
            // input(choice);
            server.sendMessage(output);
            /* std::string tmp;
            server.recvMessage(tmp);
            choice = std::stoi(tmp); */
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
    /* output << "1";
    server.sendMessage(output); */
}
void Platform::userRegisterOrLog()
{
    output << "选择操作：\n"
           << "1. 用户注册\n"
           << "2. 用户登录\n"
           << "其他数字 退出" << std::endl;
    int choice, type;
    server.sendMessage(output);
    input(choice);
    std::string operation[2] = {"注册", "登录"};
    if (choice == 1 || choice == 2)
    {
        output << "请输入" << operation[choice - 1] << "的用户类型：\n"
               << "1表示顾客，2表示商家\n";
        server.sendMessage(output);
        input(type);
        if (type > 2 || type < 0 || (type == 0 && choice == 1))  // 只有登录时能选择管理员类型
        {
            output << "没有该类型用户，已退出\n1";  //
            server.sendMessage(output);
            return;
        }
        output << "输入用户名：\n";
        server.sendMessage(output);
        input(name);
        if (name.empty())
            return;
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
        server.sendMessage(output);
        input(choice);
        switch (choice)
        {
            case 1:
                user->changePwd();
                break;
            case 2:
                output << name << "，您当前账户余额为" << user->queryBalance() << "元\n1";
                server.sendMessage(output);
                break;
            case 3:
                user->topUpAndDown();
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 4);
    /*  output << "1";
     server.sendMessage(output); */
}
void Platform::userQuit()
{
    output << "已退出！\n1";
    server.sendMessage(output);
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
    server.sendMessage(output);
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
            server.sendMessage(output);
            // std::cin >> goodsName;
            input(goodsName);
            goods->search(goodsName, showGoods);
            break;
        case 2:
            while (1)
            {
                output << "请输入商品最低价格\n";
                server.sendMessage(output);
                input(priceLow);
                output << "请输入商品最高价格\n";
                server.sendMessage(output);
                input(priceHigh);
                //大小比较
                if (priceLow > priceHigh || priceLow < 0 || priceHigh < 0)
                {
                    output << "输入错误，请重新输入！\n";
                    server.sendMessage(output);
                }
                else
                {
                    goods->search(priceLow, priceHigh, showGoods);
                    break;
                }
            }
            break;
        case 3:
            output << "请输入商品最小数量";
            server.sendMessage(output);
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
        server.sendMessage(output);
        input(choice);
        // std::cin >> choice;
        if (choice == 1)
            user->orderManagement(showGoods, allGoods);
    }
    output << "1";
    server.sendMessage(output);
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
        output << "请登入商家账号后进行该操作！\n1";
        server.sendMessage(output);
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
        server.sendMessage(output);
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
                server.sendMessage(output);
                input(goodsName);
                // std::cin >> goodsName;
            }
        }
        switch (choice)
        {
            case 0:
                if (user->getUserType())
                {
                    output << "1";
                    server.sendMessage(output);
                    break;
                }
                output << "请输入要给出的折扣(用小数表示，0-1之间):\n";
                server.sendMessage(output);
                input(dis);
                if (dis < 0 || dis > 1)
                {
                    output << "折扣不合理，已退出！\n1";
                    server.sendMessage(output);
                    return;
                }
                goods->atDiscount(dis);
                output << "打折成功\n1";
                server.sendMessage(output);
                break;
            case 1:
                goods->changeItems(goodsName, name);
                break;
            case 2:
                goods->addItems(goodsName, name);
                break;
            default:
                break;
        }
    } while (choice > 0 && choice < 3);
    /* output << "1";
    server.sendMessage(output); */
    if (goods != nullptr)
        goods->getGoods(allGoods);
    freeGoods();
}
void Platform::definiteType()
{
    int type;
    output << "请选择商品类型\n"
           << "1表示食物，2表示衣服，3表示图书\n";
    server.sendMessage(output);
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

/* void Platform::initSock()
{
    server.serverInit();
} */
void Platform::input(int &x)
{
    /* std::cin >> x;

    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
    inputStream >> x; */
    std::string tmp;
    server.recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    if (tmp.empty())
    {
        x = -1;
        return;
    }
    while (!isInt(tmp))
    {
        output << "输入不合法，请输入数字\n";
        server.sendMessage(output);
        server.recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stoi(tmp);
}
void Platform::input(double &x)
{
    std::string tmp;
    server.recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    while (!isDouble(tmp))
    {
        output << "输入不合法，请输入数字\n";
        server.sendMessage(output);
        server.recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stod(tmp);
}
void Platform::input(std::string &x)
{
    server.recvMessage(x);
    if (!x.empty())
        x.erase(x.end() - 1);
}
bool Platform::isInt(const std::string &input) const
{
    std::regex rx("^\\-?\\d+$");  //+号表示多次匹配
    return std::regex_match(input, rx);
}
bool Platform::isDouble(const std::string &input) const
{
    std::regex rx("^\\d+(.\\d+)?$");
    return std::regex_match(input, rx);
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
