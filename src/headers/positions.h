#ifndef POSITIONS_H
#define POSITIONS_H
#include "main.h"
#include "gameobjects.h"
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

class Move
{
    public:
        //Function that updates assets
        void setPlayerShooting(Pos& pos);
        void updateBars(Pos& pos, int health, int power);
        void update(Pos& pos, Stats& mainSta);

        //generic movement
        void handleMovement(Pos& pos, float& playerMoveDiagSpeed);
        void genericMove(std::vector<std::vector<float>>& posVec, float x_vel, float y_vel, int index);

        //player movement
        void playerMoveF(Pos& pos);
        void playerMoveFL(Pos& pos, float& playerMoveDiagSpeed);
        void playerMoveFR(Pos& pos, float& playerMoveDiagSpeed);
        void playerMoveB(Pos& pos);
        void playerMoveBL(Pos& pos, float& playerMoveDiagSpeed);
        void playerMoveBR(Pos& pos, float& playerMoveDiagSpeed);
        void playerMoveR(Pos& pos);
        void playerMoveL(Pos& pos);

};

class StagePos {
    public:
        static bool initialised;
        //Level 1 movements
        bool initLvlOneMovement(Pos& pos, Stats& mainSta);

};


#endif