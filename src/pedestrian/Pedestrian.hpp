#ifndef PEDESTRIAN_HPP
#define PEDESTRIAN_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

struct Point 
{
    double x, y;
};

class Ward
{
    private:
        string name;
        Point entrance; // Cổng vào khoa viện
        Point exit; // Cổng ra khoa viện
        vector<Point> wallCoordinate; // Các cạnh viền của khoa viện
    public:
        Ward(Point entrance, Point exit, string name, vector<Point> wallCoordinate)
        {
            this->name = name;
            this->entrance = entrance;
            this->exit = exit;
            this->wallCoordinate = wallCoordinate;
        }
        Ward() {}

        string getName() { return name; }
        Point getEntrance() { return entrance; }
        Point getExit() { return exit; }
        vector<Point> getWallCoordinate() { return wallCoordinate; }

        void setName(string name) { this->name = name; }
        void setEntrance(Point entrance) { this->entrance = entrance; }
        void setExit(Point exit) { this->exit = exit; }
        void setWallCoordinate(vector<Point> wallCoordinate) { this->wallCoordinate = wallCoordinate; }
};

enum Walkability
{
    noDisabilityNoOvertaking,
    noDisabilityOvertaking,
    crutches,
    sticks,
    wheelchairs,
    blind
};

class Emotion
{
    private:
        double pleasure;
        double surprise;
        double anger;
        double fear;
        double hate; 
        double sad; 
    public:
        Emotion() : pleasure(0.75), surprise(0.5), anger(-0.2), fear(-0.2), hate(-0.4), sad(-0.4) {}

        // getter methods
        double getPleasure() { return pleasure; }
        double getSurprise() { return surprise; }
        double getAnger() { return anger; }
        double getFear() { return fear; }
        double getHate() { return hate; }
        double getSad() { return sad; }

        // // setter methods
        // void setPleasure(double pleasure) { this->pleasure = pleasure; }
        // void setSurprise(double surprise) { this->surprise = surprise; }
        // void setAnger(double anger) { this->anger = anger; }
        // void setFear(double fear) { this->fear = fear; }
        // void setHate(double hate) { this->hate = hate; }
        // void setSad(double sad) { this->sad = sad; }
};

class Event
{
    private:
        double time; 
        vector<double> intensity;
    public:
        // getter methods
        double getTime() { return time; }
        vector<double> getIntensity() { return intensity; }

        // setter methods
        void setIntensity(vector<double> intensity) { this->intensity = intensity; }
        void setTime(double time) { this->time = time; }
};

class AGVEvent : public Event{};

class Personality
{
    private:
        double lambda; 
        double positiveEmotionThreshold; 
        double negativeEmotionThreshold; 
    public:
        // getter methods
        double getLambda() { return lambda; }
        double getPositiveEmotionThreshold() { return positiveEmotionThreshold; }
        double getNegativeEmotionThreshold() { return negativeEmotionThreshold; }

        // setter methods
        void setLambda(double lambda) { this->lambda = lambda; }
        void setPositiveEmotionThreshold(double positiveEmotionThreshold) { this->positiveEmotionThreshold = positiveEmotionThreshold; }
        void setNegativeEmotionThreshold(double negativeEmotionThreshold) { this->negativeEmotionThreshold = negativeEmotionThreshold; }
};

class Pedestrian
{
    protected:
        int ID; 
        Ward start; 
        Ward end; 
        vector<Ward> journey; 
        double velocity; 
        Personality personality; 
        Emotion emotion = Emotion(); 
        vector<Event> events; 
        double walkingTime; 
        double distance; 
        double age; 
        AGVEvent impactOfAGV; 
        Point tempPoints; 
    public:
        // getter methods
        int getID() { return ID; }
        Ward getStart() { return start; }
        Ward getEnd() { return end; }
        vector<Ward> getJourney() { return journey; }
        double getVelocity() { return velocity; }
        Personality getPersonality() { return personality; }
        Emotion getEmotion() { return emotion; }
        // vector<Event> getEvents() { return events; }
        double getWalkingTime() { return walkingTime; }
        double getDistance() { return distance; }
        double getAge() { return age; }
        AGVEvent getImpactOfAGV() { return impactOfAGV; }
        Point getTempPoints() { return tempPoints; }
        
        // setter methods
        void setID(int ID) { this->ID = ID; }
        void setStart(Ward start) { this->start = start; }
        void setEnd(Ward end) { this->end = end; }
        void setJourney(vector<Ward> journey) { this->journey = journey; }
        void setVelocity(double velocity) { this->velocity = velocity; }
        void setPersonality(Personality personality) { this->personality = personality; }
        void setEmotion(Emotion emotion) { this->emotion = emotion; }
        void setEvents(vector<Event> events) { this->events = events; }
        void setWalkingTime(double walkingTime) { this->walkingTime = walkingTime; }
        void setDistance(double distance) { this->distance = distance; }
        void setAge(double age) { this->age = age; }
        void setImpactOfAGV(AGVEvent impactOfAGV) { this->impactOfAGV = impactOfAGV; }
        void setTempPoints(Point tempPoints) { this->tempPoints = tempPoints; }

        vector<vector<double>> getEvents() 
        {
            vector<vector<double>> allEvents(6, vector<double>(20));
            for (int i = 0; i < 6; ++i) 
            {
                for (int j = 0; j < 20; ++j) 
                {
                    allEvents[i][j] = events[j].getIntensity()[i];
                }
            }
            return allEvents;
        }

        virtual Walkability getWalkability() { return Walkability::noDisabilityNoOvertaking; } 
};

class Patient : public Pedestrian
{
    private:
        Walkability walkability;
    public:
        Walkability getWalkability() { return walkability; }
};

class Visitor: public Pedestrian
{
    private:
        Walkability walkability;
    public:
        Walkability getWalkability() { return walkability; }
};

class Personel: public Pedestrian{};

vector<Ward> generateWard();

void generatePedestrian();

vector<Event> generateEvents();

vector<vector<double>> eventsImpact(Pedestrian p, int timeHorizon);



#endif // PEDESTRIAN_HPP