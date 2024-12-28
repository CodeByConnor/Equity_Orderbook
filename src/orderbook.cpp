/**
 * @file orderbook.cpp
 * @brief Implementation of the Orderbook class for a simple partial-fill order book.
 */

#include "../include/orderbook.hpp"
#include "../include/helpers.hpp"
#include <iostream>
#include <iomanip>
#include <thread>
#include <cmath>   // for std::min, etc.

// Constructor
Orderbook::Orderbook(bool generate_dummies) {
    if (generate_dummies) {
        // Example: auto-generate some dummy data if desired
        add_order(10, 100.0, BookSide::bid);
        add_order(15, 99.5, BookSide::bid);
        add_order(8,  101.0, BookSide::ask);
        add_order(5,  102.0, BookSide::ask);
    }
}

// Add a new order to the book
void Orderbook::add_order(int qty, double price, BookSide side) {
    // Create a unique_ptr to a new Order
    auto new_order = std::make_unique<Order>(qty, price, side, unix_time());

    if (side == BookSide::bid) {
        // Insert into bids
        m_bids[price].push_back(std::move(new_order));
    } else {
        // Insert into asks
        m_asks[price].push_back(std::move(new_order));
    }
    remove_empty_keys();
}

// Remove map entries with empty vectors
void Orderbook::remove_empty_keys() {
    // Clean bids
    for (auto it = m_bids.begin(); it != m_bids.end(); ) {
        if (it->second.empty()) it = m_bids.erase(it);
        else ++it;
    }
    // Clean asks
    for (auto it = m_asks.begin(); it != m_asks.end(); ) {
        if (it->second.empty()) it = m_asks.erase(it);
        else ++it;
    }
}

// Template method to clean a specific side
template<typename T>
void Orderbook::clean_leg(std::map<double, std::vector<std::unique_ptr<Order>>, T>& price_map) {
    for (auto it = price_map.begin(); it != price_map.end(); ) {
        if (it->second.empty()) it = price_map.erase(it);
        else ++it;
    }
}

// Handle an incoming order (market or limit), partial fills included.
std::pair<int,double> Orderbook::handle_order(OrderType type, 
                                              int order_quantity, 
                                              Side side, 
                                              double price) 
{
    // Track fill metrics
    int units_transacted = 0;
    double total_value = 0.0;

    // If user is BUYING, match against Asks
    if (side == Side::buy) {
        if (m_asks.empty()) {
            return {0, 0.0}; 
        }
        fill_order(m_asks, type, side, order_quantity, price, units_transacted, total_value);
    }
    // If user is SELLING, match against Bids
    else {
        if (m_bids.empty()) {
            return {0, 0.0};
        }
        fill_order(m_bids, type, side, order_quantity, price, units_transacted, total_value);
    }

    // Remove any empty price levels after partial fill
    remove_empty_keys();

    return {units_transacted, total_value};
}

// Template to fill an incoming order from the available offers
template <typename T>
std::pair<int,double> Orderbook::fill_order(std::map<double, std::vector<std::unique_ptr<Order>>, T>& offers, 
                                            const OrderType type, 
                                            const Side side, 
                                            int& order_quantity,
                                            const double price,
                                            int& units_transacted,
                                            double& total_value) 
{
    for (auto it = offers.begin(); it != offers.end() && order_quantity > 0; ) {
        double current_price = it->first;

        // Check limit constraints
        if (type == OrderType::limit) {
            bool can_trade = (side == Side::buy)
                                 ? (current_price <= price)
                                 : (current_price >= price);

            if (!can_trade) {
                break;
            }
        }

        auto& order_vector = it->second;
        // Fill orders at this price level
        for (auto order_it = order_vector.begin(); order_it != order_vector.end() && order_quantity > 0; ) {
            Order* existing_order = order_it->get();
            int available_qty = existing_order->quantity;

            // Determine how many units we can fill
            int fill_qty = std::min(order_quantity, available_qty);

            // Update totals
            units_transacted += fill_qty;
            total_value += fill_qty * current_price;

            // Decrement from existing order and the incoming order
            existing_order->quantity -= fill_qty;
            order_quantity -= fill_qty;

            // If the existing order is fully filled, remove it
            if (existing_order->quantity == 0) {
                order_it = order_vector.erase(order_it);
            } else {
                ++order_it;
            }
        }

        // If this price level is empty, erase it
        if (order_vector.empty()) {
            it = offers.erase(it);
        } else {
            ++it;
        }
    }

    return {units_transacted, total_value};
}

// Get the best quote (lowest ask or highest bid)
double Orderbook::best_quote(BookSide side) {
    // For bids: highest key in m_bids
    // For asks: lowest key in m_asks
    if (side == BookSide::bid) {
        if (!m_bids.empty()) {
            return m_bids.rbegin()->first; 
        }
    } else {
        if (!m_asks.empty()) {
            return m_asks.rbegin()->first; 
        }
    }
    return 0.0;
}

// Print one side of the order book with color bars
template<typename T>
void Orderbook::print_leg(std::map<double, std::vector<std::unique_ptr<Order>>, T>& hashmap, 
                          BookSide side) 
{
    if (side == BookSide::ask) {
        // Print in ascending price order
        for (auto& [price, orders_vec] : hashmap) {
            int total_qty = 0;
            for (auto& o : orders_vec) {
                total_qty += o->quantity;
            }

            // Red color for asks
            std::string color_code = "\033[1;31m";

            // Build a bar for visualization (1 bar per 1 unit)
            int bar_size = total_qty;
            std::string bar;
            for (int i = 0; i < bar_size; i++) {
                // UTF-8 "full block" character
                bar += u8"█";
            }

            std::cout << std::fixed << std::setprecision(2)
                      << color_code
                      << "ASK  Price: " << price << " | Qty: " << total_qty
                      << " | " << bar
                      << "\033[0m\n";
        }
    } else {
        // BookSide::bid => print in descending order
        for (auto it = hashmap.rbegin(); it != hashmap.rend(); ++it) {
            double price = it->first;
            auto& orders_vec = it->second;

            int total_qty = 0;
            for (auto& o : orders_vec) {
                total_qty += o->quantity;
            }

            // Green color for bids
            std::string color_code = "\033[1;32m";

            // Build a bar for visualization (1 bar per 1 unit)
            int bar_size = total_qty;
            std::string bar;
            for (int i = 0; i < bar_size; i++) {
                bar += u8"█";
            }

            std::cout << std::fixed << std::setprecision(2)
                      << color_code
                      << "BID  Price: " << price << " | Qty: " << total_qty
                      << " | " << bar
                      << "\033[0m\n";
        }
    }
}

// Print the entire orderbook
void Orderbook::print() {
    std::cout << "\n========== Orderbook =========\n\n";

    // Print asks first (lowest price at top in ascending order)
    std::cout << "[ASKS]\n";
    print_leg(m_asks, BookSide::ask);
    std::cout << "\n";

    // Print bids after (highest price at top in descending order)
    std::cout << "[BIDS]\n";
    print_leg(m_bids, BookSide::bid);
    std::cout << "\n================================\n\n";
}

template void Orderbook::clean_leg<std::less<double>>(std::map<double, std::vector<std::unique_ptr<Order>>, std::less<double>>&);
template void Orderbook::clean_leg<std::greater<double>>(std::map<double, std::vector<std::unique_ptr<Order>>, std::greater<double>>&);

template std::pair<int,double> Orderbook::fill_order<std::less<double>>(std::map<double, std::vector<std::unique_ptr<Order>>, std::less<double>>&, 
const OrderType, const Side, int&, const double, int&, double&);

template std::pair<int,double> Orderbook::fill_order<std::greater<double>>(std::map<double, std::vector<std::unique_ptr<Order>>, std::greater<double>>&, 
const OrderType, const Side, int&, const double, int&, double&);
