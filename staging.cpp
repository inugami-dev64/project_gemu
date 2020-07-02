#include "headers/levelstaging.h"
#include "headers/main.h"
#include <math.h>

Timer timer;
int rotation = 0;
int shootingDegreeMultiplier = 1;

//unrelated function but I really didn't want to make another cpp file for this
//Function that returns time passed from 1st January 1970 00:00:00
long Timer::getTime() {
    std::chrono::system_clock::time_point current_time = std::chrono::system_clock::now();
    return current_time.time_since_epoch().count() / 1000000;
}

/* mathematical functions */
//Function that converts degrees to radians
float Stage::degToRad(int deg) {
    return (2*PI*deg)/360;
}

//Function that calculates location on circle
std::vector<float> Stage::getCircleCoordinates(float circleCentre[2], int angle, int radius) {
    std::vector<float> coordinates(2);
    coordinates[0] = circleCentre[0] + radius * cos(this->degToRad(angle));
    coordinates[1] = circleCentre[1] + radius * sin(this->degToRad(angle));

    return coordinates;
}

//Function that pushes enemies to their vectors
void Stage::pushEnemies(stats& mainSta, std::vector<sf::Sprite>& enemyVec, std::vector<std::vector<float>>& posVec ,sf::Sprite& enemy, std::vector<float>& positions, int type) {
    std::vector<long> expl(3);
    expl[0] = false;
    expl[1] = 1;
    expl[2] = timer.getTime();
    
    enemyVec.push_back(enemy);
    posVec.push_back(positions);
    mainSta.exploded.push_back(expl);
    mainSta.enemyType.push_back(type);
    mainSta.enemyHealth.push_back(mainSta.enemyFullHealth[type]);
}

//Function that pushes attack particles to their vectors
void Stage::pushAttack(std::vector<sf::Sprite>& particleVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, stats& mainSta, sf::Sprite& particle, std::vector<float>& positions, std::vector<float>& velocity) {
    particleVec.push_back(particle);
    posVec.push_back(positions);
    velVec.push_back(velocity);
}

//Function that pushes rectangular core to their vectors
void Stage::pushRecCore(std::vector<sf::RectangleShape>& coreVec, std::vector<std::vector<float>>& posVec, sf::RectangleShape& core, std::vector<float>& positions) {
    coreVec.push_back(core);
    posVec.push_back(positions);
}

//Function that pushes circlular core to their vectors
void Stage::pushCirCore(std::vector<sf::CircleShape>& coreVec, std::vector<std::vector<float>>& posVec, sf::CircleShape& core, std::vector<float>& positions) {
    coreVec.push_back(core);
    posVec.push_back(positions);
}


void Stage::initL1S0(Obj& obj, stats& mainSta, Pos& pos) {

    std::vector<float> temp(2);
    temp[0] = -150, temp[1] = 100;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0);

    temp[0] = -100, temp[1] = 50;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0);

    temp[0] = -50, temp[1] = 0;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0);

    temp[0] = 900, temp[1] = 100;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0);

    temp[0] = 850, temp[1] = 50;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0);

    temp[0] = 800, temp[1] = 0;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0);  
}

//Function that generates enemies' fireballs
void Stage::L1S0attack(stats& mainSta, Obj& obj, Pos& pos, long& generationInterval, std::size_t& index) {
    if(index >= obj.enemies.size()) index = 0;
    if(timer.getTime() - generationInterval >= ballSingleAttackDelay && index < obj.enemies.size()) {
        if(mainSta.enemyHealth[index] > 0) {
            std::vector<float> temp(2);
            std::vector<float> velocity(2);
            //temp.reserve(2);
            //velocity.reserve(2);
            velocity[0] = 0;
            velocity[1] = 3;

            temp[0] = pos.enemies[index][0] + 4, temp[1] = pos.enemies[index][1] + 50;
            pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, mainSta, obj.fireballAttack, temp, velocity);
            temp[0] += 5, temp[1] += 5;
            pushRecCore(obj.ballCoreVector, pos.ballCorePos, obj.ballCore, temp);

            temp[0] = pos.enemies[index][0] + 32, temp[1] = pos.enemies[index][1] + 50;
            pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, mainSta, obj.fireballAttack, temp, velocity);
            temp[0] += 5, temp[1] += 5;
            pushRecCore(obj.ballCoreVector, pos.ballCorePos, obj.ballCore, temp);

            generationInterval = timer.getTime();
        }
        index++;
    }
}

void Stage::initL1S1(Obj& obj, stats& mainSta, Pos& pos) {

    //left side enemies
    int enemyAmount = 150;

    //left enemies
    for(int i = 0; i < enemyAmount/2; i++) {
        std::vector<float> temp(2);
        temp[0] = 250, temp[1] = -((i + 1) * 50);
        pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0); 
    }

    //right side enemies
    for(int i = enemyAmount/2, y = 0; i < enemyAmount; i++, y++) {
        std::vector<float> temp(2);
        temp[0] = 300, temp[1] = -((y + 1)* 50);
        pushEnemies(mainSta, obj.enemies, pos.enemies, obj.smallEnemy, temp, 0); 
    }
    
}

//Function that generates enemy attack particles for level 1 stage 1
void Stage::L1S1attack(stats& mainSta, Obj& obj, Pos& pos, long& generationInterval) {

    if(timer.getTime() - generationInterval >= ballMultiAttackDelay) {
        for(std::size_t i = 0; i < obj.enemies.size(); i++) {
            if(mainSta.enemyHealth[i] > 0 && pos.enemies[i][1] > -50) {
                std::vector<float> temp(2);
                std::vector<float> velocity(2);
                velocity[0] = 0;
                velocity[1] = 3;

                temp[0] = pos.enemies[i][0] + 4, temp[1] = pos.enemies[i][1] + 50;
                pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, mainSta, obj.fireballAttack, temp, velocity);
                temp[0] += 5, temp[1] += 5;
                pushRecCore(obj.ballCoreVector, pos.ballCorePos, obj.ballCore, temp);

                temp[0] = pos.enemies[i][0] + 32, temp[1] = pos.enemies[i][1] + 50;
                pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, mainSta, obj.fireballAttack, temp, velocity);
                temp[0] += 5, temp[1] += 5;
                pushRecCore(obj.ballCoreVector, pos.ballCorePos, obj.ballCore, temp);
                
            }
        }

        generationInterval = timer.getTime();
    }
}

void Stage::initL1S2(Obj& obj, stats& mainSta, Pos& pos) {
    std::vector<float> temp(2);


    temp[0] = -100, temp[1] = -100;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.mediumEnemy, temp, 1); 

    temp[0] = 275, temp[1] = -100;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.mediumEnemy, temp, 1); 

    temp[0] = 700, temp[1] = -150;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.mediumEnemy, temp, 1); 

}

void Stage::L1S2attack(Obj& obj, stats& mainSta, Pos& pos, long& generationInterval, std::size_t& generationIndex) {
    if(timer.getTime() - generationInterval >= particleRingDelay) {
        float circleCenter[2];

        switch (generationIndex)
        {
        case 0:
            circleCenter[0] = pos.enemies[0][0] + obj.enemies[0].getLocalBounds().width/2;
            circleCenter[1] = pos.enemies[0][1] + obj.enemies[0].getLocalBounds().height/2;

            if(mainSta.enemyHealth[0] > 0) {
                for(int i = 0; i < 360/9; i++) {

                    std::vector<float> temp = getCircleCoordinates(circleCenter, i*9, 40);

                    //This varriable shows how much have the coordinates changed compared to the centre point of the circle
                    std::vector<float> velocity(2);
                    velocity[0] = (temp[0] - circleCenter[0])/40*particleSpeed, velocity[1] = (temp[1] - circleCenter[1])/40*particleSpeed;

                    pushAttack(obj.rhombParticles, pos.particlePos, pos.particleVelocity, mainSta, obj.blueParticleAttack, temp, velocity);
                    obj.rhombParticles[obj.rhombParticles.size()-1].setRotation(i*9 - 90);
                    obj.rhombParticles[obj.rhombParticles.size()-1].setOrigin(5.f, 7.5f);
                    pushCirCore(obj.particleCoreVector, pos.particleCorePos, obj.particleCore, temp);
                    obj.particleCoreVector[obj.particleCoreVector.size()-1].setOrigin(3.f, 3.f);

                }
            }
            generationIndex++;
            break;

        case 1:
            circleCenter[0] = pos.enemies[1][0] + obj.enemies[1].getLocalBounds().width/2;
            circleCenter[1] = pos.enemies[1][1] + obj.enemies[1].getLocalBounds().height/2;

            if(mainSta.enemyHealth[1] > 0) {
                for(int i = 0; i < 360/9; i++) {
                    std::vector<float> temp = getCircleCoordinates(circleCenter, i*9, 40);

                    //This varriable shows how much have the coordinates changed compared to the centre point of the circle
                    std::vector<float> velocity(2);
                    velocity[0] = (temp[0] - circleCenter[0])/40*particleSpeed, velocity[1] = (temp[1] - circleCenter[1])/40*particleSpeed;

                    pushAttack(obj.rhombParticles, pos.particlePos, pos.particleVelocity, mainSta, obj.purpleParticleAttack, temp, velocity);
                    obj.rhombParticles[obj.rhombParticles.size()-1].setRotation(i*9 - 90);
                    obj.rhombParticles[obj.rhombParticles.size()-1].setOrigin(5.f, 7.5f);
                    pushCirCore(obj.particleCoreVector, pos.particleCorePos, obj.particleCore, temp);
                    obj.particleCoreVector[obj.particleCoreVector.size()-1].setOrigin(3.f, 3.f);

                }
            }
            generationIndex++;
            break;
        
        case 2:
           circleCenter[0] = pos.enemies[2][0] + obj.enemies[2].getLocalBounds().width/2;
           circleCenter[1] = pos.enemies[2][1] + obj.enemies[2].getLocalBounds().height/2;

           if(mainSta.enemyHealth[2] > 0) {
               for(int i = 0; i < 360/9; i++) {
                    std::vector<float> temp = getCircleCoordinates(circleCenter, i*9, 40);

                    //This varriable shows how much have the coordinates changed compared to the centre point of the circle
                    std::vector<float> velocity(2);
                    velocity[0] = (temp[0] - circleCenter[0])/40*particleSpeed, velocity[1] = (temp[1] - circleCenter[1])/40*particleSpeed;

                    pushAttack(obj.rhombParticles, pos.particlePos, pos.particleVelocity, mainSta, obj.goldParticleAttack, temp, velocity);
                    obj.rhombParticles[obj.rhombParticles.size()-1].setRotation(i*9 - 90);
                    obj.rhombParticles[obj.rhombParticles.size()-1].setOrigin(5.f, 7.5f);
                    pushCirCore(obj.particleCoreVector, pos.particleCorePos, obj.particleCore, temp);
                    obj.particleCoreVector[obj.particleCoreVector.size()-1].setOrigin(3.f, 3.f);

                }
            }
            generationIndex = 0;
            break;

        default:
            break;
        }

        generationInterval = timer.getTime();

    }
}

void Stage::initL1S3(Obj& obj, stats& mainSta, Pos& pos) {
    std::vector<float> temp(2);

    temp[0] = -100, temp[1] = 100;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.shurikenEnemy, temp, 1); 

    temp[0] = 700, temp[1] = 100;
    pushEnemies(mainSta, obj.enemies, pos.enemies, obj.shurikenEnemy, temp, 1);

    for(std::size_t i = 0; i < obj.enemies.size(); i++) obj.enemies[i].setOrigin(25.f, 25.f);
}

void Stage::L1S3attack(Obj& obj, stats& mainSta, Pos& pos, long& generationInterval, std::size_t& index) {
    mainSta.rotation = false;
    obj.enemies[0].setRotation(rotation);
    obj.enemies[1].setRotation(rotation);

    if(timer.getTime() - generationInterval >= ballFlowerAttackDelay && mainSta.enemyHealth[index] > 0) {

        for(int ii = 0; ii < 9; ii++) {
            float circleCentre[2] = {pos.enemies[index][0], pos.enemies[index][1]};
            int ballAngle = rotation + (ii * 45);
            std::vector<float> temp = getCircleCoordinates(circleCentre, ballAngle, 25);
            
            std::vector<float> velocity(2);
            velocity[0] = (temp[0] - circleCentre[0])/25*particleSpeed, velocity[1] = (temp[1] - circleCentre[1])/25*particleSpeed;
            
            switch (index)
            {
                case 0:
                    pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, mainSta, obj.neonballAttack, temp, velocity);
                    break;
                
                case 1:
                    pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, mainSta, obj.rubyballAttack, temp, velocity);
                    break;
                default:
                    break;
            }
            
            obj.balls[obj.balls.size()-1].setOrigin(7.5, 7.5);
            pushRecCore(obj.ballCoreVector, pos.ballCorePos, obj.ballCore, temp);
            obj.ballCoreVector[obj.ballCoreVector.size()-1].setOrigin(2.5, 2.5);
        }
        generationInterval = timer.getTime();
    }

    if(rotation < 360) rotation += enemyRotationSpeed, mainSta.rotation = false;
    else {
        rotation = 0, mainSta.rotation = true; 
        if(index == 1 && mainSta.enemyHealth[0] > 0) index=0; 
        else if(index == 0 && mainSta.enemyHealth[1] > 0) index++;
    }

}