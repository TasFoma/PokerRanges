#include <range/Card.h>
#include <range/Hand.h>
#include <range/RangeManager.h>
#include <iostream>

int main() {
    std::cout << "=== POKER RANGE SYSTEM TEST ===\n" << std::endl;

    // 1. Таблица карт
    std::cout << "1. CARD TABLE:" << std::endl;
    Card card(0);  // создаем объект
    card.printCardTable();

    // 2. Таблица рук (индексы)
    std::cout << "\n2. HAND INDEX TABLE:" << std::endl;
    Hand hand(Card{0}, Card{1});
    hand.printHands();
    Card c = hand.getCard1();

    std::cout << "\n -HAAAAND " << c.toString() << "\n";
    // 3. Тест нескольких карт
    std::cout << "3. CARD TESTS:" << std::endl;
    std::cout << "----------------" << std::endl;

    Card cards[] = {
        Card(0),  // 2c
        Card(1),  // 2d
        Card(4),  // 3c
        Card(48), // Ac
        Card(51)  // As
    };

    for (int i = 0; i < 5; i++) {
        std::cout << "Card " << cards[i].getId() << ": " << cards[i].toString()
                  << " (rank: " << cards[i].getRank() << ", suit: " << cards[i].getSuit() << ")"
                  << std::endl;
    }

    // 4. Тест рук разных типов
    std::cout << "\n4. HAND TYPE TESTS:" << std::endl;
    std::cout << "-------------------" << std::endl;

    // Пара
  Hand pairHand(Card(0), Card(1));  // 2c 2d
  std::cout << "Pair: " << pairHand.toString() << " | Index: " << pairHand.getIndex()
            << " | Is pair: " << (pairHand.isPair() ? "YES" : "NO")
            << " | Is suited: " << (pairHand.isSuited() ? "YES" : "NO")
            << " | Is offsuit: " << (pairHand.isOffSuited() ? "YES" : "NO") << std::endl;

  // Одномастные
  Hand suitedHand(Card(48), Card(44)); // Ac Kc
  std::cout << "Suited: " << suitedHand.toString() << " | Index: " << suitedHand.getIndex()
            << " | Is pair: " << (suitedHand.isPair() ? "YES" : "NO")
            << " | Is suited: " << (suitedHand.isSuited() ? "YES" : "NO")
            << " | Is offsuit: " << (suitedHand.isOffSuited() ? "YES" : "NO") << std::endl;

  // Разномастные
  Hand offsuitHand(Card(48), Card(45)); // Ac Kd
  std::cout << "Offsuit: " << offsuitHand.toString() << " | Index: " << offsuitHand.getIndex()
            << " | Is pair: " << (offsuitHand.isPair() ? "YES" : "NO")
            << " | Is suited: " << (offsuitHand.isSuited() ? "YES" : "NO")
            << " | Is offsuit: " << (offsuitHand.isOffSuited() ? "YES" : "NO") << std::endl;

  // 5. Тест восстановления по индексу
  std::cout << "\n5. INDEX ROUND-TRIP TESTS:" << std::endl;
  std::cout << "-------------------------" << std::endl;

  int testIndices[] = {0, 1, 100, 500, 1000, 1325};

  for (int idx : testIndices) {
      try {
          Hand h = Hand::fromIndex(idx);
          int backIndex = h.getIndex();
          std::cout << "Index " << idx << " -> " << h.toString() << " -> back to index "
                    << backIndex << " | " << (idx == backIndex ? "OK" : "FAIL") << std::endl;
      } catch (const std::exception &e) {
          std::cout << "Index " << idx << " -> ERROR: " << e.what() << std::endl;
      }
    }

    // Тест Range
    std::cout << "TESTING RANGE:" << std::endl;
    std::cout << "-----------------" << std::endl;

    Range range;
    range.generateRandom();
    std::cout << "\nSample strategies:" << std::endl;
    int sampleHands[] = {0, 1, 100, 500};

    for (int i : sampleHands) {
        float fold, check, bet;
        range.getStrategy(i, fold, check, bet);

        std::cout << "Hand " << i << ": "
                  << "F=" << fold << " "
                  << "C=" << check << " "
                  << "B=" << bet << " "
                  << "(sum=" << (fold + check + bet) << ")" << "\n\n";
    }

    //Тест кластеризации
    std::cout << "\n\n TESTING CLUSTERS:" << std::endl;
    std::cout << "-------------------" << std::endl;

    RangeManager manager;

    Cluster aaCluster("AA");
    Cluster aksCluster("AKs");
    Cluster akoCluster("AKo");

    aaCluster.addHand(1325);  // Ah As
    aaCluster.addHand(1324);  // Ad As
    aaCluster.addHand(1323);  // Ac As
    float avgFold, avgCheck, avgBet;
    aaCluster.getAverageStrategy(range, avgFold, avgCheck, avgBet);

    std::cout << "Cluster AA average strategy:" << std::endl;
    std::cout << "  F=" << avgFold << " C=" << avgCheck << " B=" << avgBet << std::endl;
    std::cout << "  Sum: " << (avgFold + avgCheck + avgBet) << "\n";

    //  Генерация нового Range через RangeManager
    std::cout << "\n\n TESTING RANGEMANAGER GENERATE():" << "\n";
    std::cout << "-----------------------------------" << "\n";

    Range newRange = manager.generate();
    std::cout << "Generated new range with " << Range::TOTAL_HANDS << " hands" << "\n";

    // Проверка кластеров RangeManager
    std::cout << "\n\n TESTING RANGEMANAGER CLUSTERS:" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    const auto& clusters = manager.getClusters();
    std::cout << "Total clusters created: " << clusters.size() << " (should be 169)" << std::endl;

    // Показать несколько кластеров
    std::cout << "\n First 10 clusters:" << std::endl;
    for (int i = 0; i < 10 && i < clusters.size(); i++) {
        std::cout << "  " << clusters[i].getName() << " (" << clusters[i].getHandCount()
                  << " hands)" << std::endl;
    }

   manager.printClusterTable();

    // как получить стратегию для кластера AKs
    std::cout << "\n\n CLUSTER STRATEGY CALCULATION:" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    // Ищем кластер AKs
    for (const auto& cluster : clusters) {
        if (cluster.getName() == "AKs") {
            cluster.getAverageStrategy(manager.getRange(), avgFold, avgCheck, avgBet);

            std::cout << "Cluster " << cluster.getName() << ":" << std::endl;
            std::cout << "  Average Fold: " << avgFold << std::endl;
            std::cout << "  Average Check: " << avgCheck << std::endl;
            std::cout << "  Average Bet: " << avgBet << std::endl;
            std::cout << "  Total hands in cluster: " << cluster.getHandCount() << std::endl;
            break;
        }
    }

    std::cout << "\n=== ALL TESTS COMPLETE ===" << std::endl;



    return 0;
}