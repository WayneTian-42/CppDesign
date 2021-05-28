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

void User::confirmPwd(std::string &tmpPwd) const  //ȷ�����룬ʵ����*�����ַ�
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
double User::queryBalance() const
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
    if (finalOrder.empty())
    {
        std::cout << "û�ж�����Ҫ֧��\n";
        return;
    }
    if (myorder.getToatalPrice() > balance)
    {
        std::cout << "���㣬���ֵ�󸶿�\n";
        return;
    }
    for (auto it : finalOrder)
    {
        int pos = search(it.first.merchant);
        double singlePrice = it.first.price * it.first.discount * it.second;
        accInfo[pos].bala += singlePrice;
        // �޸�����
        balance -= singlePrice;
    }
    finalOrder.clear();
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
    while (1)
    {
        std::cout << "��ѡ�����\n"
                  << "1. ���빺�ﳵ\n"
                  << "2. չʾ���ﳵ\n"
                  << "3. �޸Ĺ��ﳵ��Ϣ\n"
                  << "4. ���ɶ���\n"
                  << "5. չʾ����\n"
                  << "6. ֧������\n"
                  << "7. ȡ������\n"
                  << "�������� �˳�\n";
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
                    std::cout << "��֧����һ�������������ɶ���!\n";
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
        std::cout << "û�ж�����\n";
        return;
    }
    std::cout << "���Ķ������£�\n";
    std::cout << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8)
              << std::left << "��������" << std::setw(20) << std::left << "�̼�" << std::endl;
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
        std::cout << "û�ж��������˳�\n";
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
        std::cout << "���벻�Ϸ�������������\n";
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
        std::cout << "���벻�Ϸ�������������\n";
        std::cin >> x;
        continue;
    }
}*/