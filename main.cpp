#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include <stdint.h> 

enum class OrderType {
    MARKET,
    LIMIT,
    STOPLOSS,
};

enum class Side {
    BUY,
    SELL,
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

    bool operator<(const Order& other) const {
        return this->m_price < other.m_price;
    }

    bool operator>(const Order& other) const {
        return this->m_price > other.m_price;
    }
    int getOrderId() { return m_orderId; }
    OrderType getOrderType() { return m_orderType; }
    Side getSide() { return m_side; }
    uint32_t getQuantity() { return m_quantity; }
    int getPrice() { return m_price; }
    bool isFilled() { return m_quantity == 0; }

    void fill(uint32_t quantity) {
        if (quantity > getQuantity()) {
            std::cout << "Order cannot be filled\n";
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

    void placeOrder(Order order);
    
    void addOrder(Order order) {
        Side side = order.getSide();

        if (side == Side::BUY) {
            m_bids.push(order);
        }
        else {
            m_asks.push(order);
        }
    }

    void removeOrder(int orderId);
    void modifyOrder(int orderId);

    std::priority_queue<Order> getBids() { return m_bids;}

private:
    std::priority_queue<Order> m_bids {}; //max-heap
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>> m_asks {}; //min-heap 
    std::unordered_map<int, Order> orderMap ; //orderId to Order
    

};


class Client {
public:
    Client(std::string name) :
    m_name { name } 
    {}

    Client(std::string name, int balance) : 
    m_name { name } , 
    m_balance { balance }
    {}

    std::string getName() { return m_name; }; 
    int getBalance() { return m_balance; };

    void placeOrder(int amount);
    void cancelOrder(const std::vector<Order>& orders);
    void modifyOrder(const std::vector<Order>& orders);

private:
    std::string m_name;
    int m_balance {}; 
    std::vector<Order> m_orders {};
};

int main () {
    Order order(0, OrderType::LIMIT, Side::BUY, 10, 100);

    Client client("John", 50);
    
    std::cout << "CLient Name: " << client.getName() << "\n";
    std::cout << "Balance: " << client.getBalance() << "\n";

    OrderBook orderbook{};
    orderbook.addOrder(order);
    
    std::cout << "Quantity: " << order.getQuantity() << "\n";
    return 0;
}
