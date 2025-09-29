#ifndef DECKDEALER_HPP
#define DECKDEALER_HPP

#include "Card.hpp"
#include <vector>

class DeckDealer {
public:
    DeckDealer(int suitsCount = 4);
    void shuffle();
    Card deal();

private:
    std::vector<Card> deck;
    int index;
};

#endif // DECKDEALER_HPP