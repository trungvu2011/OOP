#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include"src/event/Event.h"
#include "src/ward/Ward.h"
#include "src/point/Point.h"
#include <vector>
#include "src/personality/Personality.h"
#include "src/emotion/Emotion.h"

class Pedestrian {
public:
    int ID;
    Ward* start;
    Ward* end;
    std::vector<Ward*> journey;
    double velocity;
    Personality personality;
    Emotion emotion;
    std::vector<Event> events;
    double walkingTime;
    double distance;
    double age;
    Event impactOfAGV;
    Point tempPoints;
};


#endif