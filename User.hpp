#pragma once
#include <cstdlib>
#include "Goods.hpp"
#include "Order.hpp"

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

    virtual int getUserType() = 0;            // ���麯���������û�����
    int search(const std::string &userName);  // �����û����Ƿ���ڣ������ڷ�����������λ��
    void userRegister();                      // �û�ע��
    bool login(const int userType);           // �û���¼
    void changePwd();                         // �޸�����
    void confirmPwd(std::string &tmpPwd);     // ȷ�������Ƿ���ȷ
    double queryBalance();                    // ��ѯ���
    void topUpAndDown();                      // �޸����
    void orderManagement(std::vector<GoodsInfo> &);
    void getFinalOrder(std::vector<std::pair<GoodsInfo, int>> &);
    void transferPayments();
    void cancelOrder();
    void setOrder(std::vector<std::pair<GoodsInfo, int>> &, std::vector<std::pair<GoodsInfo, int>> &);
    void quitToGetOrder(std::vector<std::pair<GoodsInfo, int>> &, std::vector<std::pair<GoodsInfo, int>> &);
    template <typename T> void input(T &x) const;  // �������

    //�޸�Ϊset get
  protected:
    std::string name, password;  // �û���������
    // bool logged;
    int type;        // �û�����
    double balance;  // �û����
    Order myorder;
    std::vector<std::pair<GoodsInfo, int>> finalOrder;

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
    virtual int getUserType() override
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
    virtual int getUserType() override
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
    virtual int getUserType() override
    {
        return type;
    }
};