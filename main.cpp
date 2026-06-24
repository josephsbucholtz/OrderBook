#include <iostream>
#include <stdint.h> 

enum class OrderType {
    Market,
    Limit,
    StopLoss,
};

enum class Side {
    Buy,
    Sell,
};

class OrderBook {
public:



private:

};

class Order {
public:
    Order(int orderId, OrderType orderType, Side side, uint32_t quantity, int price) {
        m_orderId = { orderId };
        m_orderType = { orderType };
        m_side = { side };
        m_quantity = { quantity };
        m_price = { price };
    }

    

private:
    int  m_orderId; 
    OrderType m_orderType;
    Side m_side;
    uint32_t m_quantity;
    int m_price;
    

};

int main () {
    return 0;
}
