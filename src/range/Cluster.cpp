#include "Cluster.h"
#include "Range.h"

Cluster::Cluster(const std::string& name) : name_(name) {}

void Cluster::addHand(int handIndex) {
    handIndices_.push_back(handIndex);
}

void Cluster::getAverageStrategy(const Range& range,
                                float& avgFold,
                                float& avgCheck,
                                float& avgBet) const {
    if (handIndices_.empty()) {
        avgFold = avgCheck = avgBet = 0.0f;
        return;
    }

    float totalFold = 0, totalCheck = 0, totalBet = 0;

    for (int handIndex : handIndices_) {
        float fold, check, bet;
        range.getStrategy(handIndex, fold, check, bet);

        totalFold += fold;
        totalCheck += check;
        totalBet += bet;
    }

    float n = handIndices_.size();
    avgFold = totalFold / n;
    avgCheck = totalCheck / n;
    avgBet = totalBet / n;
}