// Accelerated C++ - Chapter 2 Exercise
// Portfolio Performance Analyzer

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

int main() {
    std::cout << "=== Portfolio Performance Analyzer ===" << std::endl;
    
    // Get number of stocks in portfolio
    int num_stocks;
    std::cout << "Enter number of stocks: ";
    std::cin >> num_stocks;
    
    std::vector<std::string> symbols;
    std::vector<double> prices;
    std::vector<int> shares;
    
    // Input loop - collect portfolio data
    for (int i = 0; i < num_stocks; ++i) {
        std::string symbol;
        double price;
        int share_count;
        
        std::cout << "\nStock " << (i + 1) << ":" << std::endl;
        std::cout << "Symbol: ";
        std::cin >> symbol;
        std::cout << "Price per share: $";
        std::cin >> price;
        std::cout << "Shares owned: ";
        std::cin >> share_count;
        
        symbols.push_back(symbol);
        prices.push_back(price);
        shares.push_back(share_count);
    }
    
    // Analysis loop - calculate portfolio metrics
    double total_value = 0.0;
    double max_position = 0.0;
    std::string largest_holding;
    
    std::cout << "\n=== PORTFOLIO ANALYSIS ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    for (int i = 0; i < num_stocks; ++i) {
        double position_value = prices[i] * shares[i];
        total_value += position_value;
        
        if (position_value > max_position) {
            max_position = position_value;
            largest_holding = symbols[i];
        }
        
        std::cout << symbols[i] << ": " << shares[i] << " shares @ $" 
                  << prices[i] << " = $" << position_value << std::endl;
    }
    
    std::cout << "\n=== SUMMARY ===" << std::endl;
    std::cout << "Total Portfolio Value: $" << total_value << std::endl;
    std::cout << "Largest Position: " << largest_holding 
              << " ($" << max_position << ")" << std::endl;
    std::cout << "Average Position Size: $" << total_value / num_stocks << std::endl;
    
    return 0;
}

