#include "headers/positions.h"
#include "headers/stats.h"
#include "headers/levelstaging.h"
#include "headers/main.h"
#include "headers/engine.h"
#include <math.h>
#include <iostream>

Calc posCalc;

Pos::Pos() {
    //player
    starship.reserve(2);
    starshipCore.reserve(2);
    ultimate.reserve(2);
    for(int i = 0; i < 2; i++) starshipCore.push_back(0), ultimate.push_back(0);
    starship.push_back(275);
    starship.push_back(550);
    starshipCore.push_back(292.5);
    starshipCore.push_back(567.5);

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
/****************** Class Move ******************/

//Generic movement
//Function that moves game object
void Move::genericMove(std::vector<std::vector<float>>& posVec, float x_vel, float y_vel, int index) {
    posVec[index][0] += x_vel;
    posVec[index][1] += y_vel;
}

//Function that sets player shooting particle locations
void Move::setPlayerShooting(Pos& pos) {
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

void Move::update(Pos& pos, Stats& mainSta) {
    //player related
    for(std::size_t i = 0; i < pos.shootingParticlePos.size(); i++) pos.shootingParticlePos[i][1] -= laserParticleSpeed;
    pos.starshipCore[0] = pos.starship[0] + 16.5;
    pos.starshipCore[1] = pos.starship[1] + 18;
    pos.ultimate[0] = pos.starship[0] - 25;
    pos.ultimate[1] = pos.starship[1] - 600;

    //particle related
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

    //bars
    pos.healthBar[1] = (357 - (3.57 * mainSta.health)) + 172;
    pos.powerBar[1] = (357 - (3.57 * mainSta.power)) + 172;

}

//Player movement functions
//Move object forward
void Move::playerMoveF(Pos& pos) {
    pos.starship[1]-=playerMoveSpeed;
    pos.starshipCore[1]-=playerMoveSpeed;
}

//Move object front leftwards
void Move::playerMoveFL(Pos& pos, float& playerMoveDiagSpeed) {
    pos.starship[0]-=playerMoveDiagSpeed; pos.starship[1]-=playerMoveDiagSpeed;
    pos.starshipCore[0]-=playerMoveDiagSpeed; pos.starshipCore[1]-=playerMoveDiagSpeed;
}
    
//Move object front rightwards
void Move::playerMoveFR(Pos& pos, float& playerMoveDiagSpeed) {
    pos.starship[0]+=playerMoveDiagSpeed; pos.starship[1]-=playerMoveDiagSpeed;
    pos.starshipCore[0]+=playerMoveDiagSpeed; pos.starshipCore[1]-=playerMoveDiagSpeed;
}

//Move object backwards
void Move::playerMoveB(Pos& pos) {
    pos.starship[1]+=playerMoveSpeed;
    pos.starshipCore[1]+=playerMoveSpeed;
}

//Move object backwards left
void Move::playerMoveBL(Pos& pos, float& playerMoveDiagSpeed) {
    pos.starship[0]-=playerMoveDiagSpeed, pos.starship[1]+=playerMoveDiagSpeed;
    pos.starshipCore[0]-=playerMoveDiagSpeed, pos.starshipCore[1]+=playerMoveDiagSpeed;
}

//Move object backwards rightwards
void Move::playerMoveBR(Pos& pos, float& playerMoveDiagSpeed) {
    pos.starship[0]+=playerMoveDiagSpeed; pos.starship[1]+=playerMoveDiagSpeed;
    pos.starshipCore[0]+=playerMoveDiagSpeed; pos.starshipCore[1]+=playerMoveDiagSpeed;
}

//Move object rightwards
void Move::playerMoveR(Pos& pos) {
    pos.starship[0]+=playerMoveSpeed;
    pos.starshipCore[0]+=playerMoveSpeed;
}

//Move object leftwards
void Move::playerMoveL(Pos& pos) {
    pos.starship[0]-=playerMoveSpeed;
    pos.starshipCore[0]-=playerMoveSpeed;
}

//Function that handles player movement
void Move::handleMovement(Pos& pos, float& playerMoveDiagSpeed) {
    //forward
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && pos.starship[1] > minPosY) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] > minPosX) this->playerMoveFL(pos, playerMoveDiagSpeed);
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && pos.starship[0] < maxPosX) this->playerMoveFR(pos, playerMoveDiagSpeed);
        else this->playerMoveF(pos);

    }
    
    //backwards
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && pos.starship[1] < maxPosY) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] > minPosX) this->playerMoveBL(pos, playerMoveDiagSpeed);
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && pos.starship[0] < maxPosX) this->playerMoveBR(pos, playerMoveDiagSpeed);
        else this->playerMoveB(pos);
    }

    //rightwards
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && pos.starship[0] < maxPosX) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && pos.starship[1] > minPosY) this->playerMoveFR(pos, playerMoveDiagSpeed);
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && pos.starship[1] < maxPosY) this->playerMoveBR(pos, playerMoveDiagSpeed);
        else this->playerMoveR(pos);
    }

    //leftwards
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] > minPosX) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && pos.starship[1] > minPosY) this->playerMoveFL(pos, playerMoveDiagSpeed);
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && pos.starship[1] < maxPosY) this->playerMoveBL(pos, playerMoveDiagSpeed);
        else this->playerMoveL(pos);
    }
}



/****************** Class StagePos functions  *********/

//Variable needed to detect if randomly moving enemies are initialised to avoid weird movement glitches
bool StagePos::initialised = false;

//Staging functions
//Function that loads stage for level
bool StagePos::initLvlOneMovement(Pos& pos, Stats& mainSta) {
    bool moving = false;
    switch (mainSta.stage)
    {
    case 0:
    {
        if(pos.enemies[0][0] <= 0) pos.enemies[0][0] += pos.enemyVelocity[0][0], moving = true;
        if(pos.enemies[1][0] <= 50) pos.enemies[1][0] += pos.enemyVelocity[1][0], moving = true;
        if(pos.enemies[2][0] <= 100) pos.enemies[2][0] += pos.enemyVelocity[2][0], moving = true;
        if(pos.enemies[3][0] >= 550) pos.enemies[3][0] += pos.enemyVelocity[3][0], moving = true;
        if(pos.enemies[4][0] >= 500) pos.enemies[4][0] += pos.enemyVelocity[4][0], moving = true;
        if(pos.enemies[5][0] >= 450) pos.enemies[5][0] += pos.enemyVelocity[5][0], moving = true;

        return moving;
        break;
    }

    case 1:
    {
        moving = true;
        //left side enemies
        for(size_t i = 0; i < pos.enemies.size()/2; i++) {
            if(pos.enemies[i][1] <= 300) {
                pos.enemies[i][0] += pos.enemyVelocity[i][0];
                pos.enemies[i][1] += pos.enemyVelocity[i][1];
                if(pos.enemies[i][1] >= -50 && pos.enemyVelocity[i][0] == 0) pos.enemyVelocity[i][0] = (-mainSta.enemySpeed)+1;
                moving = false;
            }
            else pos.enemies[i][0] += pos.enemyVelocity[i][0], moving = false;
        }

        //right side enemies
        for(std::size_t i = pos.enemies.size()/2; i < pos.enemies.size(); i++) {
            if(pos.enemies[i][1] <= 300) {
                pos.enemies[i][0] += pos.enemyVelocity[i][0];
                pos.enemies[i][1] += pos.enemyVelocity[i][1];
                if(pos.enemies[i][1] >= -50 && pos.enemyVelocity[i][0] == 0) pos.enemyVelocity[i][0] = mainSta.enemySpeed-1;
                moving = false;
            }
            else pos.enemies[i][0] += pos.enemyVelocity[i][0], moving = false;
        }

        return moving;
    }

    case 2:
    {
        const int moveSpeed = mainSta.enemySpeed + 2;
        moving = false;
        if(pos.enemies[0][0] <= 100 && pos.enemies[0][1] <= 100) pos.enemies[0][0] += pos.enemyVelocity[0][0], pos.enemies[0][1] += pos.enemyVelocity[0][1], moving = true;
        if(pos.enemies[1][1] <= 150) pos.enemies[1][1] += pos.enemyVelocity[1][1], moving = true;
        if(pos.enemies[2][0] >= 450 && pos.enemies[2][1] <= 100) pos.enemies[2][0] += pos.enemyVelocity[2][0], pos.enemies[2][1] += pos.enemyVelocity[2][1], moving = true;

        return moving;
    }
    
    case 3:
    {
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

        else {
            moving = false;
            
            if(pos.newEnemyPos.size() == 2) {
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
    }

    case 4:
    {   
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

        else {
            moving = false;
            
            if(pos.newEnemyPos.size() == 2) {
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
    }
    default:
        return false;
    }
}



