#include "User.hpp"

bool AccInfo::operator<(const AccInfo &ac) const
{
    if (this->name == ac.name)
        return false;
    if (this->name < ac.name)
        return true;
    else
        return false;
};

bool Account::search()
{
    AccInfo tmp;
    tmp.name = userName;
    auto st = accInfo.find(tmp);
    if (st != accInfo.end())
        acc = st;
    return (st != accInfo.end());
}
//只有账号存在才会调用该函数
bool Account::login(const std::string &input)
{
    bool flg = (input == acc->pwd);
    return flg;
}
bool Account::registerAcc()
{
    if (search())
        return false;
    accSet[num] = new AccInfo;
    accSet[num]->name = userName;
    std::cout << "Please enter the password:\n";
    std::cin >> accSet[num]->pwd;
    std::cout << "Please enter the type of the account, "
              << "0 for merchants and 1 for customers\n";
    std::cin >> accSet[num]->t;
    accSet[num]->bala = 0;
    accInfo.insert(*accSet[num]);
    std::cout << "Register Succeed!\n";
    num++;
    return true;
}
void Account::changePwd()  // set容器修改元素，先删除再插入
{
    if (!search())
    {
        std::cout << "This account doesn't exist.";
        return;
    }
    accSet[num] = new AccInfo;
    accSet[num]->name = userName;
    accSet[num]->bala = acc->bala;
    accSet[num]->t = acc->t;
    // accSet[num]并未释放掉
    accInfo.erase(acc);
    std::cout << "Please enter the new password:\n";
    std::cin >> accSet[num]->pwd;
    accInfo.insert(*accSet[num]);
    num++;
}
double Account::checkBalance()
{
    if (!search())
    {
        std::cout << "This account doesn't exist.";
        return 0;
    }
    return acc->bala;
}

void User::userRegister(const std::string &userName)
{
    Account tmp(userName);
    if (!tmp.registerAcc())
    {
        std::cout << "账户名已存在，请登录或注册新账户名.\n";
    }
}
void User::login(const std::string &userName)
{
    Account tmp(userName);
    if (tmp.search())
    {
        std::string pwd;
        std::cout << "Input the password of the account:\n";
        std::cin >> pwd;
        if (!tmp.login(pwd))
        {
            std::cout << "Wrong password!\n";
        }
        else
        {
            std::cout << "Successfully logged in!\n";
        }
    }
    else
    {
        std::cout << "The account does not exist!\n";
    }
}
void User::changePwd(const std::string &userName)
{
    Account tmp(userName);
    tmp.changePwd();
}
void User::queryBalance(const std::string &userName)
{
    Account tmp(userName);
    balance = tmp.checkBalance();
    std::cout << "该账户余额为" << balance << std::endl;
}
void User::buySth()
{
}