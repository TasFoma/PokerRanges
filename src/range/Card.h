#ifndef CARD_H
#define CARD_H
#include <string>

class Card {
private:
    int id_;  // 0-51

public:
    // Конструкторы
  Card();
  explicit Card(int id);

  // Геттеры
  int getId() const;
  int getRank() const; // (2-A)
  int getSuit() const; //(c,d,h,s)

  std::string toString() const;

  void printCardTable();
};
#endif