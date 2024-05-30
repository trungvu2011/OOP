#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP
#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

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

#endif // DISTRIBUTION_HPP