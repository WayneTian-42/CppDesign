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

bool User::search()
{
    AccInfo tmp;
    tmp.name = name;
    auto st = accInfo.find(tmp);
    if (st != accInfo.end())
        acc = st;
    return (st != accInfo.end());
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
void User::login()
{
    if (search())
    {
        std::string pwd;
        std::cout << "Input the password of the account:\n";
        std::cin >> pwd;
        if (pwd != acc->pwd)
        {
            std::cout << "Wrong password!\n";
        }
        else
        {
            std::cout << "Successfully logged in!\n";
            // logged = true;
        }
    }
    else
    {
        std::cout << "The account does not exist!\n";
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
void User::queryBalance()
{
    if (!search())
    {
        std::cout << "This account doesn't exist.";
    }
    std::cout << "账户余额为" << acc->bala << "元";
}
void User::buySth()
{
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