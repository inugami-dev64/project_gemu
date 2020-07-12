#ifndef CALC_H
#define CALC_H
#include <chrono>
#include <vector>

class Calc {
    public:
        //Function that returns time passed from 1st January 1970 00:00:00
        long getTime();
        //Function that converts degrees to radians 
        float degToRad(int deg);
        //Function that calculates point coordinates on circle
        std::vector<float> getCircleCoordinates(float circleCentre[2], int angle, int radius);
        //Function that generates new coordinates
        std::vector<float> getNewRandomCoordinates(float x_min, int x_max, float y_min, int y_max, std::vector<float>& prevCoordinates, int x_minDif, int y_minDif, int seedMultiplier);
        //Function that calculates new velocity
        std::vector<float> calcVelocity(std::vector<float>& prevCoordinates, std::vector<float>& newCoordinates, float speed);
};



#endif