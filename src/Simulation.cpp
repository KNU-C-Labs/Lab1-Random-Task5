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
    freq.clear();

    for (int run = 0; run < runs; ++run) {
        DeckDealer dealer(suits);

        int stackLength = 0;
        Card prevCard = dealer.deal();
        stackLength = 1;

        for (int i = 1; i < cardsPerDeal; ++i) {
            Card currCard = dealer.deal();
            if (currCard.compare(prevCard) >= 0) {
                ++stackLength;
            } else {
                freq[stackLength]++;
                stackLength = 1;
            }
            prevCard = currCard;
        }
        freq[stackLength]++;
    }
}

int Simulation::mostFrequent() const {
    if (freq.empty()) throw std::runtime_error("No data");
    int bestLength = -1;
    int maxCount = -1;
    for (const auto& [length, count] : freq) {
        if (count > maxCount) {
            maxCount = count;
            bestLength = length;
        }
    }
    return bestLength;
}

double Simulation::average() const {
    if (freq.empty()) throw std::runtime_error("No data");
    double sum = 0;
    int total = 0;
    for (const auto& [length, count] : freq) {
        sum += length * count;
        total += count;
    }
    return sum / total;
}

double Simulation::median() const {
    if (freq.empty()) throw std::runtime_error("No data");
    std::vector<int> lengths;
    for (const auto& [length, count] : freq) {
        lengths.insert(lengths.end(), count, length);
    }
    std::sort(lengths.begin(), lengths.end());
    size_t n = lengths.size();
    if (n == 0) return 0;
    if (n % 2 == 1) {
        return lengths[n / 2];
    } else {
        return (lengths[n / 2 - 1] + lengths[n / 2]) / 2.0;
    }
}

void Simulation::printStats() const {
    if (freq.empty()) {
        std::cout << "No data\n";
        return;
    }

    int totalStacks = 0;
    for (const auto& [length, count] : freq) {
        totalStacks += count;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Total stacks: " << totalStacks << "\n";
    std::cout << "Stack length distribution (length : count, %):\n";
    for (const auto& [length, count] : freq) {
        double percent = 100.0 * count / totalStacks;
        std::cout << "  " << length << " : " << count << ", " << percent << "%\n";
    }

    std::cout << "Most frequent stack length: " << mostFrequent() << "\n";
    std::cout << "Average stack length: " << average() << "\n";
    std::cout << "Median stack length: " << median() << "\n";
}
