#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Ex1.hpp"

std::set<AccInfo> accInfo;
std::set<GoodsInfo> goodsInfo;

bool AccInfo::operator<(const AccInfo &ac) const
{
    if (this->name == ac.name)
        return false;
    if (this->name < ac.name)
        return true;
    else
        return false;
};
bool Account::registerAcc()
{
    accSet[num] = new AccInfo;
    accSet[num]->name = userName;
    auto it = accInfo.find(*accSet[num]);
    if (it != accInfo.end())
        return false;

    std::cout << "Please enter the password:\n";
    std::cin >> accSet[num]->pwd;
    std::cout << "Please enter the type of the account, "
              << "0 for merchants and 1 for customers\n";
    std::cin >> accSet[num]->t;
    accSet[num]->bala = 0;
    accInfo.insert(*accSet[num]);
    record(accSet[num], 0);
    std::cout << "Register Succeed!\n";
    num++;
    return true;
}
void Account::changePwd()  // set容器修改元素，先删除再插入
{
    accSet[num] = new AccInfo;
    accSet[num]->name = userName;
    auto it = accInfo.find(*accSet[num]);
    if (it == accInfo.end())
    {
        std::cout << "This account doesn't exist.";
        delete accSet[num];
        return;
    }
    accSet[num]->bala = it->bala;
    accSet[num]->t = it->t;
    accInfo.erase(*accSet[num]);
    std::cout << "Please enter the new password:\n";
    std::cin >> accSet[num]->pwd;
    accInfo.insert(*accSet[num]);
    record(accSet[num], 1);
    num++;
}
void Account::record(const AccInfo *tmp, const int &mode)
{
    if (!mode)
    {
        accfp.seekg(0, std::fstream::end);
        accfp << tmp->name << " " << tmp->pwd << " " << tmp->t << " " << tmp->bala << std::endl;
    }
    else
    {
        int flg = 1;
        char tmpLineData[1024] = {0};
        std::string tmpName;
        accfp.seekg(0, std::fstream::beg);
        while (flg)
        {
            accfp >> tmpName;
            if (tmpName == userName)
            {
                flg = 0;
                accfp << tmp->name << " " << tmp->pwd << " " << tmp->t << " " << tmp->bala << std::flush;
                accfp.getline(tmpLineData, sizeof(tmpLineData));
                int rest = sizeof(tmpLineData);
                accfp.seekg(-rest, std::fstream::cur);
                for (int i = 0; i < rest; i++)
                    tmpLineData[i] = ' ';
                accfp << tmpLineData;
            }
            else
            {
                accfp.getline(tmpLineData, sizeof(tmpLineData));
            }
        }
    }
}
Account::~Account()
{
}