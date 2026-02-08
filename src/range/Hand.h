#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <string>

class Hand {
    Card card1_;
    Card card2_;

    void normalize();

    static int handIndexTable[52][52];
    static int reverseIndexTable[1326][2];
    static void initTables();

  public:
    Hand();
    Hand(Card c1, Card c2);

    Card getCard1() const;
    Card getCard2() const;

    bool isPair() const;
    bool isSuited() const;
    bool isOffSuited() const;

    std::string toString() const;

    int getIndex() const;
    static Hand fromIndex(int index);

    void printHands();

    std::string getClusterName() const {
        const char ranks[] = "23456789TJQKA";

        int r1 = card1_.getRank();
        int r2 = card2_.getRank();

        if (r1 < r2) std::swap(r1, r2);

        std::string name;
        name += ranks[r1];
        name += ranks[r2];

        if (isPair()) {
        } else if (isSuited()) {
            name += 's';
        } else {
            name += 'o';
        }

        return name;
    }
};

#endif // HAND_H