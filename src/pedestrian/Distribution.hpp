#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

#include <vector>
#include <string>
#include <iostream>
using namespace std;

std::vector<int> generateTypeOfPedestrian(int, int, int, int);

std::vector<double> generateAge(int, double, double);

double normalDistribution(double, double, double);

double randNormal(double, double);

float randFloat(float, float);

int randInt(int, int);

#endif // DISTRIBUTION_HPP