#include "Pedestrian.hpp"
#include "../../lib/nlohmann/json.hpp" 
#include "../utility/Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>

using namespace std;
using json = nlohmann::json;

vector<Ward> generateWard()
{
    vector<Ward> wards;
    ifstream file("data/hospital.txt");
    string line;
    if (file.is_open()) 
    {
        while (getline(file, line))
        {
            vector<Point> wall;
            Point midPoint1, midPoint2, point1, point2, point3, point4;
            double length;
            string name;
            istringstream iss(line);
            iss >> midPoint1.x >> midPoint1.y;
            iss >> midPoint2.x >> midPoint2.y;
            iss >> length;
            iss >> name;
            point1.x = midPoint1.x - length / 2;
            point1.y = midPoint1.y;
            point2.x = midPoint1.x + length / 2;
            point2.y = midPoint1.y;
            point3.x = midPoint2.x - length / 2;
            point3.y = midPoint2.y;
            point4.x = midPoint2.x + length / 2;
            point4.y = midPoint2.y;
            wall.push_back(point1);
            wall.push_back(point2);
            wall.push_back(point3);
            wall.push_back(point4);
            wards.push_back(Ward(midPoint1, midPoint2, name, wall));
            cout << wards.size() << endl;
        }
        file.close();
    }
    else 
    {
        cout << "Can't open file\n";
    }
    return wards;
}

vector<Event> generateEvents() 
{
    vector<Event> events;
    ifstream file("data/event_distribution.txt");
    string line;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            Event event;
            istringstream iss(line);
            double value;
            vector<double> intensity;
            while (iss >> value) 
            {
                intensity.push_back(value);
            }
            event.setIntensity(intensity);
            event.setTime(0);
            events.push_back(event);
        }
        file.close();
    }
    else 
    {
        cout << "Can't open file\n";
    }
    return events;
}

float randomFloat(float lower, float upper)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(lower, upper);
    return dis(gen);
}

int randomInt(int lower, int upper)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(lower, upper);
    return dis(gen);
}

// Excersice 3
void generatePedestrian() 
{
    json inputData;
    inputData = Utility::readInputData("data/input.json");
    float deviationParam = randomFloat(1 - (float)inputData["experimentalDeviation"]["value"] / 100, 1 + (float)inputData["experimentalDeviation"]["value"] / 100);
    // age distribution
    double ages[] = {66.7, 45.2, 19.9, 41.8, 80.6, 74.7, 44.6, 52.7, 48.1, 52.6, 80.8, 62.7, 62.2, 
                    38.6, 72.2, 73.4, 42.9, 44.9, 46.0, 60.9, 36.4, 44.9, 31.4, 57.7, 22.5, 44.0, 
                    46.3, 44.3, 37.2, 31.7, 64.6, 67.8, 38.4, 98.1, 49.5, 39.6, 55.7, 45.7, 45.3, 
                    49.8, 64.3, 77.8, 68.2, 98.3, 75.6, 64.3, 66.9, 31.2, 63.8, 66.1, 64.7, 56.8, 
                    67.8, 83.6, 75.5, 75.6, 48.5, 56.1, 51.5, 28.6, 77.8, 75.6, 53.7, 54.9, 20.1, 
                    60.8, 56.0, 42.2, 48.0, 55.1, 52.0, 58.8, 72.7, 56.2, 39.7, 55.6, 56.2, 67.3, 
                    51.7, 80.5, 48.2, 67.3, 84.2, 74.3, 59.4, 76.7, 70.3, 30.8, 51.3, 32.4, 14.4, 
                    53.8, 66.6, 57.2, 23.8, 44.0, 83.4, 63.7, 30.5, 58.4, 50.6, 71.1, 68.0, 67.6, 
                    38.3, 48.5, 71.9, 55.2, 82.9, 44.3, 9.9, 34.4, 86.6, 65.9, 67.3, 49.4, 57.9, 
                    53.7, 63.1, 44.4, 45.1, 62.5, 37.7, 41.3, 59.1, 69.5, 60.2, 77.5, 82.7, 53.2, 
                    50.9, 54.2, 47.9, 46.8, 57.7, 47.6, 44.6, 70.5, 62.3, 40.9, 46.6, 60.8, 59.3, 
                    39.2, 58.0, 38.0, 71.6, 72.1, 16.6, 71.5, 30.9, 71.6, 35.0, 79.4, 37.3, 40.9, 
                    78.4, 36.4, 49.9, 44.1, 51.9, 62.8, 48.6, 47.7, 75.7, 62.2, 72.9, 54.7, 52.6, 
                    31.9, 53.7, 49.0, 88.9, 65.3, 49.9, 73.5, 42.1, 72.4, 42.7, 56.2, 67.4, 59.1, 
                    43.3, 71.2, 83.7, 60.8, 59.6, 75.4, 61.0, 78.7, 26.4, 67.0, 31.0, 41.7, 71.2, 
                    69.2, 70.0, 65.8, 51.6, 74.5};
    int numPedestrians[] = {80, 53, 67};
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    // 43 values ~ 43 events
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 43);
    vector<double> allTimeDistances(43);
    for (int i = 0; i < 43; ++i) 
    {
        allTimeDistances[i] = dis(gen);
    }

    int ID = -1;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < numPedestrians[i]; ++j) 
        {
            ID++;
            // personality
            Personality personalityOpen, personalityNeurotic;
            personalityOpen.setLambda(double(inputData["personalityDistribution"]["distribution"]["open"]["lambda"]));
            personalityOpen.setPositiveEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["open"]["positiveEmotionThreshold"]));
            personalityOpen.setNegativeEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["open"]["negativeEmotionThreshold"]));

            personalityNeurotic.setLambda(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["lambda"]));
            personalityNeurotic.setPositiveEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["positiveEmotionThreshold"]));
            personalityNeurotic.setNegativeEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["negativeEmotionThreshold"]));

            // velocity
            double perNoDisabilityNoOvertaking = double(inputData["walkability"]["distribution"]["noDistributionNoOvertaking"]["velocity"]) * deviationParam;
            double perNoDisabilityOvertaking = double(inputData["walkability"]["distribution"]["noDistributionOvertaking"]["velocity"]) * deviationParam;
            double perWalkingWithCrutches =  double(inputData["walkability"]["distribution"]["crutches"]["velocity"]) * deviationParam;
            double perWalkingWithSticks =  double(inputData["walkability"]["distribution"]["sticks"]["velocity"]) * deviationParam;
            double perWheelChairs = double(inputData["walkability"]["distribution"]["wheelchairs"]["velocity"]) * deviationParam;
            double perBlind = double(inputData["walkability"]["distribution"]["blind"]["velocity"]) * deviationParam;
            
            switch (i)
            {
                case 0:
                {
                    Personel personel;
                    vector<Event> events;
                    personel.setID(ID + 1);
                    personel.setAge(ages[ID]);
                    personel.setPersonality(personalityOpen);
                    personel.setVelocity(ID < 47 ? perNoDisabilityNoOvertaking : perNoDisabilityOvertaking);
                    for (int k = 0; k < 20; ++k) 
                    {
                        int x = randomInt(0, 42);
                        Event event = allEvents[x];
                        event.setTime(allTimeDistances[x]);
                        events.push_back(event);
                    }
                    personel.setEvents(events);
                    pedestrians.push_back(personel);
                    break;
                }
                case 1: 
                {
                    Visitor visitor;
                    vector<Event> events;
                    visitor.setID(ID + 1);
                    visitor.setAge(ages[ID]);
                    visitor.setPersonality(ID > 100 ? personalityNeurotic : personalityOpen);
                    visitor.setVelocity(ID < 122 ? (ID < 85 ? perNoDisabilityOvertaking : perWalkingWithCrutches) : perWalkingWithSticks);
                    for (int k = 0; k < 20; ++k) 
                    {
                        int x = randomInt(0, 42);
                        Event event = allEvents[x];
                        event.setTime(allTimeDistances[x]);
                        events.push_back(event);
                    }
                    visitor.setEvents(events);
                    pedestrians.push_back(visitor);
                    break;
                }
                case 2:
                {
                    Patient patient;
                    vector<Event> events;
                    patient.setID(ID + 1);
                    patient.setAge(ages[ID]);
                    patient.setPersonality(personalityNeurotic);
                    patient.setVelocity(ID > 148 ? (ID > 173 ? perBlind : perWheelChairs) : perWalkingWithSticks);
                    for (int k = 0; k < 20; ++k) 
                    {
                        int x = randomInt(0, 42);
                        Event event = allEvents[x];
                        event.setTime(allTimeDistances[x]);
                        events.push_back(event);
                    }
                    patient.setEvents(events);
                    pedestrians.push_back(patient);
                    break;
                }  
            }   
        }
    }
    // Write result on file
    ofstream outFile("data/pedestrian.txt", ios::app);
    if (!outFile.is_open()) 
    {
        cout << "Can't open file\n";
        return;
    }
    for (auto& pedestrian : pedestrians)
    {
        json jsonObject;
        jsonObject["ID"] = pedestrian.getID();
        jsonObject["age"] = pedestrian.getAge();
        jsonObject["velocity"] = pedestrian.getVelocity();
        jsonObject["emotion"]["lambda"] = pedestrian.getPersonality().getLambda();
        jsonObject["emotion"]["surprise"] = pedestrian.getEmotion().getSurprise();
        jsonObject["emotion"]["anger"] = pedestrian.getEmotion().getAnger();
        jsonObject["emotion"]["fear"] = pedestrian.getEmotion().getFear();
        jsonObject["emotion"]["hate"] = pedestrian.getEmotion().getHate();
        jsonObject["emotion"]["sad"] = pedestrian.getEmotion().getSad();
        jsonObject["age"] = pedestrian.getAge();
        jsonObject["personality"]["name"] = pedestrian.getPersonality().getLambda() == 1 ? "open" : "neurotic";
        jsonObject["personality"]["lamda"] = pedestrian.getPersonality().getLambda();
        jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
        jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
        jsonObject["events"] = pedestrian.getEvents();
        outFile << jsonObject.dump() << endl;
    }
    outFile.close();
    cout << "Write file successfully\n";
    return;
}

// Excersice 6
vector<vector<double>> eventsImpact(Pedestrian p, int timeHorizon)
{
    int lastTime = 0, index = 0;
    vector<double> temp(6, 0.0);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(4, 10);
    vector<int> times(19);
    for (int i = 0; i < 19; ++i) 
    {
        times[i] = dis(gen);
    }
    vector<vector<double>> events = p.getEvents();
    double lambda = p.getPersonality().getLambda();
    vector<vector<double>> allEmotions = {
        {p.getEmotion().getPleasure()},
        {p.getEmotion().getSurprise()},
        {p.getEmotion().getAnger()},
        {p.getEmotion().getFear()},
        {p.getEmotion().getHate()},
        {p.getEmotion().getSad()}
        };
    for (int i = 0; i < 6; ++i) 
    {
        allEmotions[i].push_back(events[i][0] + allEmotions[i][0] * exp(-lambda) + allEmotions[i][0]);
        cout<<"allEmotions["<<i<<"][0]="<<allEmotions[i][0]<<", events[" << i << "][0]=" << events[i][0] <<endl;
    }
    for (int time : times) 
    {
        cout << time << ' ';
    }
    cout << endl;
    for (int i = 2; i < 20; ++i) 
    {
        for (int j = 0; j < 6; ++j)
        {
            temp[j] = allEmotions[j][i];
        }
        if (i - lastTime == times[index])
        {
            index++;
            lastTime = i;
            for (int j = 0; j < 6; ++j) 
            {
                temp[j] += allEmotions[j][i] * exp(-lambda) + events[j][index];
            }
        }
        for (int j = 0; j < 6; ++j) 
        {
            allEmotions[j].push_back(temp[j]);
        }
    }

    return allEmotions;
}
