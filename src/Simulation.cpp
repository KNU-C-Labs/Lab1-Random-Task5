#include "include/Simulation.hpp"
#include <stdexcept>

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