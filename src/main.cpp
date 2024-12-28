// /**
//  * @file main.cpp
//  * @brief Entry point for demonstrating the Orderbook.
//  *
//  * This file uses the Orderbook class to add orders, then executes
//  * partial limit and market orders.
//  *
//  *   g++ -std=c++17 -o main main.cpp orderbook.cpp helperFunctions.cpp
//  *   ./main
//  */

#include <iostream>
#include <utility> // std::pair
#include "../include/orderbook.hpp"
#include "../include/helpers.hpp" // for unix_time() and print_fill()

int main() {
    // Create an Orderbook with no dummy orders
    Orderbook ob(false);

  
    // 1) Populate BID orders

    ob.add_order(5,   98.5,  BookSide::bid);
    ob.add_order(12,  98.6,  BookSide::bid);
    ob.add_order(20,  98.9,  BookSide::bid);
    ob.add_order(15,  99.0,  BookSide::bid);
    ob.add_order(8,   99.1,  BookSide::bid);
    ob.add_order(10,  99.5,  BookSide::bid);
    ob.add_order(14,  99.3,  BookSide::bid);
    ob.add_order(11,  99.4,  BookSide::bid);

   
    // 2) Populate ASK orders

    ob.add_order(8,   100.0, BookSide::ask);
    ob.add_order(10,  100.5, BookSide::ask);
    ob.add_order(7,   100.8, BookSide::ask);
    ob.add_order(12,  101.0, BookSide::ask);
    ob.add_order(9,   101.3, BookSide::ask);
    ob.add_order(10,  101.6, BookSide::ask);
    ob.add_order(15,  102.0, BookSide::ask);
    ob.add_order(5,   102.3, BookSide::ask);

    // Print the initial Orderbook
    std::cout << "----- INITIAL ORDERBOOK -----\n";
    ob.print();

  
    // 3) Timing a partial LIMIT order (BUY 20 units @ $100.0)

    uint64_t start_time_limit = unix_time();
    auto fill1 = ob.handle_order(OrderType::limit, 20, Side::buy, 100.0);
    uint64_t end_time_limit = unix_time();

    // Print fill info with time cost
    print_fill(fill1, 20, start_time_limit, end_time_limit);

    // Print the Orderbook after partially filling
    std::cout << "\n----- AFTER PARTIAL LIMIT BUY -----\n";
    ob.print();

    
    // 4) Timing a partial MARKET order (SELL 16 units)

    uint64_t start_time_market = unix_time();
    auto fill2 = ob.handle_order(OrderType::market, 16, Side::sell);
    uint64_t end_time_market = unix_time();

    // Print fill info with time cost
    print_fill(fill2, 16, start_time_market, end_time_market);

    // Print the Orderbook after partial market sell
    std::cout << "\n----- AFTER PARTIAL MARKET SELL -----\n";
    ob.print();

    return 0;
}


