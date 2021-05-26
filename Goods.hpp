#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <set>

/**
 * @brief �洢��Ʒ��Ϣ����������������ʵ��std::find����
 *
 */
struct GoodsInfo
{
    std::string name, merchant, discription;
    double price, discount;
    int type, amount;
    bool operator==(const GoodsInfo &) const;
};
/**
 * @brief ��Ʒ�࣬ʵ���й���Ʒ�ĸ��ֲ���
 *
 */
class Goods  // ���캯����������Ʒ����
{
  public:
    Goods()
    {
        num = 0;
        goofp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\GoodsInfo.txt");
        if (!goofp)
        {
            std::cout << "Open file error!\n";
            return;
        }
        while (goofp.peek() != EOF)
        {
            GoodsInfo goodTemp;
            goofp >> goodTemp.type >> goodTemp.name >> goodTemp.discription >> goodTemp.amount >> goodTemp.price >>
                goodTemp.discount >> goodTemp.merchant;
            if (goodTemp.name.empty())  // �Թ�����
                continue;
            else
                goodsInfo.emplace_back(goodTemp);
        }
    }
    virtual ~Goods()  // ��������������Ʒ���ݴ����ļ�
    {
        goofp.close();
        goofp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\GoodsInfo.txt", std::ios::out | std::ios::trunc);
        goofp.seekg(0, std::fstream::beg);
        for (auto st : goodsInfo)
            goofp << st.type << " " << st.name << " " << st.discription << " " << st.amount << " " << st.price << " "
                  << st.discount << " " << st.merchant << std::endl;
        goofp.close();
    }

    virtual double getPrice() = 0;                               // ���麯����������Ʒ�۸�
    void addItems(const std::string &, const std::string &);     // ������Ʒ
    void changeItems(const std::string &, const std::string &);  // �޸���Ʒ��Ϣ
    bool changeInt(int &);                                       // �ж��޸�int�����Ƿ�Ϸ�
    bool changeDouble(double &);                                 // �ж��޸�double�����Ƿ�Ϸ�
    void search(std::vector<GoodsInfo> &);                       // ������Ʒ��������vector�У�ʵ�������
    void search(const std::string &, std::vector<GoodsInfo> &);  // ���أ������Ʋ�����Ʒ��������vector�У�ʵ�������
    void search(const double, const double, std::vector<GoodsInfo> &);  // ���أ����۸������Ʒ
    void search(const int, std::vector<GoodsInfo> &);                   // ���أ�������������Ʒ
    void atDiscount(const double);                                      // ��ĳ������Ʒ����
    bool isInt(const std::string &);                                    // ������ʽ�ж������Ƿ�Ϊint����
    bool isFloat(const std::string &);                        // ������ʽ�ж������Ƿ�Ϊdouble����
    template <typename T> void input(T &) const;              //���Ƿ�����
    void copyInfo(GoodsInfo &);                               //���������ݳ�Ա��Ϣ��������ʱ������
    void copyInfo(const std::vector<GoodsInfo>::iterator &);  //�����������ݳ�Ա��Ϣ���������ݳ�Ա��

  protected:
    std::string name, merchant, discription;
    int type, amount;
    double price, discount;
    std::vector<GoodsInfo> goodsInfo;

  private:
    std::fstream goofp;
    int num;
};

class Foods : public Goods
{
  public:
    Foods() : Goods()
    {
        type = 1;
    }
    Foods(const std::string &tname) : Goods()
    {
        merchant = tname;
        type = 1;
    }
    virtual ~Foods() override
    {
    }
    virtual double getPrice() override;

  private:
};

class Clothes : public Goods
{
  public:
    Clothes() : Goods()
    {
        type = 2;
    }
    Clothes(const std::string &tname) : Goods()
    {
        merchant = tname;
        type = 2;
    }
    virtual ~Clothes() override
    {
    }
    virtual double getPrice() override;

  private:
};

class Books : public Goods
{
  public:
    Books() : Goods()
    {
        type = 3;
    }
    Books(const std::string &tname) : Goods()
    {
        merchant = tname;
        type = 3;
    }
    virtual ~Books() override
    {
    }
    virtual double getPrice() override;

  private:
};
