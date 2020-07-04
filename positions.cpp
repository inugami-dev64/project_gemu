#include "headers/positions.h"
#include "headers/stats.h"
#include "headers/levelstaging.h"
#include "headers/main.h"
#include "headers/engine.h"
#include <math.h>
#include <iostream>

Timer posTi;

Pos::Pos() {
    //player
    starship.reserve(2);
    starshipCore.reserve(2);
    ultimate.reserve(2);
    for(int i = 0; i < 2; i++) starshipCore.push_back(0), ultimate.push_back(0);
    starship.push_back(275);
    starship.push_back(550);

    //player stats
    healthBar.reserve(2);
    powerBar.reserve(2);
    healthBar.push_back(647);
    powerBar.push_back(732);

    //ui
    scorePos.reserve(2);
    highScorePos.reserve(2);
    backgroundPos.reserve(2);
    backgroundVelocity.reserve(2);
    menu.reserve(2);
    menuselector.reserve(2);
    deadScreen.reserve(2);
    deadSelector.reserve(2);
    nextSel.reserve(2);
    nostagePos.reserve(2);

    statsPos.push_back(600);
    statsPos.push_back(0);
    highScorePos.push_back(statsPos[0] + 95);
    highScorePos.push_back(562);
    scorePos.push_back(statsPos[0] + 95);
    scorePos.push_back(543);
    backgroundPos.push_back(0);
    backgroundPos.push_back(-5400);
    backgroundVelocity.push_back(0);
    backgroundVelocity.push_back(0.5);
    menu.push_back(250);
    menu.push_back(100);
    menuselector.push_back(296);
    menuselector.push_back(226);
    deadScreen.push_back(200);
    deadScreen.push_back(150);
    deadSelector.push_back(267);
    deadSelector.push_back(354);
    nextSel.push_back(165);
    nextSel.push_back(60);
    nostagePos.push_back(100);
    nostagePos.push_back(200);


}

/****************** Class InitPos functions  *********/

//Variable needed to detect if randomly moving enemies are initialised to avoid weird movement glitches
bool initialised = false;

//Function that initialises player shooting particle locations
void InitPos::initPlayerShooting(Pos& pos) {
    std::vector<float> set(2); 
    set[0] = pos.starship[0] + 7;
    set[1] = pos.starship[1] - 30;
    pos.shootingParticlePos.push_back(set);

    set[0] = pos.starship[0] + 16; 
    set[1] = pos.starship[1] - 30;
    pos.shootingParticlePos.push_back(set);
     
    set[0] = pos.starship[0] + 26; 
    set[1] = pos.starship[1]- 30; 
    pos.shootingParticlePos.push_back(set);

    set[0] = pos.starship[0] + 35; 
    set[1] = pos.starship[1]- 30;
    pos.shootingParticlePos.push_back(set);
}

//Function that updates player
void InitPos::updatePlayer(Pos& pos) {
    for(std::size_t i = 0; i < pos.shootingParticlePos.size(); i++) pos.shootingParticlePos[i][1] -= laserParticleSpeed;
    pos.starshipCore[0] = pos.starship[0] + 13;
    pos.starshipCore[1] = pos.starship[1] + 15;
    pos.ultimate[0] = pos.starship[0] - 25;
    pos.ultimate[1] = pos.starship[1] - 600;
}

//Function that updates particle attack positions
void InitPos::updateAttack(Pos& pos) {
    for(std::size_t i = 0; i < pos.particlePos.size(); i++) {
        //rhomb particles
        pos.particlePos[i][0] += pos.particleVelocity[i][0];
        pos.particlePos[i][1] += pos.particleVelocity[i][1];
        pos.particleCorePos[i][0] += pos.particleVelocity[i][0];
        pos.particleCorePos[i][1] += pos.particleVelocity[i][1];

    }

    for(std::size_t i = 0; i < pos.ballPos.size(); i++) {
        //balls
        pos.ballPos[i][0] += pos.ballVelocity[i][0];
        pos.ballPos[i][1] += pos.ballVelocity[i][1];
        pos.ballCorePos[i][0] += pos.ballVelocity[i][0];
        pos.ballCorePos[i][1] += pos.ballVelocity[i][1];
    }
}

//Function that sets player statsbar Y coordinate
void InitPos::updateBarY(Pos& pos, int health, int power) {
    pos.healthBar[1] = (357 - (3.57 * health)) + 172;
    pos.powerBar[1] = (357 - (3.57 * power)) + 172;
}

//Staging functions

//Function that moves enemy positions L1S0
bool InitPos::initL1S0(Pos& pos) {
    bool moving = false;
    if(pos.enemies[0][0] <= 0) pos.enemies[0][0] += pos.enemyVelocity[0][0], moving = true;
    if(pos.enemies[1][0] <= 50) pos.enemies[1][0] += pos.enemyVelocity[1][0], moving = true;
    if(pos.enemies[2][0] <= 100) pos.enemies[2][0] += pos.enemyVelocity[2][0], moving = true;
    if(pos.enemies[3][0] >= 550) pos.enemies[3][0] += pos.enemyVelocity[3][0], moving = true;
    if(pos.enemies[4][0] >= 500) pos.enemies[4][0] += pos.enemyVelocity[4][0], moving = true;
    if(pos.enemies[5][0] >= 450) pos.enemies[5][0] += pos.enemyVelocity[5][0], moving = true;

    return moving;
}

bool InitPos::initL1S1(Pos& pos) {
    bool moving = false;

    //left side enemies
    
    for(size_t i = 0; i < pos.enemies.size()/2; i++) {
        if(pos.enemies[i][1] <= 300) {
            pos.enemies[i][0] += pos.enemyVelocity[i][0];
            pos.enemies[i][1] += pos.enemyVelocity[i][1];
            if(pos.enemies[i][1] >= -50 && pos.enemyVelocity[i][0] == 0) pos.enemyVelocity[i][0] = (-enemyMoveSpeed)+1;
            moving = true;
        }
        else pos.enemies[i][0] += pos.enemyVelocity[i][0], moving = true;
    }

    //right side enemies
    for(std::size_t i = pos.enemies.size()/2; i < pos.enemies.size(); i++) {
        if(pos.enemies[i][1] <= 300) {
            pos.enemies[i][0] += pos.enemyVelocity[i][0];
            pos.enemies[i][1] += pos.enemyVelocity[i][1];
            if(pos.enemies[i][1] >= -50 && pos.enemyVelocity[i][0] == 0) pos.enemyVelocity[i][0] = enemyMoveSpeed-1;
            moving = true;
        }
        else pos.enemies[i][0] += pos.enemyVelocity[i][0], moving = true;
    }

    return moving;
}

bool InitPos::initL1S2(Pos& pos) {
    const int moveSpeed = enemyMoveSpeed + 2;
    bool moving = false;
    if(pos.enemies[0][0] <= 100 && pos.enemies[0][1] <= 100) pos.enemies[0][0] += pos.enemyVelocity[0][0], pos.enemies[0][1] += pos.enemyVelocity[0][1], moving = true;
    if(pos.enemies[1][1] <= 150) pos.enemies[1][1] += pos.enemyVelocity[1][1], moving = true;
    if(pos.enemies[2][0] >= 450 && pos.enemies[2][1] <= 100) pos.enemies[2][0] += pos.enemyVelocity[2][0], pos.enemies[2][1] += pos.enemyVelocity[2][1], moving = true;

    return moving;
}

bool InitPos::initL1S3(Pos& pos) {
    if(!initialised) {
        bool temp[2] = {false, false};
        if(pos.enemies[0][0] < 100) pos.enemies[0][0] += pos.enemyVelocity[0][0];
        else temp[0] = true;
        
        if(pos.enemies[1][0] > 500) pos.enemies[1][0] += pos.enemyVelocity[1][0];
        else temp[1] = true;

        if(temp[0] && temp[1]) {
            initialised = true;
            return false;
        }
        else return true;

    }

    return false;
}

bool InitPos::updateL1S3(Pos& pos, stats& mainSta) {
    bool moving = false;
    if(mainSta.rotation == false) return moving;
    
    else {
        //if(this->newEnemyPos.size() < 2) this->updateL1S3newPos();

        for(int i = 0; i < pos.newEnemyPos.size(); i++) {
            if(abs(pos.newEnemyPos[i][0] - pos.enemies[i][0]) > abs(pos.enemyVelocity[i][0]) && abs(pos.newEnemyPos[i][1] - pos.enemies[i][1]) > abs(pos.enemyVelocity[i][1])) { 
                pos.enemies[i][0] += pos.enemyVelocity[i][0], moving = true;
                pos.enemies[i][1] += pos.enemyVelocity[i][1], moving = true;
            }

            else moving = false;

        }
    }

    return moving;

}

void InitPos::updateL1S3newPos(Pos& pos) {
    pos.newEnemyPos.clear(), pos.enemyVelocity.clear();
    std::vector<float> temp(2);
    temp.reserve(2);
    int seed = 0;
    float difZ;
    float sinX;
    float sinY;
    
    bool collide = true;

    srand(time(NULL));
    temp[0] = 50 + rand() % 500;
    temp[1] = 50 + rand() % 250;
    pos.newEnemyPos.push_back(temp);
    difZ = sqrt(pow((pos.newEnemyPos[0][0] - pos.enemies[0][0]), 2) + pow((pos.newEnemyPos[0][1] - pos.enemies[0][1]), 2));
    sinX = (pos.newEnemyPos[0][0] - pos.enemies[0][0]) / difZ;
    sinY = (pos.newEnemyPos[0][1] - pos.enemies[0][1]) / difZ;

    temp[0] = sinX * enemyMoveSpeed, temp[1] = sinY * enemyMoveSpeed;
    pos.enemyVelocity.push_back(temp);

    srand(time(NULL) * 2);
    temp[0] = 50 + rand() % 500;
    temp[1] = 50 + rand() % 250;
    pos.newEnemyPos.push_back(temp);
    difZ = sqrt(pow((pos.newEnemyPos[1][0] - pos.enemies[1][0]), 2) + pow((pos.newEnemyPos[1][1] - pos.enemies[1][1]), 2));
    sinX = (pos.newEnemyPos[1][0] - pos.enemies[1][0]) / difZ;
    sinY = (pos.newEnemyPos[1][1] - pos.enemies[1][1]) / difZ;
    temp[0] = sinX * enemyMoveSpeed, temp[1] = sinY * enemyMoveSpeed;
    pos.enemyVelocity.push_back(temp);

}



