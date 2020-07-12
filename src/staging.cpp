#include "headers/levelstaging.h"
#include "headers/main.h"
#include <math.h>

Attack attack;
ManageVectors manageVec;
Attack::Pointers ptr;
int rotation = 0;
int shootingDegreeMultiplier = 1;

/****************** Attack class ***************/
//Function that pushes attack particles to their vectors
void Attack::pushAttack(std::vector<sf::Sprite>& particleVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, sf::Sprite& particle, std::vector<float>& positions, std::vector<float>& velocity) {
    particleVec.push_back(particle);
    posVec.push_back(positions);
    velVec.push_back(velocity);
}

//Function that pushes rectangular core to their vectors
//type 1 is ball core, type 2 is rhomb core
void Attack::pushCore(std::vector<float>& positions, int type, Pos& pos, Obj& obj) {
    switch (type)
    {
    case 1:
        obj.ballCoreVector.push_back(obj.ballCore);
        pos.ballCorePos.push_back(positions);
        break;

    case 2:
        obj.particleCoreVector.push_back(obj.particleCore);
        pos.particleCorePos.push_back(positions);
    
    default:
        break;
    }
}

//Function that initialises vector pointers
void Attack::Pointers::getPointers(int type, Pos& pos, Obj& obj) {
    switch (type)
    {
    case 1:
        this->posVecPtr = &pos.ballPos;
        this->particleVecPtr = &obj.balls;
        this->velVecPtr = &pos.ballVelocity;
        this->corePosVecPtr = &pos.ballCorePos;
        break;
    
    case 2:
        this->posVecPtr = &pos.particlePos;
        this->particleVecPtr = &obj.rhombParticles;
        this->velVecPtr = &pos.particleVelocity;
        this->corePosVecPtr = &pos.particleCorePos;
        break;
    
    default:
        break;
    }
}

//Function that shoots particles down from enemy
void Attack::basicDualAttackDown(std::size_t& enemyIndex, Pos& pos, Obj& obj, int particleType, sf::Sprite& particle) {
    std::vector<float> temp(2);
    std::vector<float> velocity(2);
    velocity[0] = 0;
    velocity[1] = 3;

    ptr.getPointers(particleType, pos, obj);
    std::vector<std::vector<float>>& posVec = *ptr.posVecPtr;
    std::vector<sf::Sprite>& particleVec = *ptr.particleVecPtr;
    std::vector<std::vector<float>>& velVec = *ptr.velVecPtr;
    std::vector<std::vector<float>>& corePosVec = *ptr.corePosVecPtr;

    temp[0] = pos.enemies[enemyIndex][0] + 4, temp[1] = pos.enemies[enemyIndex][1] + 50;
    this->pushAttack(particleVec, posVec, velVec, particle, temp, velocity);
    temp[0] += 5, temp[1] += 5;
    this->pushCore(temp, 1, pos, obj);

    temp[0] = pos.enemies[enemyIndex][0] + 32, temp[1] = pos.enemies[enemyIndex][1] + 50;
    this->pushAttack(particleVec, posVec, velVec, particle, temp, velocity);
    temp[0] += 5, temp[1] += 5;
    this->pushCore(temp, 1, pos, obj);
}

//Function that makes circular attack particle pattern
//type 1 is ball particles type 2 is rhomb 
void Attack::circularAttack(std::size_t enemyIndex, Pos& pos, Obj& obj, Stats& mainSta, int particleType, int frequency, int startRadius, sf::Sprite& particle, Calc& calc) {
    ptr.getPointers(particleType, pos, obj);
    std::vector<std::vector<float>>& posVec = *ptr.posVecPtr;
    std::vector<sf::Sprite>& particleVec = *ptr.particleVecPtr;
    std::vector<std::vector<float>>& velVec = *ptr.velVecPtr;
    std::vector<std::vector<float>>& corePosVec = *ptr.corePosVecPtr;

    float circleCenter[2];
    circleCenter[0] = pos.enemies[enemyIndex][0] + obj.enemies[enemyIndex].getLocalBounds().width/2;
    circleCenter[1] = pos.enemies[enemyIndex][1] + obj.enemies[enemyIndex].getLocalBounds().height/2;

    for(int i = 0; i < frequency; i++) {

        std::vector<float> temp = calc.getCircleCoordinates(circleCenter, i*(360/frequency), startRadius);
        std::vector<float> velocity(2);
        velocity[0] = (temp[0] - circleCenter[0])/startRadius*mainSta.particleSpeed, velocity[1] = (temp[1] - circleCenter[1])/startRadius*mainSta.particleSpeed;

        this->pushAttack(particleVec, posVec, velVec, particle, temp, velocity);
        particleVec[particleVec.size()-1].setRotation(i*(360/frequency) - 90);
        particleVec[particleVec.size()-1].setOrigin(particleVec[particleVec.size()-1].getLocalBounds().width/2, particleVec[particleVec.size()-1].getLocalBounds().height/2);
        this->pushCore(temp, particleType, pos, obj);
        obj.particleCoreVector[obj.particleCoreVector.size()-1].setOrigin(3.f, 3.f);

    }
}

//Function that rotates enemy and performs flower attack
//Only balls can be used
void Attack::flowerAttack(std::size_t enemyIndex, Pos& pos, Obj& obj, Stats& mainSta, int startRadius, int frequency, sf::Sprite& ball, Calc& calc) {
    obj.enemies[enemyIndex].setOrigin(obj.enemies[enemyIndex].getLocalBounds().width/2, obj.enemies[enemyIndex].getLocalBounds().height/2);
    for(int cycle = 0; cycle < frequency; cycle++) {
        float circleCentre[2] = {pos.enemies[enemyIndex][0], pos.enemies[enemyIndex][1]};
        int ballAngle = rotation + (cycle * (360/frequency));
        std::vector<float> temp = calc.getCircleCoordinates(circleCentre, ballAngle, startRadius);
        
        std::vector<float> velocity(2);
        velocity[0] = (temp[0] - circleCentre[0])/startRadius*mainSta.particleSpeed, velocity[1] = (temp[1] - circleCentre[1])/startRadius*mainSta.particleSpeed;
        
        pushAttack(obj.balls, pos.ballPos, pos.ballVelocity, ball, temp, velocity);
        obj.balls[obj.balls.size()-1].setOrigin(7.5, 7.5);
        pushCore(temp, 1, pos, obj);
        obj.ballCoreVector[obj.ballCoreVector.size()-1].setOrigin(2.5, 2.5);
    }
}

/************ Class ManageVectors ************/
//Function that pushes enemies to their vectors
void ManageVectors::pushEnemies(Stats& mainSta, std::vector<sf::Sprite>& enemyVec, std::vector<std::vector<float>>& posVec, std::vector<std::vector<float>>& velVec, sf::Sprite& enemy, std::vector<float>& positions, std::vector<float>& velocity, int type, Calc& calc) {
    std::vector<long> expl(3);
    expl[0] = false;
    expl[1] = 1;
    expl[2] = calc.getTime();
    
    enemyVec.push_back(enemy);
    posVec.push_back(positions);
    velVec.push_back(velocity);
    mainSta.exploded.push_back(expl);
    mainSta.enemyType.push_back(type);
    mainSta.enemyHealth.push_back(mainSta.enemyFullHealth[type]);
}


//Function that clears the stage from all enemies
void ManageVectors::clearStage(Pos& pos, Obj& obj, Stats& mainSta) {
        obj.enemies.clear(); 
        pos.enemies.clear();
        mainSta.enemyHealth.clear();
        mainSta.exploded.clear();
        mainSta.enemyType.clear();
        pos.enemyVelocity.clear();
}

//Function that clears all particles from display
void ManageVectors::clearParticles(Pos& pos, Obj& obj) {
    //balls
    obj.balls.clear();
    obj.ballCoreVector.clear();
    pos.ballPos.clear();
    pos.ballCorePos.clear();
    pos.ballVelocity.clear();

    //rhomb particles
    obj.rhombParticles.clear();
    obj.particleCoreVector.clear();
    pos.particlePos.clear();
    pos.particleCorePos.clear();
    pos.particleVelocity.clear();

    //player shooted laser particles
    obj.shootingParticles.clear();
    pos.shootingParticlePos.clear();
}

//Function that erases all particles that are outside of the game frame
void ManageVectors::cleanAssets(bool cleanEnemies, Pos& pos, Obj& obj, Stats& mainSta) {
    //laser particles
    for(std::size_t i = 0; i < pos.shootingParticlePos.size(); i++) 
        if(pos.shootingParticlePos[i][1] < -100) pos.shootingParticlePos.erase(pos.shootingParticlePos.begin()+i), obj.shootingParticles.erase(obj.shootingParticles.begin()+i);
    
    //balls
    for(std::size_t i = 0; i < obj.balls.size(); i++) 
        if(pos.ballPos[i][1] > 610 || pos.ballPos[i][1] < -10 || pos.ballPos[i][0] < -10 || pos.ballPos[i][0] > 610) {
            pos.ballPos.erase(pos.ballPos.begin() +i);
            obj.balls.erase(obj.balls.begin()+i);
            pos.ballCorePos.erase(pos.ballCorePos.begin()+i);
            obj.ballCoreVector.erase(obj.ballCoreVector.begin() + i); 
            pos.ballVelocity.erase(pos.ballVelocity.begin()+i);
        }

    //rhomb attack particles
    for(std::size_t i = 0; i < obj.rhombParticles.size(); i++) 
        if(pos.particlePos[i][0] < -10 || pos.particlePos[i][0] > 610 || pos.particlePos[i][1] < -10 || pos.particlePos[i][1] > 610)
            pos.particlePos.erase(pos.particlePos.begin()+i),
            pos.particleCorePos.erase(pos.particleCorePos.begin()+i),
            obj.rhombParticles.erase(obj.rhombParticles.begin()+i),
            obj.particleCoreVector.erase(obj.particleCoreVector.begin()+i),
            pos.particleVelocity.erase(pos.particleVelocity.begin()+i);
    
    //enemies 
    if(cleanEnemies) {
        for(std::size_t i = 0; i < obj.enemies.size(); i++)
            if(pos.enemies[i][0] > 600 || pos.enemies[i][0] < -100 || pos.enemies[i][1] > 600)
                obj.enemies.erase(obj.enemies.begin()+i), pos.enemies.erase(pos.enemies.begin()+i), pos.enemyVelocity.erase(pos.enemyVelocity.begin()+i), 
                mainSta.enemyHealth.erase(mainSta.enemyHealth.begin()+i), mainSta.exploded.erase(mainSta.exploded.begin()+i);
    }
}

/********** Level 1 *************/
void LevelOne::handleLvlAttack(Obj& obj, Stats& mainSta, Pos& pos, long& generationInterval, std::size_t& generationIndex, StagePos& initPos, Calc& calc) {
    switch (mainSta.stage)
    {
    case 0:
    {
        if(generationIndex >= obj.enemies.size()) generationIndex = 0;
        if(calc.getTime() - generationInterval >= ballSingleAttackDelay && generationIndex < obj.enemies.size()) {
            if(mainSta.enemyHealth[generationIndex] > 0) {
                attack.basicDualAttackDown(generationIndex, pos, obj, 1, obj.rubyballAttack);
                generationInterval = calc.getTime();
            }
            generationIndex++;
        }
        break;
    }

    case 1:
    {
        if(calc.getTime() - generationInterval >= ballMultiAttackDelay) {
            for(std::size_t i = 0; i < obj.enemies.size(); i++) 
                if(mainSta.enemyHealth[i] > 0 && pos.enemies[i][1] > -50) attack.basicDualAttackDown(i, pos, obj, 1, obj.fireballAttack);
            generationInterval = calc.getTime();
        }
        break;
    }

    case 2:
    {
        if(calc.getTime() - generationInterval >= particleRingDelay) {
            float circleCenter[2];
            int freq = 40;

            switch (generationIndex)
            {
            case 0:
                if(mainSta.enemyHealth[0] > 0) 
                    attack.circularAttack(0, pos, obj, mainSta, 2, freq, 40, obj.blueParticleAttack, calc);
                generationIndex++;
                break;

            case 1:
                if(mainSta.enemyHealth[1] > 0) 
                    attack.circularAttack(1, pos, obj, mainSta, 2, freq, 40, obj.goldParticleAttack, calc);
                generationIndex++;
                break;
            
            case 2:
                if(mainSta.enemyHealth[2] > 0) 
                    attack.circularAttack(2, pos, obj, mainSta, 2, freq, 40, obj.purpleParticleAttack, calc);
                generationIndex = 0;
                break;

            default:
                break;
            }

            generationInterval = calc.getTime();
        }
        break;
    }

    case 3:
    {
        mainSta.rotation = false;
        obj.enemies[0].setRotation(rotation);
        obj.enemies[1].setRotation(rotation);

        if(calc.getTime() - generationInterval >= ballFlowerAttackDelay && mainSta.enemyHealth[generationIndex] > 0) {
            int freq = 7.5;
            switch (generationIndex)
            {
            case 0:
                attack.flowerAttack(generationIndex, pos, obj, mainSta, 25, freq, obj.rubyballAttack, calc);
                break;
            case 1:
                attack.flowerAttack(generationIndex, pos, obj, mainSta, 25, freq, obj.neonballAttack, calc);
                break;
            
            default:
                break;
            }
            generationInterval = calc.getTime();
        }

        if(rotation < 360) rotation += mainSta.enemyRotationSpeed, mainSta.rotation = false;
        else {
            pos.newEnemyPos.clear();
            pos.enemyVelocity.clear();
            rotation = 0, mainSta.rotation = true; 
            pos.newEnemyPos.push_back(calc.getNewRandomCoordinates(50, 500, 50, 250, pos.enemies[generationIndex], 100, 100, 1));
            pos.enemyVelocity.push_back(calc.calcVelocity(pos.enemies[0], pos.newEnemyPos[0], 3.3));
            pos.newEnemyPos.push_back(calc.getNewRandomCoordinates(50, 500, 50, 250, pos.enemies[generationIndex], 100, 100, 2));
            pos.enemyVelocity.push_back(calc.calcVelocity(pos.enemies[1], pos.newEnemyPos[1], 3.3));

            if(generationIndex == 1 && mainSta.enemyHealth[0] > 0) generationIndex = 0; 
            else if(generationIndex == 0 && mainSta.enemyHealth[1] > 0) generationIndex++;
        }
        break;
    }

    case 4:
    {
        if(calc.getTime() - generationInterval >= burstAttackDelay) {
            mainSta.particleSpeed = 3.8;
            switch (generationIndex)
            {
            case 0:
            {
                if(mainSta.enemyHealth[0] > 0)
                   attack.circularAttack(0, pos, obj, mainSta, 2, 40, 40, obj.blueParticleAttack, calc);

                if(mainSta.enemyHealth[1] > 0)
                    attack.circularAttack(1, pos, obj, mainSta, 2, 40, 40, obj.blueParticleAttack, calc);
                generationIndex++;
                std::cout << "case: 0" << std::endl;
                break;
            }

            case 1: 
            {
                if(mainSta.enemyHealth[0] > 0)
                    attack.circularAttack(0, pos, obj, mainSta, 2, 60, 40, obj.goldParticleAttack, calc);
                if(mainSta.enemyHealth[1] > 0)
                    attack.circularAttack(1, pos, obj, mainSta, 2, 60, 40, obj.goldParticleAttack, calc);
                generationIndex++;
                std::cout << "case: 1" << std::endl;
                break;
            }
            
            case 2:
            {
                if(mainSta.enemyHealth[0] > 0)
                    attack.circularAttack(0, pos, obj, mainSta, 2, 72, 40, obj.purpleParticleAttack, calc);

                if(mainSta.enemyHealth[1] > 0)
                    attack.circularAttack(1, pos, obj, mainSta, 2, 72, 40, obj.purpleParticleAttack, calc);
                generationIndex++;
                std::cout << "case 2" << std::endl;
                break;
            }

            case 3:
            {
                pos.newEnemyPos.clear();
                pos.enemyVelocity.clear();
                pos.newEnemyPos.push_back(calc.getNewRandomCoordinates(50, 500, 50, 250, pos.enemies[0], 100, 100, 1));
                pos.enemyVelocity.push_back(calc.calcVelocity(pos.enemies[0], pos.newEnemyPos[0], 3.5));
                pos.newEnemyPos.push_back(calc.getNewRandomCoordinates(50, 500, 50, 250, pos.enemies[1], 100, 100, 2));
                pos.enemyVelocity.push_back(calc.calcVelocity(pos.enemies[1], pos.newEnemyPos[1], 3.5));

                generationIndex = 0;
                break;
            }


            default:
                break; 
            }
            generationInterval = calc.getTime();
            break;
        }
    }
    
    default:
        break;
    }
}

void LevelOne::initLvl(Obj& obj, Stats& mainSta, Pos& pos, Calc& calc) {
    switch (mainSta.stage)
    {
    case 0:
    {
        std::vector<float> temp(2);
        std::vector<float> vel(2);

        temp[0] = -150, temp[1] = 100;
        vel[0] = mainSta.enemySpeed, vel[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc);

        temp[0] = -100, temp[1] = 50;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc);

        temp[0] = -50, temp[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc);

        temp[0] = 900, temp[1] = 100;
        vel[0] = -mainSta.enemySpeed, vel[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc);

        temp[0] = 850, temp[1] = 50;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc);

        temp[0] = 800, temp[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc); 
        break;
    }

    case 1:
    {
        //left side enemies
        int enemyAmount = 80;

        std::vector<float> vel(2);
        vel[0] = 0, vel[1] = mainSta.enemySpeed;

        //left enemies
        for(int i = 0; i < enemyAmount/2; i++) {
            std::vector<float> temp(2);
            temp[0] = 250, temp[1] = -((i + 1) * 50);
            manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity ,obj.smallEnemy, temp, vel, 0, calc); 
        }

        //right side enemies
        for(int i = enemyAmount/2, y = 0; i < enemyAmount; i++, y++) {
            std::vector<float> temp(2);
            temp[0] = 300, temp[1] = -((y + 1)* 50);
            manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.smallEnemy, temp, vel, 0, calc); 
        }
        break;
    }

    case 2:
    {
        std::vector<float> temp(2);
        std::vector<float> vel(2);

        temp[0] = -100, temp[1] = -100;
        vel[0] = mainSta.enemySpeed + 2; vel[1] = mainSta.enemySpeed + 2;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.mediumEnemy, temp, vel, 1, calc); 

        temp[0] = 275, temp[1] = -100;
        vel[0] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.mediumEnemy, temp, vel, 1, calc); 

        temp[0] = 700, temp[1] = -150;
        vel[0] = -(mainSta.enemySpeed + 2), vel[1] = mainSta.enemySpeed + 2;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.mediumEnemy, temp, vel, 1, calc); 
        break;
    }

    case 3:
    {   
        std::vector<float> temp(2);
        std::vector<float> vel(2);

        temp[0] = -100, temp[1] = 100;
        vel[0] = mainSta.enemySpeed, vel[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.shurikenEnemy, temp, vel, 1, calc); 

        temp[0] = 700, temp[1] = 100;
        vel[0] = -mainSta.enemySpeed;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.shurikenEnemy, temp, vel, 1, calc); 

        for(std::size_t i = 0; i < obj.enemies.size(); i++) obj.enemies[i].setOrigin(25.f, 25.f);
        break;
    }

    case 4:
    {
        std::vector<float> temp(2);
        std::vector<float> vel(2);

        temp[0] = -100, temp[1] = 100;
        vel[0] = mainSta.enemySpeed, vel[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.mediumEnemy, temp, vel, 1, calc);

        temp[0] = 700, temp[1] = 100;
        vel[0] = -mainSta.enemySpeed, vel[1] = 0;
        manageVec.pushEnemies(mainSta, obj.enemies, pos.enemies, pos.enemyVelocity, obj.mediumEnemy, temp, vel, 1, calc);
        break;
    }

    
    default:
        break;
    }
}

void LevelOne::drawStage(Pos& pos, Obj& obj, Stats& mainSta, StagePos& stagePos, Calc& calc, long& stageInterval, long& generationInterval, std::size_t& generationIndex, bool cleanEnemiesOutFrame) {
    if(calc.getTime() - stageInterval >= stageDelay) {
        obj.explosion.setOrigin(0.f, 0.f);
        if(!stagePos.initLvlOneMovement(pos, mainSta)) this->handleLvlAttack(obj, mainSta, pos, generationInterval, generationIndex, stagePos, calc);
        manageVec.cleanAssets(cleanEnemiesOutFrame, pos, obj, mainSta);

        bool nextStage = true;
        for(std::size_t i = 0; i < mainSta.enemyHealth.size(); i++) if(mainSta.enemyHealth[i] > 0 || !mainSta.exploded[i][0]) nextStage = false; 
        if(nextStage) mainSta.stage++, stageInterval = calc.getTime(), manageVec.clearStage(pos, obj, mainSta), this->initLvl(obj, mainSta, pos, calc), generationIndex = 0, stagePos.initialised = false;
    }
}

void LevelOne::handleLvl(Obj& obj, Stats& mainSta, Pos& pos, Calc& calc, StagePos& stagePos, long& generationInterval, long& stageInterval ,std::size_t& generationIndex) {
    //stage 0
    if(mainSta.stage == 0) {
        obj.explosion.setOrigin(0.f, 0.f);
        this->drawStage(pos, obj, mainSta, stagePos, calc, stageInterval, generationInterval, generationIndex, 0);
    }

    //stage 1
    if(mainSta.stage == 1) this->drawStage(pos, obj, mainSta, stagePos, calc, stageInterval, generationInterval, generationIndex, 1);
    

    //stage 2
    if(mainSta.stage == 2) this->drawStage(pos, obj, mainSta, stagePos, calc, stageInterval, generationInterval, generationIndex, 0);
    

    //stage 3
    if(mainSta.stage == 3) {
        obj.explosion.setOrigin(25.f, 25.f);
        this->drawStage(pos, obj, mainSta, stagePos, calc, stageInterval, generationInterval, generationIndex, 0);
    }

    if(mainSta.stage == 4) this->drawStage(pos, obj, mainSta, stagePos, calc, stageInterval, generationInterval, generationIndex, 0);
}
