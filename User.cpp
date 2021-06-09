#include "User.hpp"
#include <algorithm>
#include <string>
#include <limits>
#include <iostream>
// 头文件用来实现星号显示密码
#include <conio.h>
#include <windows.h>
#include <regex>

bool AccInfo::operator==(const AccInfo &ac) const
{
    return (this->name == ac.name);
};

int User::search(const std::string &userName) const
{
    AccInfo tmp;
    int pos = -1;
    tmp.name = userName;
    auto st = std::find(accInfo.begin(), accInfo.end(), tmp);
    if (st != accInfo.end())
        pos = st - accInfo.begin();
    return pos;
}
void User::userRegister()
{
    if (search(name) != -1)
    {
        output << "该用户名已存在！\n1";
        server->sendMessage(output);
        return;
    }
    AccInfo tmp;
    tmp.name = name;

    while (1)
    {
        output << "输入密码:\n2";
        server->sendMessage(output);
        std::string confirm;
        // confirmPwd(tmp.pwd);
        server->recvMessage(tmp.pwd);
        tmp.pwd.erase(tmp.pwd.end() - 1);
        output << "请再次输入密码确认:\n2";
        server->sendMessage(output);
        server->recvMessage(confirm);
        confirm.erase(confirm.end() - 1);
        // confirmPwd(confirm);
        if (tmp.pwd == confirm)  // 直至两次密码相同才设定成功
            break;
    }
    tmp.t = type;
    tmp.bala = 0;
    accInfo.emplace_back(tmp);
    output << "注册成功!\n1";
    server->sendMessage(output);
}
bool User::login(const int userType)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != userType)
        {
            output << "用户类型错误，请退出重新选择！\n1";
            server->sendMessage(output);
            return false;
        }
        std::string pwd;
        output << "请输入密码:\n2";
        server->sendMessage(output);
        // confirmPwd(pwd);
        server->recvMessage(pwd);
        pwd.erase(pwd.end() - 1);
        if (pwd != accInfo[pos].pwd)
        {
            output << "密码错误!\n1";
            server->sendMessage(output);
            return false;
        }
        else
        {
            output << "登录成功!\n1";
            server->sendMessage(output);
            /* output << "-1";
            server->sendMessage(output); */
            password = pwd;
            this->type = userType;
            balance = accInfo[pos].bala;
            num = pos;
            return true;
        }
    }
    else
    {
        output << "用户不存在!\n1";
        server->sendMessage(output);
        return false;
    }
}
void User::changePwd()
{
    // 可以删掉？必须登陆后才能改密码
    if (search(name) == -1)
    {
        output << "用户不存在！\n1";
        server->sendMessage(output);
        return;
    }
    std::string pwd;
    output << "输入旧密码:\n2";
    server->sendMessage(output);
    std::string confirm;
    // confirmPwd(confirm);
    server->recvMessage(confirm);
    confirm.erase(confirm.end() - 1);
    if (confirm != password)
    {
        output << "密码错误，已退出！\n1";
        server->sendMessage(output);
        return;
    }
    while (1)
    {
        output << "输入新密码:\n2";
        server->sendMessage(output);
        pwd.erase();
        server->recvMessage(pwd);
        pwd.erase(pwd.end() - 1);
        // confirmPwd(pwd);
        output << "请再次输入密码确认:\n2";
        server->sendMessage(output);
        confirm.erase();
        // confirmPwd(confirm);
        server->recvMessage(confirm);
        confirm.erase(confirm.end() - 1);
        if (pwd == confirm)
            break;
        else
            output << "两次密码不一致，请重新输入！\n";
    }
    password = pwd;
    accInfo[num].pwd = pwd;
    output << "修改成功！\n1";
    server->sendMessage(output);
}

/* void User::confirmPwd(std::string &tmpPwd)  //确认密码，实现用*代替字符
{
    while (1)
    {
        char ch;
        ch = _getch();      //读取一个字符并且不显示到屏幕上
        if (ch == VK_BACK)  //输入backspace
        {
            if (!tmpPwd.empty())
            {
                output << "\b \b" << std::flush;
                tmpPwd.erase(tmpPwd.length() - 1);  // 清除掉读入的上一个字符
            }
        }
        else if (ch == VK_RETURN)  // 输入回车
        {
            output << std::endl;
            break;
        }
        else
        {
            tmpPwd += ch;  // 读入字符
            _putch('*');   // 输出*
        }
    }
} */

double User::queryBalance() const
{
    return balance;
}
void User::topUpAndDown()
{
    output << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
    double money;
    output << "请输入充值或消费金额:(正数表示充值，负数表示消费)\n";
    server->sendMessage(output);
    while (1)
    {
        input(money);
        if (balance + money < 0)
            output << "余额不能为负，请重新输入\n";
        else
            break;
    }
    balance += money;
    accInfo[num].bala = balance;
    output << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl << '1';
    server->sendMessage(output);
}
void User::transferPayments()
{
    std::string tmp = name;
    if (finalOrder.empty())
    {
        output << "没有订单需要支付\n1";
        server->sendMessage(output);
        return;
    }
    if (myorder.getToatalPrice() > balance)
    {
        output << "余额不足，请充值后付款\n1";
        server->sendMessage(output);
        return;
    }
    for (auto it : finalOrder)
    {
        int pos = search(it.first.merchant);
        double singlePrice = it.first.price * it.first.discount * it.second;
        accInfo[pos].bala += singlePrice;
        // 修改数量
        balance -= singlePrice;
    }
    finalOrder.clear();
    output << "交易成功！\n1";
    server->sendMessage(output);
    int pos = search(name);
    accInfo[pos].bala = balance;
    myorder.clearPrice();
    return;
}
void User::orderManagement(std::vector<GoodsInfo> &showGoods, std::vector<GoodsInfo> &goodsInfo)
{
    int choice;
    myorder.setName(name);
    while (1)
    {
        output << "请选择操作\n"
               << "1. 加入购物车\n"
               << "2. 展示购物车\n"
               << "3. 修改购物车信息\n"
               << "4. 生成订单\n"
               << "5. 展示订单\n"
               << "6. 支付订单\n"
               << "7. 取消订单\n"
               << "其他数字 退出\n";
        server->sendMessage(output);
        input(choice);
        /* std::string buff;
        server->recvMessage(buff);
        choice = std::stoi(buff); */
        if (choice < 1 || choice > 7)
            return;
        switch (choice)
        {
            case 1:
                myorder.preAddGoods(showGoods, goodsInfo);
                break;
            case 2:
                myorder.showShoppingCart();
                break;
            case 3:
                myorder.deleteGoods();
                break;
            case 4:
                if (finalOrder.empty())
                    myorder.generateOrder(finalOrder, goodsInfo);
                else
                {
                    output << "请支付上一个订单后再生成订单!\n1";
                    server->sendMessage(output);
                }
                break;
            case 5:
                showOrder();
                break;
            case 6:
                transferPayments();
                break;
            case 7:
                cancelOrder(goodsInfo);
                break;
            default:
                break;
        }
    }
}
void User::showOrder()
{
    if (finalOrder.empty())
    {
        output << "没有订单！\n1";
        server->sendMessage(output);
        return;
    }
    output << "您的订单如下：\n";
    output << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8) << std::left
           << "购买数量" << std::setw(20) << std::left << "商家" << std::endl;
    for (auto it : finalOrder)
    {
        output << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left
               << it.first.price * it.first.discount << std::setw(8) << std::left << it.second << std::setw(20)
               << std::left << it.first.merchant << std::endl;
    }
    output << '1';
    server->sendMessage(output);
}
void User::cancelOrder(std::vector<GoodsInfo> &goodsInfo)
{
    if (finalOrder.empty())
    {
        output << "没有订单，已退出\n1";
        server->sendMessage(output);
        return;
    }
    for (auto it : finalOrder)
        myorder.preorderGoods(goodsInfo, it.first.name, it.first.merchant, 0);
    output << "订单已取消！\n1";
    server->sendMessage(output);
}
void User::input(double &x)
{
    std::string tmp;
    server->recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    if (tmp.empty())
    {
        x = -1;
        return;
    }
    while (!isDouble(tmp))
    {
        output << "输入不合法，请输入数字\n";
        server->sendMessage(output);
        server->recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
    }
    if (!tmp.empty())
        x = std::stod(tmp);
}
void User::input(int &x)
{
    std::string tmp;
    server->recvMessage(tmp);
    tmp.erase(tmp.end() - 1);
    if (tmp.empty())
    {
        x = -1;
        return;
    }
    while (!isInt(tmp))
    {
        output << "输入不合法，请输入数字\n";
        server->sendMessage(output);
        server->recvMessage(tmp);
        tmp.erase(tmp.end() - 1);
        if (tmp.empty())
            break;
    }
    if (!tmp.empty())
        x = std::stoi(tmp);
}
bool User::isInt(const std::string &input) const
{
    std::regex rx("^\\-?\\d+$");  //+号表示多次匹配
    return std::regex_match(input, rx);
}
bool User::isDouble(const std::string &input) const
{
    std::regex rx("^\\-?\\d+(.\\d+)?$");
    return std::regex_match(input, rx);
}
void User::getShoppingCart(std::vector<std::pair<GoodsInfo, int>> &dest)
{
    myorder.getShoppingCart(dest);
}
void User::setShoppingCart(std::vector<std::pair<GoodsInfo, int>> &sou)
{
    myorder.setShoppingCart(sou);
}
void User::getFinalOrder(std::vector<std::pair<GoodsInfo, int>> &dest)
{
    dest = finalOrder;
}
void User::setFinalOrder(std::vector<std::pair<GoodsInfo, int>> &sou)
{
    finalOrder = sou;
}