#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include <map>
#include <deque>
#include <unordered_map>

struct Order {
    std::string id;
    std::string side;
    double price;
    int quantity;
};

class OrderBook {
private:

    std::map<double, std::deque<Order>, std::greater<double>> bids;
    std::map<double, std::deque<Order>> asks;

    std::unordered_map<std::string, std::pair<double,std::string>> orderIndex;

public:

    void addOrder(Order order);
    void cancelOrder(std::string orderId);
    void printBook();

private:

    void matchBuy(Order order);
    void matchSell(Order order);

};

#endif
