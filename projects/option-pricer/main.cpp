// Project 1: Option Pricing Library
// GitHub: option-pricing-cpp

#include <iostream>
#include <cmath>
#include <memory>

class Option {
protected:
    double strike, expiry, spot, rate, volatility;
    
public:
    Option(double S, double K, double T, double r, double sigma)
        : spot(S), strike(K), expiry(T), rate(r), volatility(sigma) {}
    
    virtual ~Option() = default;
    virtual double price() const = 0;
    virtual double delta() const = 0;
    virtual double gamma() const = 0;
};

class EuropeanCall : public Option {
public:
    EuropeanCall(double S, double K, double T, double r, double sigma)
        : Option(S, K, T, r, sigma) {}
    
    double price() const override {
        double d1 = (std::log(spot/strike) + (rate + 0.5*volatility*volatility)*expiry) 
                   / (volatility * std::sqrt(expiry));
        double d2 = d1 - volatility * std::sqrt(expiry);
        
        return spot * normalCDF(d1) - strike * std::exp(-rate * expiry) * normalCDF(d2);
    }
    
    double delta() const override {
        double d1 = (std::log(spot/strike) + (rate + 0.5*volatility*volatility)*expiry) 
                   / (volatility * std::sqrt(expiry));
        return normalCDF(d1);
    }
    
    double gamma() const override {
        double d1 = (std::log(spot/strike) + (rate + 0.5*volatility*volatility)*expiry) 
                   / (volatility * std::sqrt(expiry));
        return normalPDF(d1) / (spot * volatility * std::sqrt(expiry));
    }
    
private:
    double normalCDF(double x) const {
        return 0.5 * (1 + std::erf(x / std::sqrt(2)));
    }
    
    double normalPDF(double x) const {
        return std::exp(-0.5 * x * x) / std::sqrt(2 * M_PI);
    }
};

int main() {
    auto call = std::make_unique<EuropeanCall>(100, 100, 1.0, 0.05, 0.2);
    
    std::cout << "European Call Option Pricing\n";
    std::cout << "============================\n";
    std::cout << "Price: $" << call->price() << std::endl;
    std::cout << "Delta: " << call->delta() << std::endl;
    std::cout << "Gamma: " << call->gamma() << std::endl;
    
    return 0;
}