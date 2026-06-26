#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

#include "utils.hpp"

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
    Order(OrderType orderType, Side side, Quantity quantity, Price price) {
        m_orderId = { nextID++ };
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
    OrderId getOrderId() { return m_orderId; }
    OrderType getOrderType() { return m_orderType; }
    Side getSide() { return m_side; }
    Quantity getQuantity() { return m_quantity; }
    Price getPrice() { return m_price; }
    bool isFilled() { return m_quantity == 0; }

    void fill(Quantity quantity) {
        if (quantity > getQuantity()) {
            std::cout << "Order cannot be filled\n";
            return; 
        }

        m_quantity -= quantity;
    }
    

private:
    static OrderId nextID;
    OrderId m_orderId; 
    OrderType m_orderType;
    Side m_side;
    Quantity m_quantity;
    Price m_price;

};

OrderId Order::nextID {};


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

    void removeOrder(OrderId orderId);
    void modifyOrder(OrderId orderId);

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

    Client(std::string name, Balance balance) : 
    m_name { name } , 
    m_balance { balance }
    {}

    std::string getName() { return m_name; }; 
    Balance getBalance() { return m_balance; };

    void placeOrder(Quantity quantity, OrderType type, Side side, Price price) {
        const uint amount { quantity * price };

        if (amount > this->getBalance()) {
            throw std::underflow_error("Amount Greater than Balance.");
        }

        Order order {type, side, quantity, price};
        m_orders.push_back(order);
        this->m_balance -= amount;
    }

    void cancelOrder() {
        
    }

    void modifyOrder() {

    }

private:
    std::string m_name;
    Balance m_balance {}; 
    std::vector<Order> m_orders {};

};

int main () {
    Order order(OrderType::LIMIT, Side::BUY, 10, 100);
    Order order2(OrderType::LIMIT, Side::BUY, 10, 100);
    Order order3(OrderType::LIMIT, Side::BUY, 10, 100);

    std::cout << "OrderID: " << order.getOrderId() << "\n";
    std::cout << "OrderID: " << order2.getOrderId() << "\n";
    std::cout << "OrderID: " << order3.getOrderId() << "\n";

    Client client("John", 50);
    
    std::cout << "CLient Name: " << client.getName() << "\n";
    std::cout << "Balance: " << client.getBalance() << "\n";

    OrderBook orderbook{};
    orderbook.addOrder(order);
    
    std::cout << "Quantity: " << order.getQuantity() << "\n";
    return 0;
}
