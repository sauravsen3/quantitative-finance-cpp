// Accelerated C++ Chapter 1: Working with Strings
// Finance applications using string operations

#include <iostream>
#include <string>

int main() {
    std::cout << "=== Chapter 1: Strings in Finance ===" << std::endl;
    
    // Exercise 1-1: Basic string input/output (like the greeting program)
    std::string trader_name;
    std::cout << "Enter trader name: ";
    std::cin >> trader_name;
    
    std::cout << "Welcome to the trading desk, " << trader_name << "!" << std::endl;
    
    // Exercise 1-2: String concatenation for trade messages
    std::string symbol = "MSFT";
    std::string action = "BUY";
    std::string quantity = "1000";
    
    std::string trade_order = action + " " + quantity + " " + symbol;
    std::cout << "Trade order: " << trade_order << std::endl;
    
    // Exercise 1-3: Creating formatted output (like the framed greeting)
    std::string message = "MARKET OPEN";
    std::string border(message.size() + 4, '*');
    
    std::cout << border << std::endl;
    std::cout << "* " << message << " *" << std::endl;
    std::cout << border << std::endl;
    
    // Exercise 1-4: Multi-word input (getline)
    std::string company_name;
    std::cout << "Enter company name: ";
    std::cin.ignore(); // Clear the input buffer
    std::getline(std::cin, company_name);
    
    std::cout << "Company: " << company_name << std::endl;
    
    // Exercise 1-5: String size and manipulation
    std::string ticker = "GOOGL";
    std::cout << "Ticker length: " << ticker.size() << " characters" << std::endl;
    
    // Create a formatted ticker display
    std::string ticker_frame(ticker.size() + 6, '=');
    std::cout << ticker_frame << std::endl;
    std::cout << "|| " << ticker << " ||" << std::endl;
    std::cout << ticker_frame << std::endl;
    
    return 0;
}

// Accelerated C++ Chapter 1 concepts:
// - std::string as a fundamental type
// - String operations: +, size()
// - Input with >> and getline()
// - Creating formatted output
// - Building practical applications immediately