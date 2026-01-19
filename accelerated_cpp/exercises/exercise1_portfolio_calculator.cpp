// Accelerated C++ - Chapter 1 Exercise
// Build a Trading Portfolio Calculator

#include <iostream>
#include <string>
#include <iomanip>

int main() {
    std::cout << "=== Trading Portfolio Calculator ===" << std::endl;
    
    // TODO: Complete this program step by step
    
    // Step 1: Get trader information
    std::string trader_name;
    std::cout << "Enter your name: ";
    std::cin >> trader_name;
    
    
    // Step 2: Get stock information
    std::string stock_symbol;
    std::cout << "Enter stock symbol (e.g., AAPL): ";
    std::cin >> stock_symbol;
    
    
    // Step 3: Get trade details
    int shares;
    double price_per_share;
    double commission;
    
    std::cout << "Enter number of shares: ";
    std::cin >> shares;
    
    std::cout << "Enter price per share: $";
    std::cin >> price_per_share;
    
    std::cout << "Enter commission: $";
    std::cin >> commission;
    
    
    // Step 4: Calculate totals
    double gross_cost;
    double total_cost;
    double cost_per_share_including_commission;
    
    // YOUR CODE HERE: Calculate gross cost (shares * price)
    gross_cost = shares * price_per_share;
    // YOUR CODE HERE: Calculate total cost (gross + commission)
    total_cost = gross_cost + commission;
    // YOUR CODE HERE: Calculate effective cost per share
    cost_per_share_including_commission = total_cost / shares;
    
    // Step 5: Create a formatted report
    std::cout << std::fixed << std::setprecision(2);
    
    // Create a border for the report
    std::string border(50, '=');
    std::cout << "\n" << border << std::endl;
    std::cout << "           TRADE CONFIRMATION" << std::endl;
    std::cout << border << std::endl;
    
    // YOUR CODE HERE: Display trader name
    std::cout << "Trader: " << trader_name << std::endl;
    // YOUR CODE HERE: Display stock symbol
    std::cout << "Stock: " << stock_symbol << std::endl;
    // YOUR CODE HERE: Display number of shares
    std::cout << "Shares: " << shares << std::endl;
    // YOUR CODE HERE: Display price per share
    std::cout << "Price per share: $" << price_per_share << std::endl;
    // YOUR CODE HERE: Display gross cost
    std::cout << "Gross cost: $" << gross_cost << std::endl;
    // YOUR CODE HERE: Display commission
    std::cout << "Commission: $" << commission << std::endl;
    // YOUR CODE HERE: Display total cost
    std::cout << "Total cost: $" << total_cost << std::endl;
    // YOUR CODE HERE: Display effective cost per share
    std::cout << "Effective cost per share: $" << cost_per_share_including_commission << std::endl;
    std::cout << border << std::endl;
    
    // Bonus: Add a warning if commission is high
    double commission_percentage = (commission / gross_cost) * 100;
    if (commission_percentage > 1.0) {
        std::cout << "⚠️  WARNING: Commission is " << commission_percentage 
                  << "% of trade value!" << std::endl;
    }
    
    return 0;
}

/*
LEARNING OBJECTIVES:
1. Practice std::cin for input
2. Use std::string for text data
3. Perform financial calculations
4. Format output with std::setprecision
5. Create professional-looking reports
6. Use conditional logic

EXPECTED OUTPUT EXAMPLE:
===================================
           TRADE CONFIRMATION
===================================
Trader: John Smith
Stock: AAPL
Shares: 100
Price per share: $150.75
Gross cost: $15,075.00
Commission: $9.99
Total cost: $15,084.99
Effective cost per share: $150.85
===================================

COMPILE AND RUN:
g++ -std=c++17 -o exercise1 exercise1.cpp && ./exercise1
*/