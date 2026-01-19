// Accelerated C++ - Chapter 3: Working with batches of data
// Finance Applications: Advanced data processing and analysis

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>

int main() {
    std::cout << "=== Chapter 3: Batch Data Processing ===" << std::endl;
    
    // Example 1: Processing price data with algorithms
    std::vector<double> stock_prices = {150.25, 148.75, 152.10, 149.80, 151.45, 153.20, 147.90};
    
    std::cout << "\n1. Price Analysis:" << std::endl;
    
    // Find min and max prices
    auto min_price = *std::min_element(stock_prices.begin(), stock_prices.end());
    auto max_price = *std::max_element(stock_prices.begin(), stock_prices.end());
    
    // Calculate average using accumulate
    double sum = std::accumulate(stock_prices.begin(), stock_prices.end(), 0.0);
    double average = sum / stock_prices.size();
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Min Price: $" << min_price << std::endl;
    std::cout << "Max Price: $" << max_price << std::endl;
    std::cout << "Average: $" << average << std::endl;
    
    // Example 2: Sorting and median calculation
    std::vector<double> sorted_prices = stock_prices;
    std::sort(sorted_prices.begin(), sorted_prices.end());
    
    double median = sorted_prices[sorted_prices.size() / 2];
    std::cout << "Median: $" << median << std::endl;
    
    // Example 3: Working with strings - ticker symbols
    std::vector<std::string> tickers = {"AAPL", "GOOGL", "MSFT", "AMZN", "TSLA"};
    
    std::cout << "\n2. Portfolio Holdings:" << std::endl;
    for (const auto& ticker : tickers) {
        std::cout << ticker << " ";
    }
    std::cout << std::endl;
    
    return 0;
}