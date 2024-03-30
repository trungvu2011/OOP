#include "Personality.h"

using namespace std;

void Personality::setPersonality(double lamb, double pos, double neg) {
    this->lambda = lamb;
    this->positiveEmotionThreshold = pos;
    this->negativeEmotionThreshold = neg;
}