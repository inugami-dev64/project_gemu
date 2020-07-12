#include "headers/calc.h"
#include "headers/main.h"
#include <math.h>
#include <cmath>
#include <iostream>


//Function that returns time passed from 1st January 1970 00:00:00
long Calc::getTime() {
    std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
    return current_time.time_since_epoch().count() / 1000000;
}

//Function that converts degrees to radians
float Calc::degToRad(int deg) {
    return (2*PI*deg)/360;
}

//Function that calculates location on circle
std::vector<float> Calc::getCircleCoordinates(float circleCentre[2], int angle, int radius) {
    std::vector<float> coordinates(2);
    coordinates[0] = circleCentre[0] + radius * cos(this->degToRad(angle));
    coordinates[1] = circleCentre[1] + radius * sin(this->degToRad(angle));

    return coordinates;
}

//Function that generates random coordinates
std::vector<float> Calc::getNewRandomCoordinates(float x_min, int x_max, float y_min, int y_max, std::vector<float>& prevCoordinates, int x_minDif, int y_minDif, int seedMultiplier) {
    std::vector<float> coordinates;
    coordinates.reserve(2);

    srand(time(NULL)*seedMultiplier);
    if(prevCoordinates[0] - x_minDif > x_min)
        coordinates.push_back(x_min + (rand() % int(prevCoordinates[0] - x_minDif - x_min)));
    else 
        coordinates.push_back(prevCoordinates[0] + x_minDif + (rand() % int(x_max - prevCoordinates[0] - x_minDif)));

    srand(2*time(NULL)*seedMultiplier);
    if(prevCoordinates[1] - y_minDif > y_min)
        coordinates.push_back(y_min + (rand() % int(prevCoordinates[1] - y_minDif - y_min)));
    else 
        coordinates.push_back(prevCoordinates[1] + y_minDif + (rand() % int(y_max - prevCoordinates[1] - y_minDif)));

    return coordinates;
}

//Function that calculates new velocity
std::vector<float> Calc::calcVelocity(std::vector<float>& prevCoordinates, std::vector<float>& newCoordinates, float speed) {
    std::vector<float> velocity;
    //velocity.reserve(2);
    float sinX = (newCoordinates[0] - prevCoordinates[0]) / sqrt(pow((newCoordinates[0] - prevCoordinates[0]), 2) + pow((newCoordinates[1] - prevCoordinates[1]), 2));
    float sinY = (newCoordinates[1] - prevCoordinates[1]) / sqrt(pow((newCoordinates[0] - prevCoordinates[0]), 2) + pow((newCoordinates[1] - prevCoordinates[1]), 2));
    velocity.push_back(sinX*speed);
    velocity.push_back(sinY*speed);

    return velocity;
}