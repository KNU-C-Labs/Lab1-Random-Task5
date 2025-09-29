#include "include/Card.hpp"
#include <stdexcept>

Card::Card(Suit s, int v) : suit(s), value(v) {
    if (v < 1 || v > 13)
        throw std::invalid_argument("Card value must be 1-13");
}

std::string Card::toString() const {
    static const char* suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    static const char* names[] = {"", "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
    return std::string(names[value]) + " of " + suits[suit];
}

Card::Suit Card::getSuit() const { return suit; }

int Card::getValue() const { return value; }

int Card::compare(const Card& other) const {
    if (value < other.value) return -1;
    if (value > other.value) return 1;
    if (suit < other.suit) return -1;
    if (suit > other.suit) return 1;
    return 0;
}
