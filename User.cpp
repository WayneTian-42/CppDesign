#include "User.hpp"
#include <algorithm>
#include <limits>
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
    if (search(name) == -1)
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
template <typename T> void User::input(T &x) const
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
}