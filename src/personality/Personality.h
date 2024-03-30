#ifndef PERSONALITY_H
#define PERSONALITY_H

class Personality 
{
private:
    double lambda;
    double positiveEmotionThreshold;
    double negativeEmotionThreshold;
public:
    void setPersonality(double lam, double pos, double neg);
    double getLambda() {return lambda;}
    double getPositiveEmotionThreshold() {return positiveEmotionThreshold;}
    double getNegativeEmotionThreshold() {return negativeEmotionThreshold;}
};

#endif