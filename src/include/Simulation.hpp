#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "DeckDealer.hpp"
#include <map>
#include <vector>

class Simulation {
public:
    Simulation(int suits, int cardsPerDeal, int runs);
    void run();
    int mostFrequent() const;
    double average() const;
    double median() const;
    void printStats() const;

private:
    int suits;
    int cardsPerDeal;
    int runs;
    std::map<int,int> freq;
};

#endif // SIMULATION_HPP
