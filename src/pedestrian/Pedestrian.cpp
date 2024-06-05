#include "Pedestrian.hpp"
#include "Distribution.hpp"
#include "../../lib/nlohmann/json.hpp" 
#include "../utility/Utility.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include <unordered_set>

using namespace std;
using json = nlohmann::json;


vector<int> generateTypeOfPedestrian(int num_samples, int total_value, int lower_bound, int upper_bound)
{
    // Calculate mean and standard deviation
    double mean = (lower_bound + upper_bound) / 2;
    double std_dev = (mean - lower_bound) / 3.0;

    // Create random number generator
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std_dev);

    // Generate samples
    vector<int> samples(num_samples);
    for (int i = 0; i < num_samples; i++)
    {
        double number = distribution(gen);
        samples[i] = clamp(static_cast<int>(round(number)), lower_bound, upper_bound);
    }

    // Shuffle samples
    shuffle(samples.begin(), samples.end(), gen);

    // Swap the maximum value with the first element
    auto max_iter = max_element(samples.begin(), samples.end());
    iter_swap(samples.begin(), max_iter);

    // Print sum of sample values
    int sum = accumulate(samples.begin(), samples.end(), 0);
    cout << "Sum of sample values: " << sum << endl;

    return samples;
}

vector<double> generateAge(int n, double minValue, double maxValue)
{
    // Calculate mean and standard deviation
    double mean = (minValue + maxValue) / 2;
    double std_dev = (mean - minValue) / 3.0;

    // Create random number generator
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std_dev);

    // Generate samples
    vector<double> samples(n);
    for (int i = 0; i < n; i++)
    {
        double number = distribution(gen);
        samples[i] = max(minValue, min(maxValue, number));
    }

    // Round the values to one decimal place
    for (int i = 0; i < n; i++)
    {
        samples[i] = round(samples[i] * 10) / 10.0;
    }
    return samples;
}

// normal distribution
double normalDistribution(double x, double mean, double std_dev)
{
    return exp(-0.5 * pow((x - mean) / std_dev, 2)) / (std_dev * sqrt(2 * M_PI));
}

// rand normal distribution
double randNormal(double mean, double std_dev)
{
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(mean, std_dev);
    return distribution(gen);
}

float randFloat(float a, float b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> distribution(a, b);
    return distribution(gen);
}

int randInt(int a, int b)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(a, b);
    return distribution(gen);
}


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

// Excersice 3
vector<Pedestrian> generatePedestrian(int writeToFile) 
{
    json inputData;
    inputData = Utility::readInputData("data/input.json");
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    int numOfPedestrian = inputData["numOfAgents"]["value"];
    float deviationParam = randFloat(1 - (float)inputData["experimentalDeviation"]["value"] / 100, 1 + (float)inputData["experimentalDeviation"]["value"] / 100);
    vector<int> numOfTypePedestrians = generateTypeOfPedestrian(6, numOfPedestrian, 20, 47);
    // generate type of pedestrian
    int numOfStaff = numOfTypePedestrians[0] + numOfTypePedestrians[1] - randInt(1, 20);
    int numOfVisitor = numOfTypePedestrians[0] + numOfTypePedestrians[1] - numOfStaff;
    int numOfPatient = numOfPedestrian - numOfStaff - numOfVisitor;
    int numPedestrians[] = {numOfStaff, numOfVisitor, numOfPatient};
    // age distribution
    vector<double> ages = generateAge(numOfPedestrian, 5, 104);
    vector<double> agesStaff = generateAge(numOfStaff, 23, 61);

    
    // 43 values ~ 43 events
    vector<double> allTimeDistances(43);
    for (int i = 0; i < 43; ++i) 
    {
        allTimeDistances[i] = randInt(1, 19);
    }

    // 
    // personality
    Personality personalityOpen, personalityNeurotic;
    personalityOpen.setLambda(double(inputData["personalityDistribution"]["distribution"]["open"]["lambda"]));
    personalityOpen.setPositiveEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["open"]["positiveEmotionThreshold"]));
    personalityOpen.setNegativeEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["open"]["negativeEmotionThreshold"]));

    personalityNeurotic.setLambda(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["lambda"]));
    personalityNeurotic.setPositiveEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["positiveEmotionThreshold"]));
    personalityNeurotic.setNegativeEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["negativeEmotionThreshold"]));

    // velocity
    double perNoDisabilityNoOvertaking = double(inputData["walkability"]["distribution"]["noDisabilityNoOvertaking"]["velocity"]) * deviationParam;
    double perNoDisabilityOvertaking = double(inputData["walkability"]["distribution"]["noDisabilityOvertaking"]["velocity"]) * deviationParam;
    double perWalkingWithCrutches =  double(inputData["walkability"]["distribution"]["crutches"]["velocity"]) * deviationParam;
    double perWalkingWithSticks =  double(inputData["walkability"]["distribution"]["sticks"]["velocity"]) * deviationParam;
    double perWheelChairs = double(inputData["walkability"]["distribution"]["wheelchairs"]["velocity"]) * deviationParam;
    double perBlind = double(inputData["walkability"]["distribution"]["blind"]["velocity"]) * deviationParam;
    double velocityList[numOfPedestrian];
    for (int i = 0; i < numOfPedestrian; ++i) 
    {
        if (i < numOfTypePedestrians[0]) 
            velocityList[i] = perNoDisabilityNoOvertaking;
        else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1]) 
            velocityList[i] = perNoDisabilityOvertaking;
        else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1] + numOfTypePedestrians[2]) 
            velocityList[i] = perWalkingWithCrutches;
        else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1] + numOfTypePedestrians[2] + numOfTypePedestrians[3]) 
            velocityList[i] = perWalkingWithSticks;
        else if (i < numOfTypePedestrians[0] + numOfTypePedestrians[1] + numOfTypePedestrians[2] + numOfTypePedestrians[3] + numOfTypePedestrians[4]) 
            velocityList[i] = perWheelChairs;
        else 
            velocityList[i] = perBlind;
    }

    // ward
    vector<Ward> wards = generateWard();
    int ID = -1;
    for (int i = 0; i < 3; ++i) 
    {
        for (int j = 0; j < numPedestrians[i]; ++j)
        {
            ID++;
            switch (i) 
            {
            case 0:
                {
                    Personel personel;
                    vector<Event> events;
                    personel.setID("s" + to_string(ID + 1));
                    personel.setAge(agesStaff[ID]);
                    personel.setStart(wards[ID % 9]);
                    personel.setEnd(wards[ID % 9]);
                    personel.setPersonality(personalityOpen);
                    personel.setVelocity(velocityList[ID]);
                    for (int i = 0; i < 20; ++i) 
                    {
                        int x = randInt(0, 42);
                        Event event = allEvents[x];
                        if (i == 0) 
                            event.setTime(allTimeDistances[x]);
                        else    
                            event.setTime(allTimeDistances[x] + events[i - 1].getTime());
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
                    visitor.setID("v" + to_string(ID + 1));
                    visitor.setAge(ages[ID]);
                    visitor.setStart(wards[9]);
                    visitor.setEnd(wards[9]);
                    visitor.setPersonality(ID > 100 ? personalityNeurotic : personalityOpen);
                    visitor.setVelocity(velocityList[ID]);
                    for (int i = 0; i < 20; ++i) 
                    {
                        int x = randInt(0, 42);
                        Event event = allEvents[x];
                        if (i == 0) 
                            event.setTime(allTimeDistances[x]);
                        else    
                            event.setTime(allTimeDistances[x] + events[i - 1].getTime());
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
                    patient.setID("p" + to_string(ID + 1));
                    patient.setAge(ages[ID]);
                    patient.setStart(wards[9]);
                    patient.setEnd(wards[9]);
                    patient.setPersonality(personalityNeurotic);
                    patient.setVelocity(velocityList[ID]);
                    for (int i = 0; i < 20; ++i) 
                    {
                        int x = randInt(0, 42);
                        Event event = allEvents[x];
                        if (i == 0) 
                            event.setTime(allTimeDistances[x]);
                        else    
                            event.setTime(allTimeDistances[x] + events[i - 1].getTime());
                        events.push_back(event);
                    }
                    patient.setEvents(events);
                    pedestrians.push_back(patient);
                    break;
                }
            }
        }
    }

    if (writeToFile == 1) 
    {
        // Write result on file
        ofstream outFile("data/pedestrian.txt", ios::app);
        if (!outFile.is_open()) 
        {
            cout << "Can't open file\n";
            return pedestrians;
        }
        for (auto& pedestrian : pedestrians)
        {
            json jsonObject;
            jsonObject["ID"] = pedestrian.getID();
            jsonObject["age"] = pedestrian.getAge();
            jsonObject["velocity"] = pedestrian.getVelocity();
            // jsonObject["emotion"]["lambda"] = pedestrian.getPersonality().getLambda();
            // jsonObject["emotion"]["surprise"] = pedestrian.getEmotion().getSurprise();
            // jsonObject["emotion"]["anger"] = pedestrian.getEmotion().getAnger();
            // jsonObject["emotion"]["fear"] = pedestrian.getEmotion().getFear();
            // jsonObject["emotion"]["hate"] = pedestrian.getEmotion().getHate();
            // jsonObject["emotion"]["sad"] = pedestrian.getEmotion().getSad();
            jsonObject["age"] = pedestrian.getAge();
            jsonObject["start ward"] = pedestrian.getStart().getName();
            jsonObject["end ward"] = pedestrian.getEnd().getName();
            jsonObject["personality"]["name"] = pedestrian.getPersonality().getLambda() == 1 ? "open" : "neurotic";
            // jsonObject["personality"]["lamda"] = pedestrian.getPersonality().getLambda();
            // jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
            // jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
            jsonObject["events"] = pedestrian.getEvents();
            jsonObject["eventsTime"] = pedestrian.getEventsTime();
            outFile << jsonObject << endl;
        }
        outFile.close();
        cout << "Write file successfully\n";
    }
    return pedestrians;
}

// Excersice 4
// triple - số đối tượng phải đi qua 3 khoa viên
// single - số đối tượng phải đi qua 1 khoa viện
vector<pair<Ward, int>> ex4(vector<Ward>& input, int triple, int single) 
{
    vector<pair<Ward, int>> result;
    json inputData = Utility::readInputData("data/input.json");

    int numOfAgents = inputData["numOfAgents"]["value"];

    // Tổng số lượng người
    int sum = triple + single;
    // Kiểm tra dữ liệu
    if (sum != numOfAgents) 
    {
        cerr << "Dữ liệu không khớp với số lượng người trong bệnh viện." << endl;
        return result;
    }

    // Số lượng khoa viện
    int sLuongWard = input.size();
    // Tổng số lượt đi qua các khoa viện
    int total_value = triple * 3 + single;
    int min_value = 0;
    int mean = total_value / sLuongWard; // Số lượng lượt đi qua trung bình của mỗi khoa viện
    double std = 3; // độ lệch chuẩn

    // Số lượt đi qua của từng khoa viện
    vector<int> number;
    bool test = true; // trạng thái lặp
    while (test)
    {
        // Xóa hết các giá trị không thỏa mãn
        number.clear();
        for (int i = 0; i < sLuongWard; i++) 
        {
            int a = static_cast<int>(randNormal(mean, std));
            number.push_back(a);
        }

        // Tính tổng số lượt đi qua các khoa viện
        int sum = 0;
        for (int num : number) 
        {
            sum += num;
        }

        // Kiểm tra tổng số lượt đi qua các khoa viện
        if (sum == total_value) 
        {
            test = false;
        }
    }

    // Thiết lập khoa tương ứng số lượt đi qua
    for (int i = 0; i < sLuongWard; i++) 
    {
        result.push_back(make_pair(input[i], number[i]));
    }

    return result;
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

// Excersice 7

vector<vector<double>> getImpact(int numOfSamples, int numOfValues, double minValue, double maxValue) 
{
    vector<vector<double>> impacts(6, vector<double>(numOfValues));

    random_device rd;
    mt19937 gen(rd());
    double mean = (minValue + maxValue) / 2;
    double std = (maxValue - mean) / 3;
    uniform_real_distribution<double> dis(minValue, maxValue);
    normal_distribution<double> dist(mean, std);

    for (auto& emotion : impacts) {
        generate(emotion.begin(), emotion.end(), [&]() {
            double value = dist(gen);
            return max(minValue, min(value, maxValue)); // Clamp values to range [minValue, maxValue]
        });
    }
    return impacts;
}

bool isChild(Pedestrian p) 
{
    return p.getAge() < 12;
}

int countYoungerThan12(vector<Pedestrian>& allPedestrians) 
{
    int count = 0;
    for (auto& pedestrian : allPedestrians) 
    {
        if (isChild(pedestrian))
        {
            count++;
        }
    }
    return count;
}

bool isALKW(Pedestrian p) 
{
    string name = p.getStart().getName();
    return name == "A" || name == "L" || name == "K" || name == "W";
}

int countALKW(vector<Pedestrian> allPedestrians) 
{
    int count = 0;
    for (auto& pedestrian : allPedestrians) 
    {   
        if (isALKW(pedestrian))  
        {
            count++;
        }
    }
    return count;
}

bool isBFGMEN(Pedestrian p) 
{
    string name = p.getStart().getName();
    return name == "B" || name == "F" || name == "G" || name == "M" || name == "E" || name == "N";
}

int countBFGMEN(vector<Pedestrian> allPedestrians) 
{
    int count = 0;
    for (auto& pedestrian : allPedestrians) 
    {
        if (isBFGMEN(pedestrian)) 
        {
            count++;
        }
    }
    return count;
}

bool isElder(Pedestrian p) 
{
    return p.getAge() > 60;
}

int countOlderThan60(vector<Pedestrian> allPedestrians) 
{
    int count = 0;
    for (auto& pedestrian : allPedestrians) 
    {
        if (isElder(pedestrian)) 
        {
            count++;
        }
    }
    return count;
}

bool isBlinder(Pedestrian p) 
{
    return p.getWalkability() == blind;
}

int countBlinder(vector<Pedestrian> allPedestrians)
{
    int count = 0;
    for (auto& pedestrian : allPedestrians) 
    {
        if (isBlinder(pedestrian)) 
        {
            count++;
        }
    }
    return count;
}

vector<vector<double>> assignAGVImpacts(vector<Pedestrian> allPedestrians) 
{
    int nChildren = countYoungerThan12(allPedestrians);
    vector<vector<double>> impactToChildren = getImpact(nChildren, 100, 0.01, 0.99);
    for (auto& row : impactToChildren) {
        for (auto& val : row) {
            val *= -1;
        }
    }

    int nPersonnelOfALKW = countALKW(allPedestrians);
    vector<vector<double>> impactToALKW = getImpact(nPersonnelOfALKW, 100, -0.29, 0.99);
    for (auto& row : impactToALKW) {
        for (auto& val : row) {
            val *= -1;
        }
    }

    int nPersonnelOfBFGMEN = countBFGMEN(allPedestrians);
    vector<vector<double>> impactToBFGMEN = getImpact(nPersonnelOfBFGMEN, 100, -0.29, 0.99);
    for (auto& row : impactToBFGMEN) {
        for (auto& val : row) {
            val *= -1;
        }
    }

    int nElder = countOlderThan60(allPedestrians);
    vector<vector<double>> impactToElder = getImpact(nElder, 100, -0.29, 0.99);
    for (auto& row : impactToBFGMEN) {
        for (auto& val : row) {
            val *= -1;
        }
    }

    int nBlinder = countBlinder(allPedestrians);
    vector<vector<double>> impactToBlinder = getImpact(nBlinder, 100, -0.29, 0.99);
    for (auto& row : impactToBlinder) {
        for (auto& val : row) {
            val *= -1;
        }
    }

    int nOthers = allPedestrians.size() - (nChildren + nPersonnelOfALKW + nPersonnelOfBFGMEN + nElder + nBlinder);
    vector<vector<double>> impactToOthers = getImpact(nOthers, 100, -0.69, 0.99);

    vector<vector<double>> impactOfAGV(allPedestrians.size(), vector<double>(6, 0));
    for (int i = 0; i < allPedestrians.size(); ++i)
    {   
        auto& person = allPedestrians[i];
        vector<vector<int>> impactOfAGV(6, vector<int>(1, 0));
        if (isChild(person)) 
        {
            for (int j = 0; j < 6; ++j)
                impactOfAGV[i][j] += impactToChildren[i][j];
        }
        else if (isALKW(person)) 
        {
            for (int j = 0; j < 6; ++j)
                impactOfAGV[i][j] += impactToALKW[i][j];
        }
        else if (isBFGMEN(person)) 
        {
            for (int j = 0; j < 6; ++j)
                impactOfAGV[i][j] += impactToBFGMEN[i][j];
        }
        else if (isElder(person)) 
        {
            for (int j = 0; j < 6; ++j)
                impactOfAGV[i][j] += impactToElder[i][j];
        }
        else if (isBlinder(person)) 
        {
            for (int j = 0; j < 6; ++j)
                impactOfAGV[i][j] += impactToBlinder[i][j];
        }
        else 
        {
            for (int j = 0; j < 6; ++j)
                impactOfAGV[i][j] += impactToOthers[i][j];
        }
    }
    return impactOfAGV;
}

// Excersice 8
void leavingDistribution(string name) 
{
    cerr << "leaving Distribution\n";
    int totalValue = 0;
    json inputData;
    inputData = Utility::readInputData("data/input.json");
    string start = inputData["leavingDistribution"]["distribution"][name]["normal"]["start"];
    int startTime = stoi(start);
    string end = inputData["leavingDistribution"]["distribution"][name]["normal"]["end"];
    int endTime = stoi(end);
    string time_step = inputData["leavingDistribution"]["distribution"][name]["normal"]["timeStep"];
    int timeStep = stoi(time_step);
    int stdDev = inputData["leavingDistribution"]["distribution"][name]["normal"]["std_dev"];
    vector<Pedestrian> pedestrians = generatePedestrian(0);
    for (auto& pedestrian : pedestrians)
    {
        if (pedestrian.getEnd().getName() == name) 
        {
            totalValue++;
        }
    }
    double numOfValue = (double)(endTime - startTime + 1) / timeStep;
    double meanValue = (double)totalValue / numOfValue;
    for (int i = startTime; i <= 10; i += 2) 
    {
        double numLeavers = normalDistribution(i, meanValue, stdDev) * totalValue;
        cout << "Time " << i << ": " << numLeavers << " people leaving from ward " << name << endl;
    }
}



