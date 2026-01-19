// Accelerated C++ Chapter 0: Getting Started
// Finance-focused exercises following the book's approach

#include <iostream>
#include <string>

int main() {
    std::cout << "Accelerated C++ - Chapter 0: Finance Edition" << std::endl;
    
    // Exercise 0-1: Hello World with finance twist
    std::cout << "Hello, Quantitative Finance!" << std::endl;
    
    // Exercise 0-2: Simple calculation (like the book's example)
    std::cout << "The sum of 1000 shares at $50.25 each is: $" 
              << 1000 * 50.25 << std::endl;
    
    // Exercise 0-3: Using variables (extending the book's approach)
    double share_price = 125.75;
    int quantity = 500;
    double total_value = share_price * quantity;
    
    std::cout << "Portfolio calculation:" << std::endl;
    std::cout << quantity << " shares at $" << share_price 
              << " = $" << total_value << std::endl;
    
    // Exercise 0-4: String operations (preparing for Chapter 1)
    std::string symbol = "AAPL";
    std::cout << "Trading symbol: " << symbol << std::endl;
    
    return 0;
}

// Key Accelerated C++ principles demonstrated:
// - Start with complete programs immediately
// - Use standard library from the beginning
// - Focus on practical examples
// - Build complexity gradually