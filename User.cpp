#include "User.hpp"
#include <algorithm>
#include <string>
#include <limits>
#include <iostream>
// 头文件用来实现星号显示密码
#include <conio.h>
#include <windows.h>

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
        std::cout << "该用户名已存在！\n";
        return;
    }
    AccInfo tmp;
    tmp.name = name;

    while (1)
    {
        std::cout << "输入密码:\n";
        std::string confirm;
        confirmPwd(tmp.pwd);
        std::cout << "请再次输入密码确认:\n";
        confirmPwd(confirm);
        if (tmp.pwd == confirm)  // 直至两次密码相同才设定成功
            break;
    }
    tmp.t = type;
    tmp.bala = 0;
    accInfo.emplace_back(tmp);
    std::cout << "注册成功!\n";
}
bool User::login(const int userType)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != userType)
        {
            std::cout << "用户类型错误，请退出重新选择！\n";
            return false;
        }
        std::string pwd;
        std::cout << "请输入密码:\n";
        confirmPwd(pwd);
        if (pwd != accInfo[pos].pwd)
        {
            std::cout << "密码错误!\n";
            return false;
        }
        else
        {
            std::cout << "登录成功!\n";
            password = pwd;
            this->type = userType;
            balance = accInfo[pos].bala;
            num = pos;
            return true;
        }
    }
    else
    {
        std::cout << "用户不存在!\n";
        return false;
    }
}
void User::changePwd()
{
    if (search(name) == -1)
    {
        std::cout << "用户不存在！";
        return;
    }
    std::string pwd;
    std::cout << "输入旧密码:\n";
    std::string confirm;
    confirmPwd(confirm);
    if (confirm != password)
    {
        std::cout << "密码错误，已退出！\n";
        return;
    }
    while (1)
    {
        std::cout << "输入新密码:\n";
        pwd.erase();
        confirmPwd(pwd);
        std::cout << "请再次输入密码确认:\n";
        confirm.erase();
        confirmPwd(confirm);
        if (pwd == confirm)
            break;
        else
            std::cout << "两次密码不一致，请重新输入！\n";
    }
    password = pwd;
    accInfo[num].pwd = pwd;
    std::cout << "修改成功！\n";
}

void User::confirmPwd(std::string &tmpPwd) const  //确认密码，实现用*代替字符
{
    while (1)
    {
        char ch;
        ch = _getch();      //读取一个字符并且不显示到屏幕上
        if (ch == VK_BACK)  //输入backspace
        {
            if (!tmpPwd.empty())
            {
                std::cout << "\b \b" << std::flush;
                tmpPwd.erase(tmpPwd.length() - 1);  // 清除掉读入的上一个字符
            }
        }
        else if (ch == VK_RETURN)  // 输入回车
        {
            std::cout << std::endl;
            break;
        }
        else
        {
            tmpPwd += ch;  // 读入字符
            _putch('*');   // 输出*
        }
    }
}
double User::queryBalance() const
{
    return balance;
}
void User::topUpAndDown()
{
    std::cout << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
    double money;
    std::cout << "请输入充值或消费金额:(正数表示充值，负数表示消费)\n";
    while (1)
    {
        input(money);
        if (balance + money < 0)
            std::cout << "余额不能为负，请重新输入\n";
        else
            break;
    }
    balance += money;
    accInfo[num].bala = balance;
    std::cout << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
}
void User::transferPayments()
{
    std::string tmp = name;
    if (finalOrder.empty())
    {
        std::cout << "没有订单需要支付\n";
        return;
    }
    if (myorder.getToatalPrice() > balance)
    {
        std::cout << "余额不足，请充值后付款\n";
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
    std::cout << "交易成功！\n";
    int pos = search(name);
    accInfo[pos].bala = balance;
    myorder.clearPrice();
    return;
}
void User::orderManagement(std::vector<GoodsInfo> &showGoods)
{
    int choice;
    myorder.setName(name);
    while (1)
    {
        std::cout << "请选择操作\n"
                  << "1. 加入购物车\n"
                  << "2. 展示购物车\n"
                  << "3. 修改购物车信息\n"
                  << "4. 生成订单\n"
                  << "5. 展示订单\n"
                  << "6. 支付订单\n"
                  << "7. 取消订单\n"
                  << "其他数字 退出\n";
        input(choice);
        if (choice < 1 || choice > 6)
            return;
        switch (choice)
        {
            case 1:
                myorder.preAddGoods(showGoods);
                break;
            case 2:
                myorder.showShoppingCart();
                break;
            case 3:
                myorder.deleteGoods();
                break;
            case 4:
                if (finalOrder.empty())
                    myorder.generateOrder(finalOrder);
                else
                    std::cout << "请支付上一个订单后再生成订单!\n";
                break;
            case 5:
                showOrder();
                break;
            case 6:
                transferPayments();
                break;
            case 7:
                cancelOrder();
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
        std::cout << "没有订单！\n";
        return;
    }
    std::cout << "您的订单如下：\n";
    std::cout << std::setw(20) << std::left << "名称" << std::setw(8) << std::left << "价格" << std::setw(8)
              << std::left << "购买数量" << std::setw(20) << std::left << "商家" << std::endl;
    for (auto it : finalOrder)
    {
        std::cout << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left
                  << it.first.price * it.first.discount << std::setw(8) << std::left << it.second << std::setw(20)
                  << std::left << it.first.merchant << std::endl;
    }
}
void User::cancelOrder()
{
    if (finalOrder.empty())
    {
        std::cout << "没有订单，已退出\n";
        return;
    }
    for (auto it : finalOrder)
        myorder.changeAmountOfGoods(it.first.name, it.first.merchant, it.first.type, -it.second);
}
template <typename T> void User::input(T &x) const
{
    std::cin >> x;
    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "输入不合法，请输入数字\n";
        std::cin >> x;
        continue;
    }
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
/* void User::exchangeMoney(const std::string &merchant, const double total)
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
}*/