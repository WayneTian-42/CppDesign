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

int User::search(const std::string &userName)
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
        std::cout << "���û����Ѵ��ڣ�\n";
        return;
    }
    AccInfo tmp;
    tmp.name = name;

    while (1)
    {
        std::cout << "��������:\n";
        std::string confirm;
        confirmPwd(tmp.pwd);
        std::cout << "���ٴ���������ȷ��:\n";
        confirmPwd(confirm);
        if (tmp.pwd == confirm)  // ֱ������������ͬ���趨�ɹ�
            break;
    }
    tmp.t = type;
    tmp.bala = 0;
    accInfo.emplace_back(tmp);
    std::cout << "ע��ɹ�!\n";
}
bool User::login(const int userType)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != userType)
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
            this->type = userType;
            balance = accInfo[pos].bala;
            num = pos;
            return true;
        }
    }
    else
    {
        std::cout << "�û�������!\n";
        return false;
    }
}
void User::changePwd()
{
    if (search(name) == -1)
    {
        std::cout << "�û������ڣ�";
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

void User::confirmPwd(std::string &tmpPwd)  //ȷ�����룬ʵ����*�����ַ�
{
    while (1)
    {
        char ch;
        ch = _getch();      //��ȡһ���ַ����Ҳ���ʾ����Ļ��
        if (ch == VK_BACK)  //����backspace
        {
            if (!tmpPwd.empty())
            {
                std::cout << "\b \b" << std::flush;
                tmpPwd.erase(tmpPwd.length() - 1);  // ������������һ���ַ�
            }
        }
        else if (ch == VK_RETURN)  // ����س�
        {
            std::cout << std::endl;
            break;
        }
        else
        {
            tmpPwd += ch;  // �����ַ�
            _putch('*');   // ���*
        }
    }
}
double User::queryBalance()
{
    return balance;
}
void User::topUpAndDown()
{
    std::cout << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
    double money;
    std::cout << "�������ֵ�����ѽ��:(������ʾ��ֵ��������ʾ����)\n";
    while (1)
    {
        input(money);
        if (balance + money < 0)
            std::cout << "����Ϊ��������������\n";
        else
            break;
    }
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
        double singlePrice = it.first.price * it.first.discount * it.second;
        accInfo[pos].bala += singlePrice;
        // �޸�����
        balance -= singlePrice;
        myorder.changeAmountOfGoods(it.first.name, it.first.merchant, it.first.type, it.second);
    }
    std::cout << "���׳ɹ���\n";
    int pos = search(name);
    accInfo[pos].bala = balance;
    myorder.clearPrice();
    return;
}
void User::orderManagement(std::vector<GoodsInfo> &showGoods)
{
    int choice;
    myorder.setName(name);
    do
    {
        std::cout << "��ѡ�����\n"
                  << "1. ���빺�ﳵ\n"
                  << "2. չʾ���ﳵ\n"
                  << "3. �޸Ĺ��ﳵ��Ϣ\n"
                  << "4. ���ɶ���\n"
                  << "�������� �˳�\n";
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
                myorder.generateOrder(finalOrder, balance);
                transferPayments();
                break;
            default:
                break;
        }
    } while (choice < 5 && choice > 0);
}

void User::getFinalOrder(std::vector<std::pair<GoodsInfo, int>> &des)
{
    des = finalOrder;
}
template <typename T> void User::input(T &x) const
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
void User::setOrder(std::vector<std::pair<GoodsInfo, int>> &tmp)
{
    myorder.setOrder(tmp);
}
void User::quitToGetOrder(std::vector<std::pair<GoodsInfo, int>> &tmp)
{
    myorder.getPreorder(tmp);
}
/* void User::exchangeMoney(const std::string &merchant, const double total)
{
    std::cin >> x;
    while (std::cin.fail() || std::cin.get() != '\n')
    {
        std::cin.clear();
        std::cin.ignore(LLONG_MAX, '\n');
        std::cout << "���벻�Ϸ�������������\n";
        std::cin >> x;
        continue;
    }
}*/