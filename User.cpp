#include "User.hpp"
#include <string>

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
    std::cout << "Please enter the password:\n";
    std::cin >> accSet[num]->pwd;
    accSet[num]->t = type;
    accSet[num]->bala = 0;
    accInfo.insert(*accSet[num]);
    std::cout << "Register Succeed!\n";
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
        std::cout << "Input the password of the account:\n";
        std::cin >> pwd;
        if (pwd != acc->pwd)
        {
            std::cout << "Wrong password!\n";
            return false;
        }
        else
        {
            std::cout << "Successfully logged in!\n";
            return true;
            // logged = true;
        }
    }
    else
    {
        std::cout << "The account does not exist!\n";
        return false;
    }
}
void User::changePwd()
{
    if (!search())
    {
        std::cout << "This account doesn't exist.";
        return;
    }
    accSet[num] = new AccInfo;
    accSet[num]->name = name;
    accSet[num]->bala = acc->bala;
    accSet[num]->t = acc->t;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    std::cout << "Please enter the new password:\n";
    std::cin >> accSet[num]->pwd;
    accInfo.insert(*accSet[num]);
    num++;
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
    search();  // acc被清除掉了
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