#include "Card.h"
#include <iostream>
#include <string>

// Конструкторы
Card::Card() : id_(0) {}

Card::Card(int id) : id_(id) {}

int Card::getId() const {
    return id_;
}

int Card::getRank() const {
    return id_ / 4;  // 0-12
}

int Card::getSuit() const {
    return id_ % 4;  // 0-3
}

// Преобразование в строку
std::string Card::toString() const {
    const char ranks[] = "23456789TJQKA";
    const char suits[] = "cdhs";

    std::string result;
    result += ranks[getRank()];
    result += suits[getSuit()];
    return result;
}

void Card::printCardTable() {
    const char ranks[] = "23456789TJQKA";
    const char suits[] = "cdhs";

    std::cout << "\n=== Card ID Mapping ===\n" << std::endl;
    std::cout << "* |R/S| C  | D  | H  | S  |" << std::endl;
    std::cout << "* |---|----|----|----|----|" << std::endl;

    for (int r = 0; r < 13; ++r) {
        std::cout << "| " << ranks[r] << " |";

        for (int s = 0; s < 4; ++s) {
            Card card(r * 4 + s);
            std::cout << " " << card.id_ << " |";
        }
        std::cout << std::endl;
    }
}