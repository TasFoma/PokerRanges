#include "RangeManager.h"
#include "Hand.h"
#include <iostream>

RangeManager::RangeManager() { createClusters(); }

Range RangeManager::generate() {
    range_.generateRandom();
    return range_;
}

void RangeManager::createClusters() {
    const char *ranks = "23456789TJQKA";

    for (int r1 = 12; r1 >= 0; r1--) {     // строки от A до 2
        for (int r2 = 12; r2 >= 0; r2--) { // столбцы от A до 2
            std::string name;
            name += ranks[r1];
            name += ranks[r2];

            if (r1 == r2) {
                clusters_.push_back(Cluster(name));
            } else if (r1 > r2) {
                clusters_.push_back(Cluster(name + "s")); // Одномастные выше диагонали:
            } else {
                clusters_.push_back(Cluster(name + "o")); // Разномастные ниже диагонали:
            }
        }
    }

    for (int i = 0; i < 1326; i++) {
        Hand hand = Hand::fromIndex(i);
        std::string clusterName = hand.getClusterName();

        // Находим нужный кластер и добавляем руку
        for (auto &cluster : clusters_) {
            if (cluster.getName() == clusterName) {
                cluster.addHand(i);
                break;
            }
        }
    }
}
void RangeManager::printClusterTable() const {
    const char *ranks = "AKQJT98765432";

    std::cout << "\n=== CLUSTER TABLE 13x13 ===\n";
    std::cout << "     ";
    for (int i = 0; i < 13; i++) {
        std::cout << ranks[i] << "    ";
    }
    std::cout << "\n";

    for (int row = 0; row < 13; row++) {
        std::cout << ranks[row] << " | ";
        for (int col = 0; col < 13; col++) {
            int idx = row * 13 + col;
            if (idx < clusters_.size()) {
                std::cout << clusters_[idx].getName();
                if (clusters_[idx].getName().length() == 2)
                    std::cout << "   ";
                else
                    std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}