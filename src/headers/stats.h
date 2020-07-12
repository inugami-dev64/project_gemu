#ifndef STATS_H
#define STATS_H
#include <vector>

class Stats {

    public:

        //player stats
        int health;
        int power;
        int level;
        int xp;
        int stage;

        //gains from killing enemies or particles
        std::vector<int> powerGains;
        int xpGainFromParticles;

        //enemy stats
        std::vector<int> enemyFullHealth;
        std::vector<std::vector<long>> exploded; //[0] is bool for is exploded? [1] is for explosion stage, [2] is for interval
        std::vector<int> enemyType;
        float particleSpeed;
        float enemySpeed;
        float enemyRotationSpeed; //degrees per frame

        //bool for detecting if enemy has rotated or not
        bool rotation;
        
        std::vector<int> enemyHealth;

    Stats();
};


#endif