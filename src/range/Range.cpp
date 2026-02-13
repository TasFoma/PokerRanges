#include "Range.h"
#include <cmath>
#include <iostream>
#include <random>

Range::Range() {
    foldRange.resize(TOTAL_HANDS);
    checkRange.resize(TOTAL_HANDS);
    betRange.resize(TOTAL_HANDS);
}

void Range::getStrategy(int i, float& fold, float& check, float& bet) const {
    fold = foldRange[i];
    check = checkRange[i];
    bet = betRange[i];
}

void Range::setStrategy(int i, float fold, float check, float bet) {
    float sum = fold + check + bet;

    if (sum > 0) {
        foldRange[i] = fold / sum;
        checkRange[i] = check / sum;
        betRange[i] = bet / sum;
    } else {
        foldRange[i] = checkRange[i] = betRange[i] = 1.0f / 3.0f;
    }
}

void Range::generateRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);

    for (int i = 0; i < TOTAL_HANDS; i++) {
        float f = dist(gen);
        float c = dist(gen);
        float b = dist(gen);

        setStrategy(i, f, c, b);
    }

    checkNormalized();
}

bool Range::checkNormalized() const {
    const float EPSILON = 0.001f;

    for (int i = 0; i < TOTAL_HANDS; i++) {
        float sum = foldRange[i] + checkRange[i] + betRange[i];

        if (std::abs(sum - 1.0f) > EPSILON) {
            std::cout << "EROR CHECK sum = " << sum  << "i = " << i  << "\n";
            return false;
        }
    }
    return true;
}
