#include "include/Simulation.hpp"
#include <iostream>
#include <limits>

template<typename T>
void inputWithValidation(T& variable, const std::string& prompt, const std::string& errorMessage, T minValue, T maxValue) {
    std::cout << prompt;
    while (!(std::cin >> variable) || variable < minValue || variable > maxValue) {
        std::cout << errorMessage;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    int suits, cards, runs;
    inputWithValidation(suits, "Enter number of suits (1-4): ", "Invalid input. Enter 1-4: ", 1, 4);
    inputWithValidation(cards, "Enter cards per deal: ", "Invalid input. Enter >0: ", 1, 52);
    inputWithValidation(runs, "Enter number of runs: ", "Invalid input. Enter >0: ", 1, 1000);
    try {
        Simulation sim(suits, cards, runs);
        sim.run();
        std::cout << "Most frequent card value: " << sim.mostFrequent() << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}

