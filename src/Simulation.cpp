#include "include/Simulation.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iomanip>

Simulation::Simulation(int s, int c, int r) : suits(s), cardsPerDeal(c), runs(r) {
    if (suits < 1 || suits > 4) throw std::invalid_argument("Invalid suits");
    if (cardsPerDeal < 1) throw std::invalid_argument("Invalid cards per deal");
    if (runs < 1) throw std::invalid_argument("Invalid runs");
}

void Simulation::run() {
    for (int i = 0; i < runs; ++i) {
        DeckDealer dealer(suits);
        dealer.shuffle();
        for (int j = 0; j < cardsPerDeal; ++j) {
            Card c = dealer.deal();
            freq[c.getValue()]++;
        }
    }
}

int Simulation::mostFrequent() const {
    int best = -1, maxCount = -1;
    for (auto &kv : freq) {
        if (kv.second > maxCount || (kv.second == maxCount && kv.first < best)) {
            best = kv.first;
            maxCount = kv.second;
        }
    }
    return best;
}

double Simulation::average() const {
    if (freq.empty()) throw std::runtime_error("No data");
    double sum = 0;
    int total = 0;
    for (auto &kv : freq) {
        sum += kv.first * kv.second;
        total += kv.second;
    }
    return sum / total;
}

double Simulation::median() const {
    if (freq.empty()) throw std::runtime_error("No data");
    std::vector<int> sortedValues;
    for (auto &kv : freq) {
        sortedValues.insert(sortedValues.end(), kv.second, kv.first);
    }
    std::sort(sortedValues.begin(), sortedValues.end());
    size_t n = sortedValues.size();
    return (n % 2 == 0) ? (sortedValues[n/2 - 1] + sortedValues[n/2]) / 2.0
                        : sortedValues[n/2];
}

void Simulation::printStats() const {
    if (freq.empty()) {
        std::cout << "No data\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Most frequent value: " << mostFrequent() << "\n";
    std::cout << "Average value: " << average() << "\n";
    std::cout << "Median value: " << median() << "\n";

    std::cout << "Card counts:\n";
    for (auto &kv : freq) {
        std::cout << "Value " << kv.first << ": " << kv.second << " times\n";
    }
}