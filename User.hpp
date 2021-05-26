#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include "Goods.hpp"

/**
 * @brief �洢�û���Ϣ����������������ʵ��std::find����
 *
 */
struct AccInfo
{
    std::string name, pwd;
    double bala;
    int t;
    bool operator==(const AccInfo &ac) const;
};

/**
 * @brief �û��࣬ʵ���й��û��ĸ��ֲ���
 *
 */
class User
{
  public:
    User() : type(0), balance(0)  // ���캯���������û�����
    {
        num = 0;
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt");
        if (!accfp)
        {
            std::cout << "���ļ�ʧ�ܣ�\n";
            return;
        }
        while (accfp.peek() != EOF)
        {
            AccInfo accTemp;
            accfp >> accTemp.name >> accTemp.pwd >> accTemp.t >> accTemp.bala;
            if (accTemp.name.empty())  // �Թ�����
                continue;
            else
                accInfo.emplace_back(accTemp);
        }
    }
    virtual ~User()  // �������������û����ݴ����ļ�
    {
        accfp.close();
        accfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\AccInfo.txt", std::ios::out | std::ios::trunc);
        accfp.seekg(0, std::fstream::beg);
        for (auto st : accInfo)
            accfp << st.name << " " << st.pwd << " " << st.t << " " << st.bala << std::endl;
        accfp.close();
    }

    virtual int getUserType() const = 0;            // ���麯���������û�����
    int search(const std::string &userName) const;  // �����û����Ƿ���ڣ������ڷ�����������λ��
    void userRegister();                            // �û�ע��
    bool login(const int userType);                 // �û���¼
    void changePwd();                               // �޸�����
    void confirmPwd(std::string &tmpPwd) const;     // ȷ�������Ƿ���ȷ
    double queryBalance() const;                    // ��ѯ���
    void topUpAndDown();                            // �޸����
    template <typename T> void input(T &x) const;   // �������

    //�޸�Ϊset get
  protected:
    std::string name, password;  // �û���������
    // bool logged;
    int type;        // �û�����
    double balance;  // �û����

  private:
    std::fstream accfp;            // �ļ�ָ��
    std::vector<AccInfo> accInfo;  // �����û���Ϣ������
    int num;                       // ���û����������±�
};

/**
 * @brief ����������
 *
 */
class Consumer : public User
{
  public:
    Consumer(const std::string s) : User()
    {
        name = s;
        type = 1;
    }
    virtual ~Consumer() override
    {
    }
    virtual int getUserType() const override
    {
        return type;
    }

  private:
};
/**
 * @brief ��������
 *
 */
class Merchant : public User
{
  public:
    Merchant(const std::string s) : User()
    {
        name = s;
        type = 2;
    }
    virtual ~Merchant() override
    {
    }
    virtual int getUserType() const override
    {
        return type;
    }

  private:
};
/**
 * @brief ����Ա���ͣ�ʵ�ֶ�ĳ��������Ʒ����
 *
 */
class Admin : public User
{
  public:
    Admin(const std::string s) : User()
    {
        name = s;
        type = 0;
    }
    virtual ~Admin() override
    {
    }
    virtual int getUserType() const override
    {
        return type;
    }
};