#include "headers/positions.h"
#include "headers/stats.h"
#include "headers/levelstaging.h"
#include "headers/main.h"
#include "headers/engine.h"
#include <math.h>
#include <iostream>

Timer posTi;

//Function that initialises player shooting particle locations
void Pos::initPlayerShooting() {
    std::vector<float> set(2); 
    set[0] = starship[0] + 7;
    set[1] = starship[1] - 30;
    shootingParticleSet.push_back(set);

    set[0] = starship[0] + 16; 
    set[1] = starship[1] - 30;
    shootingParticleSet.push_back(set);
     
    set[0] = starship[0] + 26; 
    set[1] = starship[1]- 30; 
    shootingParticleSet.push_back(set);

    set[0] = starship[0] + 35; 
    set[1] = starship[1]- 30;
    shootingParticleSet.push_back(set);
}

//Function that updates player
void Pos::updatePlayer() {
    for(std::size_t i = 0; i < shootingParticleSet.size(); i++) shootingParticleSet[i][1] -= laserParticleSpeed;
    this->starshipCore[0] = starship[0] + 13;
    this->starshipCore[1] = starship[1] + 15;
    this->ultimate[0] = starship[0] - 25;
    this->ultimate[1] = starship[1] - 600;
}

//Function that updates particle attack positions
void Pos::updateAttack() {
    for(std::size_t i = 0; i < this->particlePos.size(); i++) {
        //rhomb particles
        this->particlePos[i][0] += this->particleVelocity[i][0];
        this->particlePos[i][1] += this->particleVelocity[i][1];
        this->particleCorePos[i][0] += this->particleVelocity[i][0];
        this->particleCorePos[i][1] += this->particleVelocity[i][1];

    }

    for(std::size_t i = 0; i < this->ballPos.size(); i++) {
        //balls
        this->ballPos[i][0] += this->ballVelocity[i][0];
        this->ballPos[i][1] += this->ballVelocity[i][1];
        this->ballCorePos[i][0] += this->ballVelocity[i][0];
        this->ballCorePos[i][1] += this->ballVelocity[i][1];
    }
}

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

//Function that sets player statsbar Y coordinate
void Pos::setBarY(int health, int power) {
    healthBar[1] = (357 - (3.57 * health)) + 172;
    powerBar[1] = (357 - (3.57 * power)) + 172;
}

//Function that moves enemy positions L1S0
bool Pos::updateL1S0() {
    bool moving = false;
    if(this->enemies[0][0] <= 0) this->enemies[0][0] += enemyMoveSpeed, moving = true;
    if(this->enemies[1][0] <= 50) this->enemies[1][0] += enemyMoveSpeed, moving = true;
    if(this->enemies[2][0] <= 100) this->enemies[2][0] += enemyMoveSpeed, moving = true;
    if(this->enemies[3][0] >= 550) this->enemies[3][0] -= enemyMoveSpeed, moving = true;
    if(this->enemies[4][0] >= 500) this->enemies[4][0] -= enemyMoveSpeed, moving = true;
    if(this->enemies[5][0] >= 450) this->enemies[5][0] -= enemyMoveSpeed, moving = true;

    return moving;
}

bool Pos::updateL1S1() {
    bool moving = false;
    int moveSpeedY = enemyMoveSpeed;
    int moveSpeedX = enemyMoveSpeed - 1;

    //left side enemies
    
    for(size_t i = 0; i < this->enemies.size()/2; i++) {
        if(this->enemies[i][1] <= 300) {
            this->enemies[i][1] += moveSpeedY;
            if(this->enemies[i][1] > -50) this->enemies[i][0] -= moveSpeedX;
            moving = true;
        }
        else this->enemies[i][0] -= (moveSpeedX + 2), moving = true;
    }

    //right side enemies
    for(std::size_t i = this->enemies.size()/2; i < this->enemies.size(); i++) {
        if(this->enemies[i][1] <= 300) {
            this->enemies[i][1] += moveSpeedY;
            if(this->enemies[i][1] > -50) this->enemies[i][0] += moveSpeedX; 
            moving = true;
        }
        else this->enemies[i][0] += (moveSpeedX + 2), moving = true;
    }

    return moving;
}

bool Pos::updateL1S2() {
    const int moveSpeed = enemyMoveSpeed + 2;
    bool moving = false;
    if(this->enemies[0][0] <= 100 && this->enemies[0][1] <= 100) this->enemies[0][0] += moveSpeed, this->enemies[0][1] += moveSpeed, moving = true;
    if(this->enemies[1][1] <= 150) this->enemies[1][1] += moveSpeed, moving = true;
    if(this->enemies[2][0] >= 450 && this->enemies[2][1] <= 100) this->enemies[2][0] -= moveSpeed, this->enemies[2][1] += moveSpeed, moving = true;

    return moving;
}

bool Pos::initL1S3pos() {
    bool moving = false;
    if(this->enemies[0][0] < 100) this->enemies[0][0] += enemyMoveSpeed, moving = true;
    if(this->enemies[1][0] > 500) this->enemies[1][0] -= enemyMoveSpeed, moving = true;

    return moving;
}

void Pos::updateL1S3newPos(stats& mainSta) {
    std::vector<float> temp(2);
    temp.reserve(2);
    float difX;
    float difY;
    
    bool collide = true;

    srand(time(NULL));
    temp[0] = 50 + (rand() % 500);
    while(abs((temp[0] = 50 + (rand() % 500)) - this->enemies[0][0]) < 150);
    srand(time(NULL) + (rand() % 20));
    temp[1] = 50 + (rand() % 250);
    this->newEnemyPos.push_back(temp);
    difX = this->newEnemyPos[0][0] - this->enemies[0][0];
    difY = this->newEnemyPos[0][1] - this->enemies[0][1];
    temp[0] = difX / (sqrt(pow(difX, 2) + pow(difY, 2)) / enemyMoveSpeed), temp[1] = difY / (sqrt(pow(difX, 2) + pow(difY, 2)) / enemyMoveSpeed);
    mainSta.enemyVelocity.push_back(temp);

    srand(time(NULL) *2);
    temp[0] = 50 + (rand() % 500);
    while(abs((temp[0] = 50 + (rand() % 500)) - this->enemies[1][0]) < 150);
    srand(time(NULL) + (rand() % 20));
    temp[1] = 50 + (rand() % 250);
    this->newEnemyPos.push_back(temp);
    difX = this->newEnemyPos[1][0] - this->enemies[1][0];
    difY = this->newEnemyPos[1][1] - this->enemies[1][1];
    temp[0] = difX / (sqrt(pow(difX, 2) + pow(difY, 2)) / enemyMoveSpeed), temp[1] = difY / (sqrt(pow(difX, 2) + pow(difY, 2)) / enemyMoveSpeed);
    mainSta.enemyVelocity.push_back(temp);

}

bool Pos::updateL1S3(stats& mainSta) {
    bool moving = false;
    //std::cout << posTi.getTime() - movingInterval << std::endl; 
    if(mainSta.rotation == false) return moving;
    else {
        if(this->newEnemyPos.size() < 2) this->updateL1S3newPos(mainSta);

        for(int i = 0; i < 2; i++) {
            if(mainSta.enemyVelocity[i][0] < 0 && mainSta.enemyVelocity[i][1] < 0) {
                if(this->enemies[i][0] + mainSta.enemyVelocity[i][0] >= this->newEnemyPos[i][0] && this->enemies[i][1] + mainSta.enemyVelocity[0][1] >= this->newEnemyPos[i][1]) { 
                    this->enemies[i][0] += mainSta.enemyVelocity[i][0];
                    this->enemies[i][1] += mainSta.enemyVelocity[i][1];
                    moving = true;
                }

                else this->newEnemyPos.clear(), mainSta.enemyVelocity.clear(), mainSta.rotation = false;
            }

            else if(mainSta.enemyVelocity[i][0] < 0 && mainSta.enemyVelocity[i][1] > 0) {
                if(this->enemies[i][0] + mainSta.enemyVelocity[i][0] >= this->newEnemyPos[i][0] && this->enemies[i][1] + mainSta.enemyVelocity[i][1] <= this->newEnemyPos[i][1]) { 
                    this->enemies[i][0] += mainSta.enemyVelocity[i][0];
                    this->enemies[i][1] += mainSta.enemyVelocity[i][1];
                    moving = true;
                }

                else this->newEnemyPos.clear(), mainSta.enemyVelocity.clear(), mainSta.rotation = false;
            }

            else if(mainSta.enemyVelocity[i][0] > 0 && mainSta.enemyVelocity[i][1] < 0) {
                if(this->enemies[i][0] + mainSta.enemyVelocity[i][0] <= this->newEnemyPos[i][0] && this->enemies[i][1] + mainSta.enemyVelocity[i][1] >= this->newEnemyPos[i][1]) { 
                    this->enemies[i][0] += mainSta.enemyVelocity[i][0];
                    this->enemies[i][1] += mainSta.enemyVelocity[i][1];
                    moving = true;
                }

                else this->newEnemyPos.clear(), mainSta.enemyVelocity.clear(), mainSta.rotation = false;
            }

            else if(mainSta.enemyVelocity[i][0] > 0 && mainSta.enemyVelocity[i][1] > 0) {
                if(this->enemies[i][0] + mainSta.enemyVelocity[i][0] <= this->newEnemyPos[i][0] && this->enemies[i][1] + mainSta.enemyVelocity[i][1] <= this->newEnemyPos[i][1]) { 
                    this->enemies[i][0] += mainSta.enemyVelocity[i][0];
                    this->enemies[i][1] += mainSta.enemyVelocity[i][1];
                    moving = true;
                }

                else this->newEnemyPos.clear(), mainSta.enemyVelocity.clear(), mainSta.rotation = false;
            }
        }
    }

    return moving;

}



