// Deep Hedging Implementation
// Based on: "Deep Hedging" (Buehler et al., 2019)

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

class NeuralNetwork {
private:
    std::vector<std::vector<std::vector<double>>> weights;
    std::vector<std::vector<double>> biases;
    
public:
    NeuralNetwork(const std::vector<int>& layers) {
        for (int i = 0; i < layers.size() - 1; ++i) {
            weights.push_back(std::vector<std::vector<double>>(
                layers[i], std::vector<double>(layers[i+1])));
            biases.push_back(std::vector<double>(layers[i+1]));
            
            // Random initialization
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> normal(0.0, 0.1);
            
            for (auto& row : weights.back()) {
                for (auto& w : row) {
                    w = normal(gen);
                }
            }
            for (auto& b : biases.back()) {
                b = normal(gen);
            }
        }
    }
    
    std::vector<double> forward(const std::vector<double>& input) {
        std::vector<double> current = input;
        
        for (int layer = 0; layer < weights.size(); ++layer) {
            std::vector<double> next(weights[layer][0].size(), 0.0);
            
            for (int j = 0; j < next.size(); ++j) {
                for (int i = 0; i < current.size(); ++i) {
                    next[j] += current[i] * weights[layer][i][j];
                }
                next[j] += biases[layer][j];
                
                // ReLU activation (except last layer)
                if (layer < weights.size() - 1) {
                    next[j] = std::max(0.0, next[j]);
                }
            }
            current = next;
        }
        
        return current;
    }
};

class DeepHedgingAgent {
private:
    NeuralNetwork network;
    double transaction_cost;
    
public:
    DeepHedgingAgent(double tc = 0.001) 
        : network({5, 32, 32, 1}), transaction_cost(tc) {}
    
    // Get hedging position based on market state
    double getHedgeRatio(double S, double t, double vol, double delta_prev, double pnl) {
        std::vector<double> features = {S/100.0, t, vol, delta_prev, pnl/1000.0};
        auto output = network.forward(features);
        return std::tanh(output[0]); // Bounded between -1 and 1
    }
    
    // Simulate hedging strategy
    double simulateHedging(double S0, double K, double T, double vol, double r = 0.05) {
        int n_steps = 50;
        double dt = T / n_steps;
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> normal(0.0, 1.0);
        
        double S = S0;
        double delta = 0.0;
        double cash = 0.0;
        double pnl = 0.0;
        
        for (int i = 0; i < n_steps; ++i) {
            double t = i * dt;
            
            // Get new hedge ratio from neural network
            double new_delta = getHedgeRatio(S, t/T, vol, delta, pnl);
            
            // Transaction cost
            double trade_amount = new_delta - delta;
            cash -= trade_amount * S + transaction_cost * std::abs(trade_amount) * S;
            delta = new_delta;
            
            // Update P&L
            pnl = delta * S + cash;
            
            // Evolve stock price
            double dW = normal(gen) * std::sqrt(dt);
            S *= std::exp((r - 0.5 * vol * vol) * dt + vol * dW);
        }
        
        // Final P&L including option payoff
        double option_payoff = std::max(S - K, 0.0);
        double final_pnl = delta * S + cash - option_payoff;
        
        return final_pnl;
    }
    
    // Train the network (simplified version)
    void train(int episodes = 1000) {
        std::cout << "Training Deep Hedging Agent...\n";
        
        double total_loss = 0.0;
        for (int ep = 0; ep < episodes; ++ep) {
            // Random market parameters
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> uniform(0.8, 1.2);
            
            double S0 = 100.0 * uniform(gen);
            double K = 100.0;
            double vol = 0.2 * uniform(gen);
            
            double pnl = simulateHedging(S0, K, 0.25, vol);
            total_loss += pnl * pnl; // Minimize variance of P&L
            
            if (ep % 100 == 0) {
                std::cout << "Episode " << ep << ", Avg Loss: " << total_loss / (ep + 1) << std::endl;
            }
        }
    }
};

int main() {
    std::cout << "Deep Hedging Implementation (Buehler et al. 2019)\n";
    std::cout << "================================================\n";
    
    DeepHedgingAgent agent(0.001); // 0.1% transaction cost
    
    // Train the agent
    agent.train(500);
    
    // Test hedging performance
    std::cout << "\nTesting hedging performance:\n";
    
    std::vector<double> pnls;
    for (int i = 0; i < 100; ++i) {
        double pnl = agent.simulateHedging(100.0, 100.0, 0.25, 0.2);
        pnls.push_back(pnl);
    }
    
    double mean_pnl = 0.0, var_pnl = 0.0;
    for (double pnl : pnls) {
        mean_pnl += pnl;
    }
    mean_pnl /= pnls.size();
    
    for (double pnl : pnls) {
        var_pnl += (pnl - mean_pnl) * (pnl - mean_pnl);
    }
    var_pnl /= pnls.size();
    
    std::cout << "Mean P&L: " << mean_pnl << std::endl;
    std::cout << "P&L Variance: " << var_pnl << std::endl;
    std::cout << "P&L Std Dev: " << std::sqrt(var_pnl) << std::endl;
    
    return 0;
}