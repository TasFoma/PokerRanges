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

    for (int r1 = 12; r1 >= 0; r1--) {
        for (int r2 = 12; r2 >= 0; r2--) {
            // Всегда ставим старший ранг первым
            int hi = std::max(r1, r2);
            int lo = std::min(r1, r2);
            std::string name;
            name += ranks[hi];
            name += ranks[lo];

            if (r1 == r2) {
                clusters_.push_back(Cluster(name));// Пары
            } else if (r1 > r2) {
                clusters_.push_back(Cluster(name + "s"));// Одномастные
            } else {
                clusters_.push_back(Cluster(name + "o"));// Разномастные
            }
        }
    }

    for (int i = 0; i < 1326; i++) {
        Hand hand = Hand::fromIndex(i);
        std::string clusterName = hand.getClusterName();
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
