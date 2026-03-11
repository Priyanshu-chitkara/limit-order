#include "OrderBook.h"
#include <sstream>

int main()
{

    OrderBook book;

    std::string line;

    while(std::getline(std::cin,line))
    {

        if(line.empty()) continue;

        std::stringstream ss(line);

        std::string id,side;
        double price;
        int qty;

        if(line.find("CANCEL")==0)
        {
            std::string cancel,id;
            ss>>cancel>>id;
            book.cancelOrder(id);
        }
        else
        {
            ss>>id>>side>>price>>qty;

            Order order{id,side,price,qty};

            book.addOrder(order);
        }
    }

    book.printBook();
}