#ifndef POSITIONS_H
#define POSITIONS_H
#include "main.h"
#include "gameobjects.h"
#include "engine.h"
#include <vector>



//position class for all object positions
class Pos
{       
    public:

        //arr[0] is x coordinate
        //arr[1] is y coordinate

        //player
        std::vector<float> starship;
        std::vector<float> starshipCore;
        std::vector<float> ultimate;
        std::vector<std::vector<float>> shootingParticlePos;


        //player stats
        std::vector<float> healthBar;
        std::vector<float> powerBar;


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
        std::vector<std::vector<float>> enemyVelocity;

        //enemies attack
        std::vector<std::vector<float>> ballPos;
        std::vector<std::vector<float>> ballCorePos;
        std::vector<std::vector<float>> ballVelocity;
        std::vector<std::vector<float>> particlePos;
        std::vector<std::vector<float>> particleCorePos;
        std::vector<std::vector<float>> particleVelocity;
        std::vector<std::vector<float>> newEnemyPos;

    Pos();
};

class InitPos
{
    public:
        //Function that updates assets
        void initPlayerShooting(Pos& pos);
        void updateBarY(Pos& pos, int health, int power);
        void updatePlayer(Pos& pos);
        void updateAttack(Pos& pos);

        //level 1 stage 0
        bool initL1S0(Pos& pos);

        //level 1 stage 1
        bool initL1S1(Pos& pos);

        //level 1 stage 2
        bool initL1S2(Pos& pos);

        //level 1 stage 3 
        bool initL1S3(Pos& pos);
        bool updateL1S3(Pos& pos, stats& mainSta);
        void updateL1S3newPos(Pos& pos);
};


#endif