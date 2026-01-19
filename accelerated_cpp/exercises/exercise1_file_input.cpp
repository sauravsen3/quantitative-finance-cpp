// File Input Version - Trading Portfolio Calculator
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

int main() {
    // Open input file
    std::ifstream input_file("trade_data.txt");
    
    if (!input_file) {
        std::cout << "Error: Cannot open trade_data.txt" << std::endl;
        return 1;
    }
    
    // Read data from file
    std::string trader_name, stock_symbol;
    int shares;
    double price_per_share, commission;
    
    input_file >> trader_name >> stock_symbol >> shares >> price_per_share >> commission;
    input_file.close();
    
    // Calculate totals
    double gross_cost = shares * price_per_share;
    double total_cost = gross_cost + commission;
    double cost_per_share_including_commission = total_cost / shares;
    
    // Display results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== TRADE CONFIRMATION ===" << std::endl;
    std::cout << "Trader: " << trader_name << std::endl;
    std::cout << "Stock: " << stock_symbol << std::endl;
    std::cout << "Shares: " << shares << std::endl;
    std::cout << "Price per share: $" << price_per_share << std::endl;
    std::cout << "Total cost: $" << total_cost << std::endl;
    
    return 0;
}