#include "Hand.h"
#include <iostream>
#include <sstream>

int Hand::handIndexTable[52][52];
int Hand::reverseIndexTable[1326][2];

void Hand::initTables()
{
    int indexHand = 0;
    for (int i = 0; i < 52; ++i)
    {
        for (int j = i + 1; j < 52; ++j)
        {
            handIndexTable[i][j] = indexHand;
            handIndexTable[j][i] = indexHand;
            reverseIndexTable[indexHand][0] = i;
            reverseIndexTable[indexHand][1] = j;
            indexHand++;
        }
    }
}
void Hand::printHands()
{
    const int TOTAL_HANDS = 1326;
    for (int indexHand = 0; indexHand < TOTAL_HANDS; indexHand++)
    {
        Card c1{reverseIndexTable[indexHand][0]};
        Card c2{reverseIndexTable[indexHand][1]};
        std::cout << " {" << c1.toString() << ", " << c2.toString()
                  << "} <-> " << indexHand;
                  if(indexHand % 10 == 0){
                    std::cout<<"\n";
                  }
    }
}

// Конструкторы
 Hand::Hand() : card1_(0), card2_(1) {
   initTables();
}

 Hand::Hand(Card c1, Card c2) : card1_(c1), card2_(c2) {
    initTables();
}

// Геттеры
Card Hand::getCard1() const { return card1_; }
Card Hand::getCard2() const { return card2_; }


bool Hand::isPair() const
{
    return card1_.getRank() == card2_.getRank();
}

bool Hand::isSuited() const
{
    return !isPair() && (card1_.getSuit() == card2_.getSuit());
}

bool Hand::isOffSuited() const
{
    return !isPair() && (card1_.getSuit() != card2_.getSuit());
}

std::string Hand::toString() const
{
    std::stringstream ss;
    ss << card1_.toString() << " " << card2_.toString();
    return ss.str();
}

int Hand::getIndex() const {
    return handIndexTable[card1_.getId()][card2_.getId()];
}

Hand Hand::fromIndex(int index) {
    int id1 = reverseIndexTable[index][0];
    int id2 = reverseIndexTable[index][1];

    Card c1(id1);
    Card c2(id2);

    return Hand(c1, c2);
}
