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

int User::search(const std::string &name)
{
    AccInfo tmp;
    int pos = -1;
    tmp.name = name;
    auto st = std::find(accInfo.begin(), accInfo.end(), tmp);
    if (st != accInfo.end())
        pos = st - accInfo.begin();
    return pos;
}
void User::userRegister()
{
    if (search(name) == -1)
    {
        std::cout << "该用户名已存在！\n";
        return;
    }
    AccInfo tmp;
    tmp.name = name;

    // std::cin >> accSet[num]->pwd;
    while (1)
    {
        std::cout << "输入密码:\n";
        std::string confirm;
        confirmPwd(tmp.pwd);
        std::cout << "请再次输入密码确认:\n";
        confirmPwd(confirm);
        if (tmp.pwd == confirm)
            break;
    }
    tmp.t = type;
    tmp.bala = 0;
    accInfo.emplace_back(tmp);
    std::cout << "注册成功!\n";
    num++;
}
bool User::login(const int type)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != type)
        {
            std::cout << "账户类型错误，请退出重新选择！";
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
            this->type = type;
            balance = accInfo[pos].bala;
            return true;
            // logged = true;
        }
    }
    else
    {
        std::cout << "账号不存在!\n";
        return false;
    }
}
void User::changePwd()
{
    if (search(name) == -1)
    {
        std::cout << "账号不存在！";
        return;
    }
    AccInfo tmp;
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
        tmp.pwd.erase();
        confirmPwd(tmp.pwd);
        std::cout << "请再次输入密码确认:\n";
        confirm.erase();
        confirmPwd(confirm);
        if (tmp.pwd == confirm)
            break;
        else
            std::cout << "两次密码不一致，请重新输入！\n";
    }
    accInfo[num].pwd = tmp.pwd;
    std::cout << "修改成功！\n";

    num++;
}
void User::confirmPwd(std::string &pwd)
{
    while (1)
    {
        char ch;
        ch = _getch();
        if (ch == VK_BACK)
        {
            if (!pwd.empty())
            {
                std::cout << "\b \b" << std::flush;
                pwd.erase(pwd.length() - 1);
            }
        }
        else if (ch == VK_RETURN)
        {
            std::cout << std::endl;
            break;
        }
        else
        {
            pwd += ch;
            _putch('*');
        }
    }
}
double User::queryBalance(const double consume)
{
    /* if (!search())
    {
        std::cout << "This account doesn't exist.";
    } */

    return balance;
}
void User::topUp()
{
    std::cout << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
    double money;
    std::cout << "请输入充值金额：";
    std::cin >> money;
    balance += money;
    accInfo[num].bala = balance;
    std::cout << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
}
void User::transferPayments()
{
    std::string tmp = name;
    if (myorder.getToatalPrice() > balance)
    {
        std::cout << "余额不足，请充值后付款";
        return;
    }
    for (auto it : finalOrder)
    {
        int pos = search(it.first.merchant);
        double singlePrice = it.first.price * it.first.amount * it.second;
        accInfo[pos].bala += singlePrice;
        // 修改数量
        balance -= singlePrice;
    }
    std::vector<std::pair<GoodsInfo, int>> temp;
    finalOrder.swap(temp);
    int pos = search(name);
    accInfo[pos].bala = balance;
}
void User::orderManagement(std::vector<GoodsInfo> &showGoods)
{
    std::cout << "请选择操作\n"
              << "1. 加入购物车\n"
              << "2. 展示购物车\n"
              << "3. 修改购物车信息\n"
              << "4. 生成订单\n"
              << "其他数字 退出\n";
    int choice;
    input(choice);
    if (choice < 1 || choice > 4)
        return;
    switch (choice)
    {
        case 1:
            myorder.preAddGoods(showGoods);
            break;
        case 2:
            myorder.showOrder();
            break;
        case 3:
            myorder.deleteGoods();
            break;
        case 4:
            myorder.generateOrder(finalOrder);
            break;
        default:
            break;
    }
}

void User::input(int &x) const
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
/* void User::exchangeMoney(const std::string &merchant, const double total)
{
    search(merchant);
    accSet[num] = new AccInfo;
    tmpname = merchant;
    tmpbala = acc->bala + total;
    tmpt = acc->t;
    tmppwd = acc->pwd;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    accInfo.insert(*accSet[num]);

    search();
    accSet[num] = new AccInfo;
    tmpname = name;
    tmpbala = acc->bala - total;
    tmpt = acc->t;
    tmppwd = acc->pwd;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    accInfo.insert(*accSet[num]);
} */
/* void User::save()
{
    // logged = false;
    // name.clear();
    accfp.close();
    accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt", std::ios::out | std::ios::trunc);
    accfp.seekg(0, std::fstream::beg);
    for (auto st : accInfo)
        accfp << st.name << " " << st.pwd << " " << st.t << " " << st.bala << std::endl;
    accfp.close();
} */