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
        output << "���û����Ѵ��ڣ�\n";
        server->sendMessage(output);
        return;
    }
    AccInfo tmp;
    tmp.name = name;

    while (1)
    {
        output << "��������:\n";
        server->sendMessage(output);
        std::string confirm;
        // confirmPwd(tmp.pwd);
        server->recvMessage(tmp.pwd);
        tmp.pwd.erase(tmp.pwd.end() - 1);
        output << "���ٴ���������ȷ��:\n";
        server->sendMessage(output);
        server->recvMessage(confirm);
        confirm.erase(confirm.end() - 1);
        // confirmPwd(confirm);
        if (tmp.pwd == confirm)  // ֱ������������ͬ���趨�ɹ�
            break;
    }
    tmp.t = type;
    tmp.bala = 0;
    accInfo.emplace_back(tmp);
    output << "ע��ɹ�!\n";
    server->sendMessage(output);
}
bool User::login(const int userType)
{
    int pos = search(name);
    if (pos != -1)
    {
        if (accInfo[pos].t != userType)
        {
            output << "�û����ʹ������˳�����ѡ��\n";
            server->sendMessage(output);
            return false;
        }
        std::string pwd;
        output << "����������:\n";
        server->sendMessage(output);
        // confirmPwd(pwd);
        server->recvMessage(pwd);
        pwd.erase(pwd.end() - 1);
        if (pwd != accInfo[pos].pwd)
        {
            output << "�������!\n";
            server->sendMessage(output);
            return false;
        }
        else
        {
            output << "��¼�ɹ�!\n";
            server->sendMessage(output);
            password = pwd;
            this->type = userType;
            balance = accInfo[pos].bala;
            num = pos;
            return true;
        }
    }
    else
    {
        output << "�û�������!\n";
        server->sendMessage(output);
        return false;
    }
}
void User::changePwd()
{
    if (search(name) == -1)
    {
        output << "�û������ڣ�";
        server->sendMessage(output);
        return;
    }
    std::string pwd;
    output << "���������:\n";
    server->sendMessage(output);
    std::string confirm;
    // confirmPwd(confirm);
    server->recvMessage(confirm);
    confirm.erase(confirm.end() - 1);
    if (confirm != password)
    {
        output << "����������˳���\n";
        return;
    }
    while (1)
    {
        output << "����������:\n";
        server->sendMessage(output);
        pwd.erase();
        server->recvMessage(pwd);
        pwd.erase(pwd.end() - 1);
        // confirmPwd(pwd);
        output << "���ٴ���������ȷ��:\n";
        server->sendMessage(output);
        confirm.erase();
        // confirmPwd(confirm);
        server->recvMessage(confirm);
        confirm.erase(confirm.end() - 1);
        if (pwd == confirm)
            break;
        else
            output << "�������벻һ�£����������룡\n";
    }
    password = pwd;
    accInfo[num].pwd = pwd;
    output << "�޸ĳɹ���\n";
    server->sendMessage(output);
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
                output << "\b \b" << std::flush;
                tmpPwd.erase(tmpPwd.length() - 1);  // ������������һ���ַ�
            }
        }
        else if (ch == VK_RETURN)  // ����س�
        {
            output << std::endl;
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
    output << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
    double money;
    output << "�������ֵ�����ѽ��:(������ʾ��ֵ��������ʾ����)\n";
    server->sendMessage(output);
    while (1)
    {
        // input(money);
        std::string buff;
        server->recvMessage(buff);
        money = std::stoi(buff);
        if (balance + money < 0)
            output << "����Ϊ��������������\n";
        else
            break;
    }
    balance += money;
    accInfo[num].bala = balance;
    output << name << "�����˻���ǰ���Ϊ" << queryBalance() << "Ԫ" << std::endl;
    server->sendMessage(output);
}
void User::transferPayments()
{
    std::string tmp = name;
    if (finalOrder.empty())
    {
        output << "û�ж�����Ҫ֧��\n";
        server->sendMessage(output);
        return;
    }
    if (myorder.getToatalPrice() > balance)
    {
        output << "���㣬���ֵ�󸶿�\n";
        server->sendMessage(output);
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
    output << "���׳ɹ���\n";
    server->sendMessage(output);
    int pos = search(name);
    accInfo[pos].bala = balance;
    myorder.clearPrice();
    return;
}
void User::orderManagement(std::vector<GoodsInfo> &showGoods, std::vector<GoodsInfo> &goodsInfo)
{
    int choice;
    myorder.setName(name);
    while (1)
    {
        output << "��ѡ�����\n"
               << "1. ���빺�ﳵ\n"
               << "2. չʾ���ﳵ\n"
               << "3. �޸Ĺ��ﳵ��Ϣ\n"
               << "4. ���ɶ���\n"
               << "5. չʾ����\n"
               << "6. ֧������\n"
               << "7. ȡ������\n"
               << "�������� �˳�\n";
        server->sendMessage(output);
        // input(choice);
        std::string buff;
        server->recvMessage(buff);
        choice = std::stoi(buff);
        if (choice < 1 || choice > 7)
            return;
        switch (choice)
        {
            case 1:
                myorder.preAddGoods(showGoods, goodsInfo);
                break;
            case 2:
                myorder.showShoppingCart();
                break;
            case 3:
                myorder.deleteGoods();
                break;
            case 4:
                if (finalOrder.empty())
                    myorder.generateOrder(finalOrder, goodsInfo);
                else
                {
                    output << "��֧����һ�������������ɶ���!\n";
                    server->sendMessage(output);
                }
                break;
            case 5:
                showOrder();
                break;
            case 6:
                transferPayments();
                break;
            case 7:
                cancelOrder(goodsInfo);
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
        output << "û�ж�����\n";
        server->sendMessage(output);
        return;
    }
    output << "���Ķ������£�\n";
    output << std::setw(20) << std::left << "����" << std::setw(8) << std::left << "�۸�" << std::setw(8) << std::left
           << "��������" << std::setw(20) << std::left << "�̼�" << std::endl;
    for (auto it : finalOrder)
    {
        output << std::setw(20) << std::left << it.first.name << std::setw(8) << std::left
               << it.first.price * it.first.discount << std::setw(8) << std::left << it.second << std::setw(20)
               << std::left << it.first.merchant << std::endl;
    }
    server->sendMessage(output);
}
void User::cancelOrder(std::vector<GoodsInfo> &goodsInfo)
{
    if (finalOrder.empty())
    {
        output << "û�ж��������˳�\n";
        server->sendMessage(output);
        return;
    }
    for (auto it : finalOrder)
        myorder.preorderGoods(goodsInfo, it.first.name, it.first.merchant, 0);
    output << "������ȡ����\n";
    server->sendMessage(output);
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