#ifndef LEVELSTAGING_H
#define LEVELSTAGING_H
#include "timer.h"
#include "positions.h"
#include <vector>



class Stage {
    public:
        //matematical functions
        float degToRad(int deg);
        std::vector<float> getCircleCoordinates(float circleCentre[2], int angle, int radius);

        //vector pushing functions
        void pushEnemies(stats& mainSta, std::vector<sf::Sprite>& enemyVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, sf::Sprite& enemy, std::vector<float>& positions, std::vector<float>& velocity, int type);
        void pushAttack(std::vector<sf::Sprite>& particleVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, stats& mainSta, sf::Sprite& particle, std::vector<float>& positions, std::vector<float>& velocity);
        void pushRecCore(std::vector<sf::RectangleShape>& coreVec, std::vector<std::vector<float>>& posVec, sf::RectangleShape& core, std::vector<float>& positions);
        void pushCirCore(std::vector<sf::CircleShape>& coreVec, std::vector<std::vector<float>>& posVec, sf::CircleShape& core, std::vector<float>& positions);

        //level 1 stage 0
        void initL1S0(Obj& obj, stats& mainSta, Pos& pos);
        void L1S0attack(stats& mainSta, Obj& obj, Pos& pos, long& generationInterval, std::size_t& index);

        //level 1 stage 1
        void initL1S1(Obj& obj, stats& mainSta, Pos& pos);
        void L1S1attack(stats& mainSta, Obj& obj, Pos& pos, long& generationInterval);

        //level 1 stage 2
        void initL1S2(Obj& obj, stats& mainSta, Pos& pos);
        void L1S2attack(Obj& obj, stats& mainSta, Pos& pos, long& generationInterval, std::size_t& generationIndex);

        //level 1 stage 3
        void initL1S3(Obj& obj, stats& mainSta, Pos& pos);
        void L1S3attack(Obj& obj, stats& mainSta, Pos& pos, long& generationInterval, std::size_t& index, InitPos& initPos);
};


#endif