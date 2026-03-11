#include "OrderBook.h"

void OrderBook::addOrder(Order order)
{

    if(order.side=="BUY")
        matchBuy(order);
    else
        matchSell(order);
}


void OrderBook::matchBuy(Order order)
{

    while(order.quantity>0 && !asks.empty())
    {
        auto bestAsk = asks.begin();

        if(order.price!=0 && bestAsk->first > order.price)
            break;

        auto &queue = bestAsk->second;
        Order &sellOrder = queue.front();

        int tradeQty = std::min(order.quantity, sellOrder.quantity);

        std::cout<<"TRADE "
                 <<order.id<<" "
                 <<sellOrder.id<<" "
                 <<bestAsk->first<<" "
                 <<tradeQty<<"\n";

        order.quantity -= tradeQty;
        sellOrder.quantity -= tradeQty;

        if(sellOrder.quantity==0)
        {
            queue.pop_front();
            orderIndex.erase(sellOrder.id);
        }

        if(queue.empty())
            asks.erase(bestAsk);
    }

    if(order.quantity>0 && order.price!=0)
    {
        bids[order.price].push_back(order);
        orderIndex[order.id] = {order.price,"BUY"};
    }
}


void OrderBook::matchSell(Order order)
{

    while(order.quantity>0 && !bids.empty())
    {
        auto bestBid = bids.begin();

        if(order.price!=0 && bestBid->first < order.price)
            break;

        auto &queue = bestBid->second;
        Order &buyOrder = queue.front();

        int tradeQty = std::min(order.quantity, buyOrder.quantity);

        std::cout<<"TRADE "
                 <<buyOrder.id<<" "
                 <<order.id<<" "
                 <<bestBid->first<<" "
                 <<tradeQty<<"\n";

        order.quantity -= tradeQty;
        buyOrder.quantity -= tradeQty;

        if(buyOrder.quantity==0)
        {
            queue.pop_front();
            orderIndex.erase(buyOrder.id);
        }

        if(queue.empty())
            bids.erase(bestBid);
    }

    if(order.quantity>0 && order.price!=0)
    {
        asks[order.price].push_back(order);
        orderIndex[order.id] = {order.price,"SELL"};
    }
}


void OrderBook::cancelOrder(std::string id)
{

    if(orderIndex.find(id)==orderIndex.end())
        return;

    auto info = orderIndex[id];

    double price = info.first;
    std::string side = info.second;

    if(side=="BUY")
    {
        auto &queue = bids[price];

        for(auto it=queue.begin(); it!=queue.end(); ++it)
        {
            if(it->id==id)
            {
                queue.erase(it);
                break;
            }
        }

        if(queue.empty())
            bids.erase(price);
    }
    else
    {
        auto &queue = asks[price];

        for(auto it=queue.begin(); it!=queue.end(); ++it)
        {
            if(it->id==id)
            {
                queue.erase(it);
                break;
            }
        }

        if(queue.empty())
            asks.erase(price);
    }

    orderIndex.erase(id);
}



void OrderBook::printBook()
{

    std::cout<<"--- Book ---\n";

    int count=0;

    for(auto &a:asks)
    {
        int total=0;
        for(auto &o:a.second)
            total+=o.quantity;

        std::cout<<"ASK: "<<a.first<<" x "<<total<<"\n";

        if(++count==5) break;
    }

    count=0;

    for(auto &b:bids)
    {
        int total=0;
        for(auto &o:b.second)
            total+=o.quantity;

        std::cout<<"BID: "<<b.first<<" x "<<total<<"\n";

        if(++count==5) break;
    }
}