#include "User.hpp"
#include <string>
#include <conio.h>
#include <windows.h>

bool AccInfo::operator<(const AccInfo &ac) const
{
    if (this->name == ac.name)
        return false;
    if (this->name < ac.name)
        return true;
    else
        return false;
};

bool User::search()
{
    AccInfo tmp;
    tmp.name = name;
    auto st = accInfo.find(tmp);
    if (st != accInfo.end())
        acc = st;
    return (st != accInfo.end());
}
void User::search(const std::string &name)
{
    AccInfo tmp;
    tmp.name = name;
    auto st = accInfo.find(tmp);
    if (st != accInfo.end())
        acc = st;
}
void User::userRegister()
{
    if (search())
    {
        std::cout << "该用户名已存在！\n";
        return;
    }
    accSet[num] = new AccInfo;
    accSet[num]->name = name;

    // std::cin >> accSet[num]->pwd;
    while (1)
    {
        std::cout << "输入密码:\n";
        std::string confirm;
        confirmPwd(accSet[num]->pwd);
        std::cout << "请再次输入密码确认:\n";
        confirmPwd(confirm);
        if (accSet[num]->pwd == confirm)
            break;
    }
    accSet[num]->t = type;
    accSet[num]->bala = 0;
    accInfo.insert(*accSet[num]);
    std::cout << "注册成功!\n";
    num++;
}
bool User::login(const int type)
{
    if (search())
    {
        if (acc->t != type)
        {
            std::cout << "账户类型错误，请退出重新选择！";
            return false;
        }
        std::string pwd;
        std::cout << "请输入密码:\n";
        confirmPwd(pwd);
        if (pwd != acc->pwd)
        {
            std::cout << "密码错误!\n";
            return false;
        }
        else
        {
            std::cout << "登录成功!\n";
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
    if (!search())
    {
        std::cout << "账号不存在！";
        return;
    }
    accSet[num] = new AccInfo;
    accSet[num]->name = name;
    accSet[num]->bala = acc->bala;
    accSet[num]->t = acc->t;
    accSet[num]->pwd = acc->pwd;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    std::cout << "输入旧密码:\n";
    std::string confirm;
    confirmPwd(confirm);
    if (confirm != acc->pwd)
    {
        std::cout << "密码错误，已退出！\n";
        delete accSet[num];
        return;
    }
    while (1)
    {
        std::cout << "输入新密码:\n";
        accSet[num]->pwd.erase();
        confirmPwd(accSet[num]->pwd);
        std::cout << "请再次输入密码确认:\n";
        confirm.erase();
        confirmPwd(confirm);
        if (accSet[num]->pwd == confirm)
            break;
        else
            std::cout << "两次密码不一致，请重新输入！\n";
    }
    std::cout << "修改成功！\n";
    accInfo.insert(*accSet[num]);
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

    return acc->bala;
}
void User::topUp()
{
    std::cout << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
    double money;
    std::cout << "请输入充值金额：";
    std::cin >> money;
    accSet[num] = new AccInfo;
    accSet[num]->name = name;
    accSet[num]->bala = acc->bala + money;
    accSet[num]->pwd = acc->pwd;
    accSet[num]->t = acc->t;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    accInfo.insert(*accSet[num]);
    num++;
    search();  // acc被清除掉了,好像不会清除掉
    std::cout << name << "，您账户当前余额为" << queryBalance() << "元" << std::endl;
}
void User::exchangeMoney(const std::string &merchant, const double total)
{
    search(merchant);
    accSet[num] = new AccInfo;
    accSet[num]->name = merchant;
    accSet[num]->bala = acc->bala + total;
    accSet[num]->t = acc->t;
    accSet[num]->pwd = acc->pwd;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    accInfo.insert(*accSet[num]);
    num++;

    search();
    accSet[num] = new AccInfo;
    accSet[num]->name = name;
    accSet[num]->bala = acc->bala - total;
    accSet[num]->t = acc->t;
    accSet[num]->pwd = acc->pwd;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    accInfo.insert(*accSet[num]);
    num++;
}
void User::save()
{
    // logged = false;
    // name.clear();
    accfp.close();
    accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt", std::ios::out | std::ios::trunc);
    accfp.seekg(0, std::fstream::beg);
    for (auto st : accInfo)
        accfp << st.name << " " << st.pwd << " " << st.t << " " << st.bala << std::endl;
    accfp.close();
}