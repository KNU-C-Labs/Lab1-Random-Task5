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
    int suitsCount;

    void buildDeck();
};

#endif // DECKDEALER_HPP
