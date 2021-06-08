#pragma once
#include <algorithm>
#include <cstring>
#include <map>
#include <sstream>
#include "Goods.hpp"
#include "User.hpp"
/**
 * @brief ƽ̨�࣬����չʾ��Ϣ�Լ�ѡ�����
 *
 */
class Platform
{
  public:
    Platform()
    {
        server.serverInit();
        user = nullptr;
        goods = new Foods(server);
        goods->getGoods(allGoods);
        delete goods;
        goods = nullptr;
    }
    ~Platform()
    {
    }
    void show();                             // չʾ��������
    void userCenter();                       // �û����Ľ���
    void userRegisterOrLog();                // ע���¼����
    void userInformationChange();            // �޸��û���Ϣ
    void userQuit();                         // �û��˳�
    void purchaseGoods();                    // ������Ʒ��ʵ���
    void goodsInformation();                 // ��Ʒ��Ϣ
    void changeGoods();                      // �޸���Ʒ��Ϣ
    void definiteType();                     // ȷ����Ʒ����
    void freeUser();                         // �ͷ��û�ָ��
    void freeGoods();                        // �ͷ���Ʒָ��
    template <typename T> void input(T &x);  // �������

    void initSock();

    /* void severInit();
    void clientInit(); */

  private:
    std::string name;  // �û���
    User *user;        // �û�ָ��
    Goods *goods;      // ��Ʒָ��
    std::vector<GoodsInfo> allGoods;
    std::vector<GoodsInfo> showGoods;  // չʾ����Ʒ,����ʵ���
    //���涩������
    std::map<std::string, std::vector<std::pair<GoodsInfo, int>>> shoppingCart, finalOrder;
    std::vector<std::pair<GoodsInfo, int>> changeInfo;

    std::stringstream output, inputStream;
    Server server;
};
