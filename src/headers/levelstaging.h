#ifndef LEVELSTAGING_H
#define LEVELSTAGING_H
#include "calc.h"
#include "engine.h"
#include "positions.h"
#include <vector>


//vector pushing functions
class ManageVectors {
    public:
        void pushEnemies(Stats& mainSta, std::vector<sf::Sprite>& enemyVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, sf::Sprite& enemy, std::vector<float>& positions, std::vector<float>& velocity, int type, Calc& calc);
        void clearStage(Pos& pos, Obj& obj, Stats& mainSta);
        void clearParticles(Pos& pos, Obj& obj);
        void cleanAssets(bool cleanEnemies, Pos& pos, Obj& obj, Stats& mainSta);

};

class LevelOne {
    public:
        //Function that handles attack
        void handleLvlAttack(Obj& obj, Stats& mainSta, Pos& pos, long& generationInterval, std::size_t& generationIndex, StagePos& initPos, Calc& calc);
        //Function that initialises enemies
        void initLvl(Obj& obj, Stats& mainSta, Pos& pos, Calc& calc);
        //Function that handles staging
        void handleLvl(Obj& obj, Stats& mainSta, Pos& pos, Calc& calc, StagePos& stagePos, long& generationInterval, long& stageInterval , std::size_t& index);
        //Function that draws frame for stage
        void drawStage(Pos& pos, Obj& obj, Stats& mainSta, StagePos& stagePos, Calc& calc, long& stageInterval, long& generationInterval, std::size_t& generationIndex, bool cleanEnemiesOutFrame);
};

class Levels {
    public:
        LevelOne lvlOne;
};

class Attack {
    private:
        //particle pushing to vectors
        void pushAttack(std::vector<sf::Sprite>& particleVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, sf::Sprite& particle, std::vector<float>& positions, std::vector<float>& velocity);
        void pushCore(std::vector<float>& positions, int type, Pos& pos, Obj& obj);

        //vector initialsations
        void initVecPtr(std::vector<std::vector<float>>* posVecPtr, std::vector<sf::Sprite>* particleVecPtr, std::vector<std::vector<float>>* velVecPtr, std::vector<std::vector<float>>* corePosVecPtr);

    public:
        //Function that shoots two particles down
        //type 1 is ball, type 2 is rhomb
        void basicDualAttackDown(std::size_t& enemyIndex, Pos& pos, Obj& obj, int particleType, sf::Sprite& particle);
        void circularAttack(std::size_t enemyIndex, Pos& pos, Obj& obj, Stats& mainSta, int particleType, int frequency, int startRadius, sf::Sprite& particle, Calc& calc);
        void flowerAttack(std::size_t enemyIndex, Pos& pos, Obj& obj, Stats& mainSta, int startRadius, int frequency, sf::Sprite& ball, Calc& calc);

        class Pointers {
            public:
                //Function that gets all pointer values
                void getPointers(int type, Pos& pos, Obj& obj);
                std::vector<std::vector<float>>* posVecPtr;
                std::vector<sf::Sprite>* particleVecPtr;
                std::vector<std::vector<float>>* velVecPtr;
                std::vector<std::vector<float>>* corePosVecPtr;
        };
};



#endif