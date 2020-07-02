#ifndef POSITIONS_H
#define POSITIONS_H
#include "main.h"
#include "gameobjects.h"
#include "engine.h"
#include <vector>



//position class for all object positions
class Pos
{   
    private:
        void updateL1S3newPos(stats& mainSta);
        
    public:

        //arr[0] is x coordinate
        //arr[1] is y coordinate

        //player
        std::vector<float> starship;
        std::vector<float> starshipCore;
        std::vector<float> ultimate;
        void initPlayerShooting();
        std::vector<std::vector<float>> shootingParticleSet;
        void ultimateSetDefault();


        //player stats
        std::vector<float> healthBar;
        std::vector<float> powerBar;
        void setBarY(int health, int power);


        //ui
        std::vector<float> statsPos;
        std::vector<float> scorePos;
        std::vector<float> highScorePos;
        std::vector<float> backgroundPos;
        std::vector<float> backgroundVelocity;
        std::vector<float> menu;
        std::vector<float> deadScreen;
        std::vector<float> menuselector;
        std::vector<float> deadSelector;
        std::vector<float> nextSel;
        std::vector<float> nostagePos;

        //enemies
        std::vector<std::vector<float>> enemies;

        //enemies attack
        std::vector<std::vector<float>> ballPos;
        std::vector<std::vector<float>> ballCorePos;
        std::vector<std::vector<float>> ballVelocity;
        std::vector<std::vector<float>> particlePos;
        std::vector<std::vector<float>> particleCorePos;
        std::vector<std::vector<float>> particleVelocity;
        std::vector<std::vector<float>> newEnemyPos;

        //Function that updates assets
        void updatePlayer();
        void updateAttack();

        //level 1 stage 0
        bool updateL1S0();

        //level 1 stage 1
        bool updateL1S1();

        //level 1 stage 2
        bool updateL1S2();

        //level 1 stage 3 
        bool initL1S3pos();
        bool updateL1S3(stats& mainSta);


    Pos();
};


#endif