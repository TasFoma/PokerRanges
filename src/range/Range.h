#ifndef RANGE_H
#define RANGE_H

#include <vector>

class Range {
public:
    Range();

    std::vector<float> foldRange;
    std::vector<float> checkRange;
    std::vector<float> betRange;

    void getStrategy(int i, float& fold, float& check, float& bet) const;
    void setStrategy(int i, float fold, float check, float bet);
    void generateRandom();
    bool checkNormalized() const;

    static const int TOTAL_HANDS = 1326;
};

#endif // RANGE_H