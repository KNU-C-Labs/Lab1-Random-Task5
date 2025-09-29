#include "include/DeckDealer.hpp"
#include <algorithm>
#include <random>
#include <stdexcept>
DeckDealer::DeckDealer(int suitsCount_) : index(0), suitsCount(suitsCount_) {
    if (suitsCount < 1 || suitsCount > 4)
        throw std::invalid_argument("Suits must be between 1 and 4");
    buildDeck();
    shuffle();
}
void DeckDealer::buildDeck() {
    deck.clear();
    for (int s = 0; s < suitsCount; ++s) {
        for (int v = 1; v <= 13; ++v) {
            deck.emplace_back(static_cast<Card::Suit>(s), v);
        }
    }
}
void DeckDealer::shuffle() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    index = 0;
}
Card DeckDealer::deal() {
    if (index >= (int)deck.size()) {
        buildDeck();
        shuffle();
    }
    return deck[index++];
}
