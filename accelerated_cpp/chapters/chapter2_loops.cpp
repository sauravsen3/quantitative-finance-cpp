// Accelerated C++ Chapter 2: Looping and Counting
// Finance applications: Portfolio analysis and statistics

#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::cout << "=== Chapter 2: Loops in Finance ===" << std::endl;
    
    // Exercise 2-1: Simple counting loop (like the book's example)
    std::cout << "Trading days countdown:" << std::endl;
    for (int day = 5; day >= 1; --day) {
        std::cout << "T-" << day << " days until earnings" << std::endl;
    }
    std::cout << "Earnings announcement!" << std::endl;
    
    // Exercise 2-2: Accumulation pattern - Portfolio value calculation
    std::cout << "\n--- Portfolio Value Calculation ---" << std::endl;
    
    double total_portfolio_value = 0;
    int num_positions = 5;
    
    std::cout << "Enter " << num_positions << " position values:" << std::endl;
    
    for (int i = 0; i < num_positions; ++i) {
        double position_value;
        std::cout << "Position " << (i + 1) << ": $";
        std::cin >> position_value;
        total_portfolio_value += position_value;
    }
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total Portfolio Value: $" << total_portfolio_value << std::endl;
    std::cout << "Average Position Size: $" << total_portfolio_value / num_positions << std::endl;
    
    // Exercise 2-3: Finding maximum (like finding longest name)
    std::cout << "\n--- Finding Best Performing Stock ---" << std::endl;
    
    double best_return = -100.0; // Start with very low return
    std::string best_stock;
    
    for (int i = 0; i < 3; ++i) {
        std::string stock_symbol;
        double return_pct;
        
        std::cout << "Enter stock symbol: ";
        std::cin >> stock_symbol;
        std::cout << "Enter return %: ";
        std::cin >> return_pct;
        
        if (return_pct > best_return) {
            best_return = return_pct;
            best_stock = stock_symbol;
        }
    }
    
    std::cout << "Best performer: " << best_stock 
              << " with " << best_return << "% return" << std::endl;
    
    // Exercise 2-4: Nested loops - Price grid display
    std::cout << "\n--- Price Movement Grid ---" << std::endl;
    
    double base_price = 100.0;
    std::cout << "Price movements from $" << base_price << ":" << std::endl;
    std::cout << "     ";
    
    // Header row
    for (int day = 1; day <= 5; ++day) {
        std::cout << "Day" << day << "  ";
    }
    std::cout << std::endl;
    
    // Price rows
    for (int scenario = -2; scenario <= 2; ++scenario) {
        std::cout << std::setw(3) << scenario << "%  ";
        
        for (int day = 1; day <= 5; ++day) {
            double price = base_price * (1.0 + scenario * 0.01 * day);
            std::cout << std::setw(6) << price << " ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}

// Accelerated C++ Chapter 2 concepts:
// - for loops with initialization, condition, increment
// - Accumulation patterns (sum, count, average)
// - Finding maximum/minimum values
// - Nested loops for 2D data
// - Using loops for practical financial calculations