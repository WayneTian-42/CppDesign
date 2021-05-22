#include "User.hpp"
#include <algorithm>
#include <string>
#include <limits>
#include <iostream>
// ͷ�ļ�����ʵ���Ǻ���ʾ����
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
    num++;
}
bool User::login(const int type)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != type)
        {
            std::cout << "�˻����ʹ������˳�����ѡ��";
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
    AccInfo tmp;
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
        tmp.pwd.erase();
        confirmPwd(tmp.pwd);
        std::cout << "���ٴ���������ȷ��:\n";
        confirm.erase();
        confirmPwd(confirm);
        if (tmp.pwd == confirm)
            break;
        else
            std::cout << "�������벻һ�£����������룡\n";
    }
    accInfo[num].pwd = tmp.pwd;
    std::cout << "�޸ĳɹ���\n";

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
    std::cout << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
    double money;
    std::cout << "�������ֵ��";
    std::cin >> money;
    balance += money;
    accInfo[num].bala = balance;
    std::cout << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
}
void User::transferPayments()
{
    std::string tmp = name;
    if (myorder.getToatalPrice() > balance)
    {
        std::cout << "���㣬���ֵ�󸶿�";
        return;
    }
    for (auto it : finalOrder)
    {
        int pos = search(it.first.merchant);
        double singlePrice = it.first.price * it.first.amount * it.second;
        accInfo[pos].bala += singlePrice;
        // �޸�����
        balance -= singlePrice;
    }
    std::vector<std::pair<GoodsInfo, int>> temp;
    finalOrder.swap(temp);
    int pos = search(name);
    accInfo[pos].bala = balance;
}
void User::orderManagement(std::vector<GoodsInfo> &showGoods)
{
    std::cout << "��ѡ�����\n"
              << "1. ���빺�ﳵ\n"
              << "2. չʾ���ﳵ\n"
              << "3. �޸Ĺ��ﳵ��Ϣ\n"
              << "4. ���ɶ���\n"
              << "�������� �˳�\n";
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
        std::cout << "���벻�Ϸ�������������\n";
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