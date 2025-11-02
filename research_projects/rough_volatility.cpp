// Implementation of Rough Volatility Models
// Based on: "Volatility is rough" (Gatheral, Jaisson, Rosenbaum, 2018)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

class RoughVolatilityModel {
private:
    double H;           // Hurst parameter (typically 0.1 for rough volatility)
    double xi;          // Volatility of volatility
    double rho;         // Correlation between price and volatility
    double v0;          // Initial variance
    
public:
    RoughVolatilityModel(double hurst, double vol_of_vol, double correlation, double initial_var)
        : H(hurst), xi(vol_of_vol), rho(correlation), v0(initial_var) {}
    
    // Fractional Brownian Motion generator
    std::vector<double> generateFBM(int n, double T) {
        std::vector<double> fbm(n + 1, 0.0);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> normal(0.0, 1.0);
        
        double dt = T / n;
        
        for (int i = 1; i <= n; ++i) {
            fbm[i] = fbm[i-1] + std::sqrt(dt) * std::pow(dt, H - 0.5) * normal(gen);
        }
        
        return fbm;
    }
    
    // Rough Heston simulation
    std::pair<std::vector<double>, std::vector<double>> simulateRoughHeston(int n, double T, double S0) {
        std::vector<double> prices(n + 1);
        std::vector<double> variances(n + 1);
        
        prices[0] = S0;
        variances[0] = v0;
        
        auto fbm = generateFBM(n, T);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> normal(0.0, 1.0);
        
        double dt = T / n;
        
        for (int i = 1; i <= n; ++i) {
            double dW1 = normal(gen) * std::sqrt(dt);
            double dW2 = rho * dW1 + std::sqrt(1 - rho*rho) * normal(gen) * std::sqrt(dt);
            
            // Rough variance process
            double dBH = fbm[i] - fbm[i-1];
            variances[i] = variances[i-1] + xi * std::sqrt(variances[i-1]) * dBH;
            variances[i] = std::max(variances[i], 0.001);
            
            // Price process
            prices[i] = prices[i-1] * std::exp(-0.5 * variances[i-1] * dt + 
                                              std::sqrt(variances[i-1]) * dW1);
        }
        
        return {prices, variances};
    }
};

int main() {
    RoughVolatilityModel model(0.1, 0.3, -0.7, 0.04);
    
    std::cout << "Rough Volatility Model (Gatheral et al. 2018)\n";
    std::cout << "=============================================\n";
    
    auto [prices, variances] = model.simulateRoughHeston(252, 1.0, 100.0);
    
    std::cout << "Final price: $" << prices.back() << std::endl;
    std::cout << "Final variance: " << variances.back() << std::endl;
    
    return 0;
}