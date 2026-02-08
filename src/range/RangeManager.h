#ifndef RANGEMANAGER_H
#define RANGEMANAGER_H

#include "Cluster.h"
#include "Range.h"
#include <vector>

class RangeManager {
  public:
    RangeManager();

    Range generate(); // Generate() -> Range

    const std::vector<Cluster> &getClusters() const {
        return clusters_;
    } // Получить кластеры для таблицы 13x13
    const Range &getRange() const { return range_; } // Получить текущий Range
    void printClusterTable() const;

  private:
    Range range_;
    std::vector<Cluster> clusters_;

    void createClusters();
};

#endif // RANGEMANAGER_H