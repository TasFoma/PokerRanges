#include "range/Card.h"
#include "range/Hand.h"
#include <iostream>

int main() {
    std::cout << "=== POKER RANGE SYSTEM TEST ===\n" << std::endl;

    // 1. Таблица карт
    std::cout << "1. CARD TABLE:" << std::endl;
    Card card(0);
    card.printCardTable();

    // 2. Тест карт
    std::cout << "\n2. CARD TESTS:" << std::endl;
    Card cards[] = {
        Card(0),   // 2c
        Card(1),   // 2d
        Card(4),   // 3c
        Card(48),  // Ac
        Card(51)   // As
    };

    for (int i = 0; i < 5; i++) {
        std::cout << "Card " << cards[i].getId() << ": "
                  << cards[i].toString() << std::endl;
    }

    // 3. Тест рук
    std::cout << "\n3. HAND TESTS:" << std::endl;
    Hand pairHand(Card(0), Card(1));
    std::cout << "Pair: " << pairHand.toString()
              << " | Index: " << pairHand.getIndex() << std::endl;

    return 0;
}
