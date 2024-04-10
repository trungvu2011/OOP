#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include"src/event/Event.h"
#include "src/ward/Ward.h"
#include "src/point/Point.h"
#include <vector>
#include "src/personality/Personality.h"
#include "src/emotion/Emotion.h"

class Pedestrian {
private:
    int ID;
    Ward* start;
    Ward* end;
    std::vector<Ward> journey;
    double velocity;
    Personality personality;
    Emotion emotion;
    std::vector<Event> events;
    double walkingTime;
    double distance;
    double age;
    Event impactOfAGV;
    Point tempPoints;
public:
    int getID() {return ID;}
    Ward* getStart() {return start;}
    Ward* getEnd() {return end;}
    std::vector<Ward> getJourney() {return journey;}
    double getVelocity() {return velocity;}
    Personality getPersonality() {return personality;}
    Emotion getEmotion() {return emotion;}
    std::vector<Event> getEvent() {return events;}
    double getWalkingTime() {return walkingTime;}
    double getDistance() {return distance;}
    double getAge() {return age;}
    Event getImpactOfAGV() {return impactOfAGV;}
    Point getTempPoints() {return tempPoints;}

};


#endif