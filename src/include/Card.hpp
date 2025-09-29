#ifndef CARD_HPP
#define CARD_HPP

#include <string>

class Card {
public:
    enum Suit { Hearts, Diamonds, Clubs, Spades };

    Card(Suit suit, int value);
    std::string toString() const;

    Suit getSuit() const;
    int getValue() const;

    int compare(const Card& other) const;

private:
    Suit suit;
    int value;
};

#endif // CARD_HPP
