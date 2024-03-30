#ifndef EVENT_H
#define EVENT_H

class Event {
private:
    double intensity;
    double time;
public:
    void setEvent(double intensity, double time);
    double getIntensity() {return intensity;}
    double getTime() {return time;}
};

#endif