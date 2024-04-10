#ifndef EVENT_H
#define EVENT_H

#include<vector>

class Event {
private:
    std::vector<std::vector<double>> intensity;
    double time;
public:
    void setIntensity(const std::vector<std::vector<double>>& newIntensity) {
        intensity = newIntensity;
    }
    double getTime() {return time;}
};

#endif