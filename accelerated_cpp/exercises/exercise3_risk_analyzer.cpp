// Accelerated C++ - Chapter 3 Exercise
// Advanced Portfolio Risk Analyzer

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <cmath>

int main() {
    std::cout << "=== Advanced Portfolio Risk Analyzer ===" << std::endl;
    
    // TODO: Complete this exercise
    
    // Step 1: Get portfolio data
    int num_stocks;
    std::cout << "Enter number of stocks: ";
    std::cin >> num_stocks;
    
    std::vector<std::string> symbols(num_stocks);
    std::vector<double> prices(num_stocks);
    std::vector<int> shares(num_stocks);
    std::vector<double> position_values(num_stocks);
    
    // Step 2: Input data
    for (int i = 0; i < num_stocks; ++i) {
        std::cout << "\nStock " << (i + 1) << ":" << std::endl;
        std::cout << "Symbol: ";
        std::cin >> symbols[i];
        std::cout << "Price: $";
        std::cin >> prices[i];
        std::cout << "Shares: ";
        std::cin >> shares[i];
        
        // TODO: Calculate position value
        // position_values[i] = 0.0; // WRONG: This was setting everything to zero!
        position_values[i] = prices[i] * shares[i]; // CORRECT: price × shares
    }
    
    // Step 3: Portfolio analysis using algorithms
    std::cout << "\n=== RISK ANALYSIS ===" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    
    // TODO: Calculate total portfolio value using std::accumulate
    double total_value = 0.0;
    total_value = std::accumulate(position_values.begin(), position_values.end(), 0.0);
    // TODO: Find largest and smallest positions using std::min_element and std::max_element
    double largest_position = 0.0;
    double smallest_position = 0.0;
    largest_position = *std::max_element(position_values.begin(), position_values.end());
    smallest_position = *std::min_element(position_values.begin(), position_values.end());
    // TODO: Calculate portfolio concentration (largest position / total)
    double concentration = 0.0;
    concentration = largest_position / total_value;
    // Step 4: Sort positions by value for ranking
    // TODO: Create a vector of indices and sort by position value
    std::vector<int> indices(num_stocks);
    // Fill indices with 0, 1, 2, ... num_stocks-1
    // Sort indices based on position values (largest first)
    // Create indices vector: 0, 1, 2, 3...

    for (int i = 0; i < num_stocks; ++i) {
    indices[i] = i;
    }
// Sort indices based on position values (largest first) - DO THIS BEFORE DISPLAYING!
std::sort(indices.begin(), indices.end(), 
    [&](int a, int b) {
        return position_values[a] > position_values[b];
    });

    for (int i = 0; i < num_stocks; ++i) {
    int idx = indices[i];
    std::cout << (i+1) << ". " << symbols[idx] 
              << ": $" << position_values[idx] << std::endl;
    std::cout << "   (" << shares[idx] << " shares at $"
              << prices[idx] << " each)" << std::endl;}

    // Step 5: Display results
    std::cout << "Total Portfolio Value: $" << total_value << std::endl;
    std::cout << "Largest Position: $" << largest_position << std::endl;
    std::cout << "Smallest Position: $" << smallest_position << std::endl;
    std::cout << "Portfolio Concentration: " << concentration * 100 << "%" << std::endl;
    
    std::cout << "\n=== POSITION RANKING ===" << std::endl;
    // TODO: Display positions sorted by value (largest to smallest)
    
    // Step 6: Risk warning
    if (concentration > 0.4) {
        std::cout << "\n⚠️  HIGH CONCENTRATION RISK!" << std::endl;
    }
    
    return 0;
}