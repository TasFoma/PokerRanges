#ifndef CLUSTER_H
#define CLUSTER_H

#include <vector>
#include <string>

class Range;  // предварительное объявление

class Cluster {
public:
  explicit Cluster(const std::string &name);

  void addHand(int handIndex);
  void getAverageStrategy(const Range &range, float &avgFold, float &avgCheck, float &avgBet) const;

  // Геттеры
  const std::string &getName() const { return name_; }
  int getHandCount() const { return handIndices_.size(); }

private:
    std::string name_;            // "AA", "AKs", "72o"
    std::vector<int> handIndices_; // индексы рук в этом кластере
};

#endif // CLUSTER_H