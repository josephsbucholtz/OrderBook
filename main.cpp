#include <iostream>
#include <stdint.h> 
#include <vector>

enum class OrderType {
    Market,
    Limit,
    StopLoss,
};

enum class Side {
    Buy,
    Sell,
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

    int getOrderId() { return m_orderId; }
    OrderType getOrderType() { return m_orderType; }
    Side getSide() { return m_side; }
    uint32_t getQuantity() { return m_quantity; }
    int getPrice() { return m_price; }
    bool isFilled() { return m_quantity == 0; }

    void fill(uint32_t quantity) {
        if (quantity > m_quantity) {
            return; 
        }

        m_quantity -= quantity;
    }
    

private:
    int  m_orderId; 
    OrderType m_orderType;
    Side m_side;
    uint32_t m_quantity;
    int m_price;
    

};

class OrderBook {
public:
    OrderBook () {}     
    
    void addOrder(Order order) {
        Side side = order.getSide();

        if (side == Side::Buy) {
            m_bids.push_back(order);
        }
        else {
            m_asks.push_back(order);
        }
    }

    void removeOrder(int orderId);
    void modifyOrder(int orderId);

private:
    std::vector<Order> m_bids {};
    std::vector<Order> m_asks {}; 
};


int main () {
    return 0;
}
