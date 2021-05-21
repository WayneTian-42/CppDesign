#pragma once
#include "Goods.hpp"
#include <string>
#include <utility>
#include <vector>

class Order
{
  public:
    Order()
    {
        ordfp.open("D:\\VS-Code\\VS-Code-C++\\semester_4\\Cpp_Design\\OrdersInfo.txt");
        if (!ordfp)
        {
            std::cout << "Open file error!\n";
            return;
        }
        while (ordfp.peek() != EOF)
        {
            GoodsInfo goodTemp;
            ordfp >> goodTemp.type >> goodTemp.name >> goodTemp.amount >> goodTemp.price >> goodTemp.discount >>
                goodTemp.merchant;
            if (goodTemp.name.empty())
                continue;
            else
            {
                preorder.emplace_back(goodTemp);
            }
        }
    }
    ~Order()
    {
        std::string all;
        char tmp[1024];
        ordfp.seekg(0, std::fstream::beg);
        while (ordfp.getline(tmp, sizeof(tmp)))
            /* while (ordfp.peek() != EOF)
            {
                std::getline(ordfp, tmp);
            } */
            ordfp.close();
    }
    void preAddGoods(std::vector<GoodsInfo> &, int = 0);
    void chooseGoods(std::vector<GoodsInfo> &, GoodsInfo &);
    void chooseAmount(const GoodsInfo &);
    void showOrder();
    int search(const std::string &);
    void deleteGoods();
    void changeAmount();
    void generateOrder();
    void transferPayments();

    void definiteType(int);
    void freeGoods();
    template <typename T> void input(T &) const;

  private:
    std::vector<std::pair<GoodsInfo, int>> preorder;
    Goods *goods;
    int lineNum;
    std::fstream ordfp;
};