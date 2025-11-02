// Project 2: Portfolio Risk Management System
// GitHub: portfolio-risk-manager-cpp

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <cmath>

struct Asset {
    std::string symbol;
    double weight;
    double expectedReturn;
    double volatility;
    std::vector<double> returns;
};

class Portfolio {
private:
    std::vector<Asset> assets;
    std::vector<std::vector<double>> correlationMatrix;
    
public:
    void addAsset(const Asset& asset) {
        assets.push_back(asset);
    }
    
    double calculateExpectedReturn() const {
        return std::accumulate(assets.begin(), assets.end(), 0.0,
            [](double sum, const Asset& asset) {
                return sum + asset.weight * asset.expectedReturn;
            });
    }
    
    double calculateVolatility() const {
        double variance = 0.0;
        
        // Individual asset variance contribution
        for (const auto& asset : assets) {
            variance += asset.weight * asset.weight * asset.volatility * asset.volatility;
        }
        
        // Correlation contribution (simplified - assumes correlation = 0.3)
        for (size_t i = 0; i < assets.size(); ++i) {
            for (size_t j = i + 1; j < assets.size(); ++j) {
                variance += 2 * assets[i].weight * assets[j].weight * 
                           assets[i].volatility * assets[j].volatility * 0.3;
            }
        }
        
        return std::sqrt(variance);
    }
    
    double calculateSharpeRatio(double riskFreeRate = 0.02) const {
        double excessReturn = calculateExpectedReturn() - riskFreeRate;
        return excessReturn / calculateVolatility();
    }
    
    double calculateVaR(double confidence = 0.05) const {
        // Parametric VaR calculation
        double portfolioReturn = calculateExpectedReturn();
        double portfolioVol = calculateVolatility();
        
        // Z-score for 95% confidence (1.645)
        double zScore = 1.645;
        return -(portfolioReturn - zScore * portfolioVol);
    }
    
    void printAnalysis() const {
        std::cout << "Portfolio Analysis\n";
        std::cout << "==================\n";
        std::cout << "Expected Return: " << calculateExpectedReturn() * 100 << "%\n";
        std::cout << "Volatility: " << calculateVolatility() * 100 << "%\n";
        std::cout << "Sharpe Ratio: " << calculateSharpeRatio() << "\n";
        std::cout << "VaR (95%): " << calculateVaR() * 100 << "%\n";
    }
};

int main() {
    Portfolio portfolio;
    
    portfolio.addAsset({"AAPL", 0.4, 0.12, 0.25, {}});
    portfolio.addAsset({"GOOGL", 0.3, 0.15, 0.30, {}});
    portfolio.addAsset({"BONDS", 0.3, 0.04, 0.05, {}});
    
    portfolio.printAnalysis();
    
    return 0;
}