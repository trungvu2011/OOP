#include "Event.h"

using namespace std;

void Event::setIntensity() {
    std::system("python3 data/allEventCreate/main.py > data/allEventCreate/output.txt");

    std::ifstream file("data/allEventCreate/output.txt");
    std::string line;
    std::vector<std::vector<double>> newIntensity;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<double> row;
        double value;

        while (iss >> value) {
            row.push_back(value);
        }

        newIntensity.push_back(row);
    }

    setIntensity(newIntensity);
}