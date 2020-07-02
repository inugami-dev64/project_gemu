#include "headers/stats.h"

stats::stats() {
    //player stats
    health = 100;
    power = 0;
    level = 0;
    stage = 0;
    xp = 0;

    //gains from killing enemies or particles
    powerGains.reserve(4);
    powerGains.push_back(2); //small
    powerGains.push_back(4); //medium
    powerGains.push_back(8); //big
    powerGains.push_back(50);

    xpGainFromParticles = 4;  

    //enemy stats
    enemyFullHealth.reserve(3);
    enemyFullHealth.push_back(50); //small
    enemyFullHealth.push_back(300); //medium
    enemyFullHealth.push_back(900); //big
    
}