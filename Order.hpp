#pragma once
#include "Goods.hpp"
#include <string>
#include <vector>

class Order
{
  public:
    Order(Server &s) : server(&s)
    {
        goods = new Foods(s);
        goods->updateInfo(shoppingCart);
        delete goods;
        goods = new Clothes(s);
        goods->updateInfo(shoppingCart);
        delete goods;
        goods = new Books(s);
        goods->updateInfo(shoppingCart);
        delete goods;
        goods = nullptr;
    }
    ~Order()
    {
        freeGoods();
    }
    void preAddGoods(std::vector<GoodsInfo> &, std::vector<GoodsInfo> &);
    void chooseGoods(std::vector<GoodsInfo> &, GoodsInfo &);
    void chooseAmount(const GoodsInfo &);
    void addGoods(const GoodsInfo &, const int);
    void showShoppingCart();
    int search(const std::string &);
    void deleteGoods();
    void changeAmount();
    void generateOrder(std::vector<std::pair<GoodsInfo, int>> &, std::vector<GoodsInfo> &);
    double getToatalPrice();
    void clearPrice();
    void preorderGoods(std::vector<GoodsInfo> &, const std::string &, const std::string &, const int);
    void soldOut(std::vector<GoodsInfo> &);
    void setShoppingCart(std::vector<std::pair<GoodsInfo, int>> &);
    void getShoppingCart(std::vector<std::pair<GoodsInfo, int>> &);
    // void transferPayments();

    void setName(const std::string &);
    void definiteType();
    void freeGoods();
    template <typename T> void input(T &) const;

  private:
    std::vector<std::pair<GoodsInfo, int>> shoppingCart;
    Goods *goods;
    std::string name;
    int lineNum;
    double sum = 0;
    std::fstream ordfp;

    // Client client;
    Server *server;
};
/*
1 2 1
hb wjw
1 3 1 1
雪糕 20
4 20
*/