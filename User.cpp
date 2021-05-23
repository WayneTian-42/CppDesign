#include "User.hpp"
#include <algorithm>
#include <string>
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
        std::cout << "���û����Ѵ��ڣ�\n";
        return;
    }
    AccInfo tmp;
    tmp.name = name;

    // std::cin >> accSet[num]->pwd;
    while (1)
    {
        std::cout << "��������:\n";
        std::string confirm;
        confirmPwd(tmp.pwd);
        std::cout << "���ٴ���������ȷ��:\n";
        confirmPwd(confirm);
        if (tmp.pwd == confirm)
            break;
    }
    tmp.t = type;
    tmp.bala = 0;
    accInfo.emplace_back(tmp);
    std::cout << "ע��ɹ�!\n";
}
bool User::login(const int type)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != type)
        {
            std::cout << "�û����ʹ������˳�����ѡ��\n";
            return false;
        }
        std::string pwd;
        std::cout << "����������:\n";
        confirmPwd(pwd);
        if (pwd != accInfo[pos].pwd)
        {
            std::cout << "�������!\n";
            return false;
        }
        else
        {
            std::cout << "��¼�ɹ�!\n";
            password = pwd;
            this->type = type;
            balance = accInfo[pos].bala;
            num = pos;
            return true;
            // logged = true;
        }
    }
    else
    {
        std::cout << "�˺Ų�����!\n";
        return false;
    }
}
void User::changePwd()
{
    if (search(name) == -1)
    {
        std::cout << "�˺Ų����ڣ�";
        return;
    }
    std::string pwd;
    std::cout << "���������:\n";
    std::string confirm;
    confirmPwd(confirm);
    if (confirm != password)
    {
        std::cout << "����������˳���\n";
        return;
    }
    while (1)
    {
        std::cout << "����������:\n";
        pwd.erase();
        confirmPwd(pwd);
        std::cout << "���ٴ���������ȷ��:\n";
        confirm.erase();
        confirmPwd(confirm);
        if (pwd == confirm)
            break;
        else
            std::cout << "�������벻һ�£����������룡\n";
    }
    password = pwd;
    accInfo[num].pwd = pwd;
    std::cout << "�޸ĳɹ���\n";
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
    std::cout << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
    double money;
    std::cout << "�������ֵ��";
    std::cin >> money;
    balance += money;
    accInfo[num].bala = balance;
    std::cout << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
}
/* void User::exchangeMoney(const std::string &merchant, const double total)
{
    search(merchant);
    accSet[num] = new AccInfo;
    tmpname = merchant;
    tmpbala = acc->bala + total;
    tmpt = acc->t;
    tmppwd = acc->pwd;
    // accSet[num]��δ�ͷŵ�
    accInfo.erase(acc);
    accInfo.insert(*accSet[num]);

    search();
    accSet[num] = new AccInfo;
    tmpname = name;
    tmpbala = acc->bala - total;
    tmpt = acc->t;
    tmppwd = acc->pwd;
    // accSet[num]��δ�ͷŵ�
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