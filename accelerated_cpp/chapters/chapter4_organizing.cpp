// Accelerated C++ - Chapter 4: Organizing programs and data
// Finance Applications: Structured data and functions

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Function to calculate position value
double calculate_position_value(double price, int shares) {
    return price * shares;
}

// Function to display stock info
void display_stock(const std::string& symbol, double price, int shares) {
    double value = calculate_position_value(price, shares);
    std::cout << symbol << ": " << shares << " shares @ $" << std::fixed 
              << std::setprecision(2) << price << " = $" << value << std::endl;
}

// Function to calculate portfolio total
double calculate_total(const std::vector<double>& prices, const std::vector<int>& shares) {
    double total = 0.0;
    for (size_t i = 0; i < prices.size(); ++i) {
        total += calculate_position_value(prices[i], shares[i]);
    }
    return total;
}

int main() {
    std::cout << "=== Chapter 4: Organized Trading System ===" << std::endl;
    
    // Sample portfolio data
    std::vector<std::string> symbols = {"AAPL", "GOOGL", "MSFT"};
    std::vector<double> prices = {150.25, 2500.00, 300.50};
    std::vector<int> shares = {100, 10, 50};
    
    std::cout << "\nPortfolio Holdings:" << std::endl;
    
    // Display each position using our function
    for (size_t i = 0; i < symbols.size(); ++i) {
        display_stock(symbols[i], prices[i], shares[i]);
    }
    
    // Calculate and display total
    double total = calculate_total(prices, shares);
    std::cout << "\nTotal Portfolio Value: $" << std::fixed 
              << std::setprecision(2) << total << std::endl;
    
    return 0;
}