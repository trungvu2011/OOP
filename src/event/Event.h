#ifndef EVENT_H
#define EVENT_H

#include<vector>

class Event {
private:
    double intensity;
    double time;
public:
    void setIntensity();
    double getIntensity() {return intensity;}
    double getTime() {return time;}
};

#endif