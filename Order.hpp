#pragma once
#include "Goods.hpp"
#include <string>
#include <vector>

class Order
{
  public:
    Order()
    {
    }
    ~Order()
    {
    }
    void preAddGoods(std::vector<GoodsInfo> &, int = 0);
    void chooseGoods(std::vector<GoodsInfo> &, GoodsInfo &);
    void chooseAmount(const GoodsInfo &);
    void addGoods(const GoodsInfo &, const int);
    void showOrder();
    int search(const std::string &);
    void deleteGoods();
    void changeAmount();
    void generateOrder(std::vector<std::pair<GoodsInfo, int>> &);
    double getToatalPrice();
    // void transferPayments();

    void definiteType(int);
    void freeGoods();
    template <typename T> void input(T &) const;

  private:
    std::vector<std::pair<GoodsInfo, int>> preorder;
    Goods *goods;
    int lineNum;
    double sum = 0;
    std::fstream ordfp;
};