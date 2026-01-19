// Accelerated C++ - Chapter 4 Exercise
// Trading System with Functions and Data Organization

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// TODO: Write function to calculate commission
// Function should take trade_value and return commission (0.1% of trade value, minimum $5)
double calculate_commission(double trade_value) {
    // Your code here
    return 0.0;
}

// TODO: Write function to calculate net proceeds from a sale
// Function should take shares, price, and return net amount after commission
double calculate_sale_proceeds(int shares, double price) {
    // Your code here
    return 0.0;
}

// TODO: Write function to calculate profit/loss
// Function should take buy_price, sell_price, shares and return P&L
double calculate_pnl(double buy_price, double sell_price, int shares) {
    // Your code here
    return 0.0;
}

// TODO: Write function to display trade summary
// Function should take all trade details and display formatted summary
void display_trade_summary(const std::string& symbol, int shares, 
                          double buy_price, double sell_price) {
    // Your code here
}

int main() {
    std::cout << "=== Trading System with P&L Calculator ===" << std::endl;
    
    // Get trade information
    std::string symbol;
    int shares;
    double buy_price, sell_price;
    
    std::cout << "Enter stock symbol: ";
    std::cin >> symbol;
    
    std::cout << "Enter number of shares: ";
    std::cin >> shares;
    
    std::cout << "Enter buy price per share: $";
    std::cin >> buy_price;
    
    std::cout << "Enter sell price per share: $";
    std::cin >> sell_price;
    
    // TODO: Use your functions to display complete trade analysis
    display_trade_summary(symbol, shares, buy_price, sell_price);
    
    return 0;
}