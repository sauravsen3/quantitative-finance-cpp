// Path Signature Methods for Finance
// Based on: "A primer on the signature method in machine learning" (Chevyrev & Kormilitzin, 2016)
// Application: "Signature methods in finance" (Lyons et al., 2020)

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class PathSignature {
private:
    int truncation_level;
    
public:
    PathSignature(int level = 3) : truncation_level(level) {}
    
    // Calculate signature of a path up to given level
    std::vector<double> calculateSignature(const std::vector<std::vector<double>>& path) {
        std::vector<double> signature;
        
        // Level 0: constant term
        signature.push_back(1.0);
        
        // Level 1: linear terms (increments)
        int dim = path[0].size();
        std::vector<double> level1(dim, 0.0);
        
        for (int i = 1; i < path.size(); ++i) {
            for (int d = 0; d < dim; ++d) {
                level1[d] += path[i][d] - path[i-1][d];
            }
        }
        
        for (double val : level1) {
            signature.push_back(val);
        }
        
        // Level 2: quadratic terms (area-like terms)
        if (truncation_level >= 2) {
            for (int d1 = 0; d1 < dim; ++d1) {
                for (int d2 = 0; d2 < dim; ++d2) {
                    double area = 0.0;
                    double sum1 = 0.0;
                    
                    for (int i = 1; i < path.size(); ++i) {
                        double inc1 = path[i][d1] - path[i-1][d1];
                        double inc2 = path[i][d2] - path[i-1][d2];
                        
                        area += sum1 * inc2;
                        sum1 += inc1;
                    }
                    
                    signature.push_back(area);
                }
            }
        }
        
        return signature;
    }
    
    // Calculate log signature (more stable for long paths)
    std::vector<double> calculateLogSignature(const std::vector<std::vector<double>>& path) {
        auto sig = calculateSignature(path);
        
        // Extract log signature components (simplified)
        std::vector<double> log_sig;
        
        // Level 1 terms are the same
        int dim = path[0].size();
        for (int i = 1; i <= dim; ++i) {
            log_sig.push_back(sig[i]);
        }
        
        // Level 2: antisymmetric part
        if (truncation_level >= 2) {
            int start_idx = 1 + dim;
            for (int d1 = 0; d1 < dim; ++d1) {
                for (int d2 = d1 + 1; d2 < dim; ++d2) {
                    double antisym = sig[start_idx + d1*dim + d2] - sig[start_idx + d2*dim + d1];
                    log_sig.push_back(antisym);
                }
            }
        }
        
        return log_sig;
    }
};

class SignatureBasedPredictor {
private:
    PathSignature signature_calc;
    std::vector<std::vector<double>> feature_weights;
    
public:
    SignatureBasedPredictor(int sig_level = 3) : signature_calc(sig_level) {
        // Initialize simple linear model weights
        feature_weights.resize(1);
    }
    
    // Extract features from price path using signatures
    std::vector<double> extractFeatures(const std::vector<double>& prices) {
        // Convert price path to log-return path
        std::vector<std::vector<double>> path;
        
        for (int i = 1; i < prices.size(); ++i) {
            double log_return = std::log(prices[i] / prices[i-1]);
            double abs_return = std::abs(log_return);
            path.push_back({log_return, abs_return});
        }
        
        // Calculate signature features
        auto sig_features = signature_calc.calculateLogSignature(path);
        
        // Add traditional features
        std::vector<double> features = sig_features;
        
        // Realized volatility
        double realized_vol = 0.0;
        for (int i = 1; i < prices.size(); ++i) {
            double ret = std::log(prices[i] / prices[i-1]);
            realized_vol += ret * ret;
        }
        realized_vol = std::sqrt(realized_vol / (prices.size() - 1));
        features.push_back(realized_vol);
        
        // Price momentum
        double momentum = std::log(prices.back() / prices[0]);
        features.push_back(momentum);
        
        return features;
    }
    
    // Predict next period volatility
    double predictVolatility(const std::vector<double>& prices) {
        auto features = extractFeatures(prices);
        
        // Simple linear prediction (in practice, use more sophisticated ML)
        double prediction = 0.2; // Base volatility
        
        if (features.size() >= 2) {
            // Use signature features for prediction
            prediction += 0.1 * features[0]; // Log return signature
            prediction += 0.05 * features[features.size()-1]; // Realized vol
            prediction = std::max(0.01, std::min(1.0, prediction)); // Bound prediction
        }
        
        return prediction;
    }
    
    // Detect regime changes using signature analysis
    bool detectRegimeChange(const std::vector<double>& prices, int window = 20) {
        if (prices.size() < 2 * window) return false;
        
        // Compare signatures of recent vs historical windows
        std::vector<double> recent(prices.end() - window, prices.end());
        std::vector<double> historical(prices.end() - 2*window, prices.end() - window);
        
        auto sig_recent = extractFeatures(recent);
        auto sig_historical = extractFeatures(historical);
        
        // Calculate signature distance
        double distance = 0.0;
        int min_size = std::min(sig_recent.size(), sig_historical.size());
        
        for (int i = 0; i < min_size; ++i) {
            distance += (sig_recent[i] - sig_historical[i]) * (sig_recent[i] - sig_historical[i]);
        }
        
        distance = std::sqrt(distance);
        
        // Threshold for regime change detection
        return distance > 0.5;
    }
};

int main() {
    std::cout << "Path Signature Methods for Finance\n";
    std::cout << "==================================\n";
    
    // Generate sample price path
    std::vector<double> prices = {100.0};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> normal(0.0, 0.02);
    
    // Simulate price path with regime change
    for (int i = 1; i <= 100; ++i) {
        double vol = (i < 50) ? 0.15 : 0.25; // Regime change at i=50
        double return_rate = normal(gen) * vol;
        prices.push_back(prices.back() * std::exp(return_rate));
    }
    
    SignatureBasedPredictor predictor(3);
    
    // Test volatility prediction
    std::cout << "Volatility Predictions:\n";
    for (int i = 30; i < prices.size(); i += 10) {
        std::vector<double> window(prices.begin() + i - 20, prices.begin() + i);
        double pred_vol = predictor.predictVolatility(window);
        bool regime_change = predictor.detectRegimeChange(std::vector<double>(prices.begin(), prices.begin() + i));
        
        std::cout << "Day " << i << ": Predicted Vol = " << pred_vol 
                  << ", Regime Change = " << (regime_change ? "Yes" : "No") << std::endl;
    }
    
    // Demonstrate signature calculation
    std::vector<std::vector<double>> sample_path = {{0, 0}, {1, 0.5}, {2, 1.2}, {3, 0.8}};
    PathSignature sig_calc(2);
    auto signature = sig_calc.calculateSignature(sample_path);
    
    std::cout << "\nSample Path Signature: ";
    for (double val : signature) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    return 0;
}