#include "headers/main.h"
#include "headers/levelstaging.h"
#include "aes128cbc/aes.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <sstream>
#include <string>
#include <string.h>
#include <bits/stdc++.h> 

#define DEBUG_PARTICLES 0
#define DEBUG_ULTIMATE 0
#define DEBUG_RANDOM_MOVEMENT 0

bool immortal = false;
bool ultimate = false;
int playerMoveDiagSpeed = sqrt(pow(playerMoveSpeed, 2)/4);

//timing intervals
long playerShootInterval;
long xpInterval;
long ballShootInterval;
long generationInterval;
long stageInterval;
long playerDamageInterval;
long ultimateInterval;

int ultStyle = 1;
std::size_t generationIndex = 0;

Stage stage;
Timer ti;
Obj obj;
Pos pos;
InitPos initPos;
engine eng;
stats mainSta;

//roundkey vector
std::vector<std::vector<std::vector<unsigned char>>> roundKeys = aes::expandKey(cryptKey);


//Function that erases all particles that are outside of the game frame
void cleanAssets(bool cleanEnemies) {
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

//Function that clears the stage from all enemies
void clearStage() {
        obj.enemies.clear(); 
        pos.enemies.clear();
        mainSta.enemyHealth.clear();
        mainSta.exploded.clear();
        mainSta.enemyType.clear();
        pos.enemyVelocity.clear();
}

//Function that clears all particles from display
void clearParticles() {
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

//Function that explodes enemies if their health is zero
void explode(int index) {
    if(ti.getTime() - mainSta.exploded[index][2] >= explosionEffectDelay) {
        mainSta.exploded[index][1]++;
        mainSta.exploded[index][2] = ti.getTime();
    }
    switch (mainSta.exploded[index][1])
    {
    case 1:
        obj.exp.setTexture(obj.exp1Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 2:
        obj.exp.setTexture(obj.exp2Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 3:
        obj.exp.setTexture(obj.exp3Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;
        
    case 4:
        obj.exp.setTexture(obj.exp4Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 5:
        obj.exp.setTexture(obj.exp5Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 6:
        obj.exp.setTexture(obj.exp6Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 7:
        obj.exp.setTexture(obj.exp7Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 8:
        obj.exp.setTexture(obj.exp8Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 9:
        obj.exp.setTexture(obj.exp9Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 10:
        obj.exp.setTexture(obj.exp10Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 11:
        obj.exp.setTexture(obj.exp11Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 12:
        obj.exp.setTexture(obj.exp12Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 13:
        obj.exp.setTexture(obj.exp13Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 14:
        obj.exp.setTexture(obj.exp14Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 15:
        obj.exp.setTexture(obj.exp15Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 16:
        obj.exp.setTexture(obj.exp16Tex);
        eng.drawObject(obj.exp, pos.enemies[index][0], pos.enemies[index][1]);
        break;
        
    case 17:
        mainSta.exploded[index][0] = true;        
        break;

    default:
        break;
    }
}

//Function for drawing default sprites in every frame such as healthbar, ultimate status, background, enemies etc
void drawDefault() {
    for(std::size_t i = 0; i < obj.enemies.size(); i++) {
        if(mainSta.enemyHealth[i] > 0) eng.drawObject(obj.enemies[i], pos.enemies[i][0], pos.enemies[i][1]);
        else if(!mainSta.exploded[i][0]) explode(i);
        
        
    }
    
    eng.drawObject(obj.stats, pos.statsPos[0], pos.statsPos[1]);
    obj.updateBars(mainSta.health, mainSta.power);
    initPos.updateBarY(pos, mainSta.health, mainSta.power);
    eng.drawRectangle(obj.healthbar, pos.healthBar[0], pos.healthBar[1]);
    eng.drawRectangle(obj.powerbar, pos.powerBar[0], pos.powerBar[1]);    
}

/* movement funnctions */

//Move object forward
void moveF() {
    pos.starship[1]-=playerMoveSpeed;
    pos.starshipCore[1]-=playerMoveSpeed;
}

//Move object front leftwards
void moveFL() {
    pos.starship[0]-=playerMoveDiagSpeed; pos.starship[1]-=playerMoveDiagSpeed;
    pos.starshipCore[0]-=playerMoveDiagSpeed; pos.starshipCore[1]-=playerMoveDiagSpeed;
}
    
//Move object front rightwards
void moveFR() {
    pos.starship[0]+=playerMoveDiagSpeed; pos.starship[1]-=playerMoveDiagSpeed;
    pos.starshipCore[0]+=playerMoveDiagSpeed; pos.starshipCore[1]-=playerMoveDiagSpeed;
}

//Move object backwards
void moveB() {
    pos.starship[1]+=playerMoveSpeed;
    pos.starshipCore[1]+=playerMoveSpeed;
}

//Move object backwards left
void moveBL() {
    pos.starship[0]-=playerMoveDiagSpeed, pos.starship[1]+=playerMoveDiagSpeed;
    pos.starshipCore[0]-=playerMoveDiagSpeed, pos.starshipCore[1]+=playerMoveDiagSpeed;
}

//Move object backwards rightwards
void moveBR() {
    pos.starship[0]+=playerMoveDiagSpeed; pos.starship[1]+=playerMoveDiagSpeed;
    pos.starshipCore[0]+=playerMoveDiagSpeed; pos.starshipCore[1]+=playerMoveDiagSpeed;
}

//Move object rightwards
void moveR() {
    pos.starship[0]+=playerMoveSpeed;
    pos.starshipCore[0]+=playerMoveSpeed;
}

//Move object leftwards
void moveL() {
    pos.starship[0]-=playerMoveSpeed;
    pos.starshipCore[0]-=playerMoveSpeed;
}

//Function that draws new particles for shooting
void generateParticles() {
    if(ti.getTime() - playerShootInterval >= playerShootDelay) {
        obj.shootingParticles.push_back(obj.shooting_particle);
        obj.shootingParticles.push_back(obj.shooting_particle);
        obj.shootingParticles.push_back(obj.shooting_particle);
        obj.shootingParticles.push_back(obj.shooting_particle);
        initPos.initPlayerShooting(pos);
        playerShootInterval = ti.getTime();
    }
}

//Function that draws all kind of particles
void drawParticles() {

    //player's laser particles
    for(std::size_t i = 0; i < obj.shootingParticles.size(); i++) {
        eng.drawObject(obj.shootingParticles[i], pos.shootingParticlePos[i][0], pos.shootingParticlePos[i][1]);
    }

    //enemy rhombparticles 
    for(std::size_t i = 0; i < obj.rhombParticles.size(); i++) eng.drawObject(obj.rhombParticles[i], pos.particlePos[i][0], pos.particlePos[i][1]),
        eng.drawCircle(obj.particleCoreVector[i], pos.particleCorePos[i][0], pos.particleCorePos[i][1]);

    //enemy fireballs
    for(std::size_t i = 0; i < obj.balls.size(); i++) {
        eng.drawObject(obj.balls[i], pos.ballPos[i][0], pos.ballPos[i][1]);
        eng.drawRectangle(obj.ballCoreVector[i], pos.ballCorePos[i][0], pos.ballCorePos[i][1]);
    }
}

//Function that checks to shoot or use ultimate
void checkShootingStyle() {
    if((mainSta.power == 100 && sf::Keyboard::isKeyPressed(sf::Keyboard::X)) || ultimate == true) {
        ultimate = true;
        if(!DEBUG_ULTIMATE) mainSta.power = 0;
        if(ti.getTime() - ultimateInterval < ultimateTime) {
            immortal = true;
            switch (ultStyle)
            {
                case 1:
                    eng.drawObject(obj.ultimate1, pos.ultimate[0], pos.ultimate[1]);
                    ultStyle++;
                    break;
                case 2:
                    eng.drawObject(obj.ultimate2, pos.ultimate[0], pos.ultimate[1]);
                    ultStyle++;
                    break;
                case 3:
                    eng.drawObject(obj.ultimate3, pos.ultimate[0], pos.ultimate[1]);
                    ultStyle = 1;
                    break;
                default:
                    break;
            }
        }

        else if(!DEBUG_ULTIMATE) immortal = false;
        else ultimate = false;        
        
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) generateParticles();
}

//Function that initialises game to start from stage 0
void initZero() {
    clearStage(); 
    ultimate = false;
    mainSta = stats();
    clearParticles();
    mainSta.level = 1;
    mainSta.stage = 0;
    pos.backgroundPos[0] = 0;
    pos.backgroundPos[1] = -5400;
    stage.initL1S0(obj, mainSta, pos);
    stageInterval = ti.getTime(); 
}

//Function that checks if GAMEDATA file exists
bool is_gamedata() {
    std::ifstream isFile("GAMEDATA");
    if(!isFile.is_open()) return false;
    else return true;
}

//Function that return unencrypted string for GAMEDATA file
void makeScoreData() {
    time_t timEpoch = time(NULL);
    tm* localTime = localtime(&timEpoch);

    std::string data = "{time='" + std::to_string(localTime->tm_hour) + ":" + std::to_string(localTime->tm_min + 1) + "', ";
    data += "date='" + std::to_string(localTime->tm_year + 1900) + "/" + std::to_string(localTime->tm_mon + 1)  + "/" + std::to_string(localTime->tm_mday) + "', ";
    data += "score='" + std::to_string(mainSta.xp) + "'}";

    std::vector<std::vector<std::vector<unsigned char>>> mesBlocks = aes::getMessageBlocks(data);

    bool addSpace = is_gamedata();

    std::ofstream scoreFile;
    scoreFile.open("GAMEDATA", std::ios_base::app);
    if(addSpace) scoreFile << "\n" + aes::encrypt(roundKeys, mesBlocks);
    else scoreFile << aes::encrypt(roundKeys, mesBlocks);
    scoreFile.close();

}

//Function that shows death message
void deadScreen() {
    makeScoreData();

    float selX = pos.deadSelector[0];

    //loop for death screen
    while (eng.running())
    {
        if(eng.pollevent()) {
            if(eng.getEvent() == sf::Event::Closed) {
                eng.close();
                break;
            }

            if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::D || eng.getKey() == sf::Keyboard::Right)) {
                if(selX > pos.menuselector[0]) selX -= pos.nextSel[0];
                else selX+=pos.nextSel[0];
            }
            else if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::A || eng.getKey() == sf::Keyboard::Left)) {
                if(selX > pos.menuselector[0]) selX-=pos.nextSel[0];
                else selX+=pos.nextSel[0];
                
            }

            if(eng.getEvent() == sf::Event::KeyPressed && eng.getKey() == sf::Keyboard::Enter) {
                if(selX == pos.deadSelector[0]) {
                    initZero();
                    break;
                }
                if(selX == pos.deadSelector[0] + pos.nextSel[0]) eng.close();
            }
        }

        eng.clear();
        eng.drawObject(obj.deadScreen, pos.deadScreen[0], pos.deadScreen[1]);
        eng.drawObject(obj.deadSelector, selX, pos.deadSelector[1]);
        eng.render();
    }
    
}

//Function that checks for user movement
void handleUserMovement() {
    //forward
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && pos.starship[1] > minPosY) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] > minPosX) moveFL();
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] < maxPosX) moveFR();
        else moveF();

    }
    
    //backwards
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && pos.starship[1] < maxPosY) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] > minPosX) moveBL();
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && pos.starship[0] < maxPosX) moveBR();
        else moveB();
    }

    //rightwards
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && pos.starship[0] < maxPosX) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && pos.starship[1] > minPosY) moveFR();
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && pos.starship[1] < maxPosY) moveBR();
        else moveR();
    }

    //leftwards
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && pos.starship[0] > minPosX) {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && pos.starship[1] > minPosY) moveFL();
        else if((sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && pos.starship[1] < maxPosY) moveBL();
        else moveL();
    }
}

//Function that handles all kind of events
void handleEvents() {
    while (eng.pollevent()) {
        //closing the program
        if(eng.getEvent() == sf::Event::Closed) eng.close();
        if(eng.getEvent() == sf::Event::KeyPressed && eng.getKey() == sf::Keyboard::Escape){

            //pause loop
            float selY = pos.menuselector[1];
            while (eng.running())
            {   
                if(eng.pollevent()) {
                    if(eng.getEvent() == sf::Event::KeyPressed && eng.getKey() == sf::Keyboard::Escape) break;
                    if(eng.getEvent() == sf::Event::Closed) eng.close();


                    /* pause menu contains
                        resume
                        restart
                        quit */
                    if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::S || eng.getKey() == sf::Keyboard::Down)) {
                        if(selY > pos.menuselector[1] + pos.nextSel[1]) selY = pos.menuselector[1];
                        else selY+=pos.nextSel[1];
                        
                    }
                    else if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::W || eng.getKey() == sf::Keyboard::Up)) {
                        if(selY == pos.menuselector[1]) selY=pos.menuselector[1] + 2*pos.nextSel[1];
                        else selY-=pos.nextSel[1];
                        
                    }

                    if(eng.getEvent() == sf::Event::KeyPressed && eng.getKey() == sf::Keyboard::Enter) {
                        if(selY == pos.menuselector[1]) break;
                        if(selY == pos.menuselector[1] + pos.nextSel[1]) { 
                            initZero(); 
                            break;
                        }
                        if(selY == pos.menuselector[1] + 2*pos.nextSel[1]) {
                            eng.close();
                            makeScoreData();
                            break;
                        }
                    }
                }

                eng.clear();
                eng.drawObject(obj.pausemenu, pos.menu[0], pos.menu[1]);
                eng.drawObject(obj.selector, pos.menuselector[0], selY);
                eng.render();
            }
        }
    }
}

//Function that gives player xp and power for killing enemies
void enemyDestructionGains(int index) {
        /*  0 = small enemy
            1 = medium enemy
            2 = big enemy
            3 = boss enemy */

    if(!ultimate) mainSta.power += mainSta.powerGains[mainSta.enemyType[index]], mainSta.xp += mainSta.powerGains[mainSta.enemyType[index]]*50;
    else mainSta.xp += mainSta.powerGains[mainSta.enemyType[index]]*50;
}

//Function that destroys particles and gives player xp
void particleDestruction(int index, int type) {
    switch (type)
    {   
        /*  
            0 is balls
            1 is rhomb particles
        */
        case 0:
            obj.balls.erase(obj.balls.begin() + index);
            obj.ballCoreVector.erase(obj.ballCoreVector.begin() + index);
            pos.ballCorePos.erase(pos.ballCorePos.begin() + index);
            pos.ballPos.erase(pos.ballPos.begin() + index);
            pos.ballVelocity.erase(pos.ballVelocity.begin()+index);
            mainSta.xp += mainSta.xpGainFromParticles;
            break;
        
        case 1:
            obj.rhombParticles.erase(obj.rhombParticles.begin() + index);
            obj.particleCoreVector.erase(obj.particleCoreVector.begin() + index);
            pos.particleCorePos.erase(pos.particleCorePos.begin() + index);
            pos.particlePos.erase(pos.particlePos.begin() + index);
            pos.particleVelocity.erase(pos.particleVelocity.begin() + index);
            mainSta.xp += mainSta.xpGainFromParticles;
        default:
            break;
    }
}

//Function that checks for any collisions
void collisions() {

    //player laser particle collision with enemies
    for(std::size_t i = 0; i < obj.enemies.size(); i++) {
        for(std::size_t ii = 0; ii < obj.shootingParticles.size(); ii++) {
            if(eng.collision(obj.enemies[i], obj.shootingParticles[ii], true) && mainSta.enemyHealth[i] > 0) {
                mainSta.enemyHealth[i] -= laserParticleDamage;
                if(mainSta.enemyHealth[i] <= 0 && !mainSta.exploded[i][0]) enemyDestructionGains(i);
            }
        }
    }

    //player collision with balls
    for(sf::RectangleShape rec : obj.ballCoreVector) {
        if(eng.collisionRec(rec, obj.starshipCore, true) && ti.getTime() - playerDamageInterval >= damageDelay) {
            if(!immortal) mainSta.health -= ballDamage;
            if(mainSta.health < 0) mainSta.health = 0; 
            playerDamageInterval = ti.getTime();
        }
    }

    //player collision with rhomb particles
    for(std::size_t i = 0; i < obj.rhombParticles.size(); i++) {
        if(eng.collisionCirRec(obj.starshipCore, obj.particleCoreVector[i]) && ti.getTime() - playerDamageInterval >= damageDelay) {
            if(!immortal) mainSta.health -= particleDamage;
            if(mainSta.health < 0) mainSta.health = 0; 
            playerDamageInterval = ti.getTime();
        }
    }

    /* ultimate collisions */

    //with balls
    for(std::size_t i = 0; i < obj.ballCoreVector.size(); i++) {
        if(eng.collisionRecSpr(obj.ballCoreVector[i], obj.ultimate1, ultimate) || eng.collisionRecSpr(obj.ballCoreVector[i], obj.ultimate2, ultimate) || eng.collisionRecSpr(obj.ballCoreVector[i], obj.ultimate3, ultimate)) 
            particleDestruction(i, 0);
        
    }

    //with rhomb particles
    for(std::size_t i = 0; i < obj.particleCoreVector.size(); i++) {
        if(eng.collisionCirSpr(obj.ultimate1, obj.particleCoreVector[i], ultimate) || eng.collisionCirSpr(obj.ultimate2, obj.particleCoreVector[i], ultimate) || eng.collisionCirSpr(obj.ultimate3, obj.particleCoreVector[i], ultimate))
            particleDestruction(i, 1);
    }

    //with enemies
    for(std::size_t i = 0; i < obj.enemies.size(); i++) {
        if((eng.collision(obj.enemies[i], obj.ultimate1, ultimate) || eng.collision(obj.enemies[i], obj.ultimate2, ultimate) || eng.collision(obj.enemies[i], obj.ultimate3, ultimate)) &&
        mainSta.enemyHealth[i] > 0) {
            if(mainSta.enemyType[i] == 0) mainSta.enemyHealth[i] = 0;
            else if(mainSta.enemyType[i] == 1) mainSta.enemyHealth[i] -= laserParticleDamage*5;
            if(mainSta.enemyHealth[i] <= 0 && !mainSta.exploded[i][0]) enemyDestructionGains(i);
        }
    }

    if(mainSta.power > 100) mainSta.power = 100;
}

//Function that displays main menu
void mainMenu() {
    float selY = pos.menuselector[1];
    while (eng.running()) {

        eng.clear();
        eng.drawObject(obj.mainmenu, pos.menu[0], pos.menu[1]);
        eng.drawObject(obj.selector, pos.menuselector[0], selY);
        eng.render();

        if(eng.pollevent()) {
            if(eng.getEvent() == sf::Event::Closed) {
                eng.close();
                break;
            }

            if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::S || eng.getKey() == sf::Keyboard::Down)) {
                if(selY > pos.menuselector[1]) selY -= pos.nextSel[1];
                else selY+=pos.nextSel[1];
            }
            else if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::W || eng.getKey() == sf::Keyboard::Up)) {
                if(selY == pos.menuselector[1]) selY+=pos.nextSel[1];
                else selY-=pos.nextSel[1];
                
            }

            if(eng.getEvent() == sf::Event::KeyPressed && eng.getKey() == sf::Keyboard::Enter) {
                if(selY == pos.menuselector[1]) { 
                    initZero();
                    break;
                }
                if(selY == pos.menuselector[1] + pos.nextSel[1]) eng.close();
            }
        }
    }
}

//Function that sets player score(xp) to string
void getScoreText(sf::Text& scoreTxt, std::vector<float>& scorePos, int& scoreVal) {
    char score[strlen(std::to_string(scoreVal).c_str())];
    strcpy(score, std::to_string(scoreVal).c_str());

    char des[7] = {'0', '0', '0', '0', '0', '0', '0'};
    for(int i = strlen(std::to_string(scoreVal).c_str()) - 1, y = 6; i >= 0; i--, y--)des[y] = score[i];
    scoreTxt.setString(des);
    eng.drawText(scoreTxt, scorePos[0], scorePos[1]);

} 

//Function that gets local high score from GAMEDATA file
int getHighScore() {
    if(!is_gamedata) return 0;
    else {
        std::ifstream gamedata("GAMEDATA");
        std::vector<std::string> data;
        std::vector<int> highScore;
        std::string temp;
        while (std::getline(gamedata, temp)) data.emplace_back(aes::decrypt(roundKeys, temp));

        for(std::string& str : data) {
            std::cout << str << std::endl;
            std::size_t tagPos = str.find("score");
            std::string scoreStr;
            for(std::size_t i = tagPos + 7; str[i] != (int)39; i++) scoreStr+=str[i];
            highScore.push_back(std::stoi(scoreStr));
        }   
        return *std::max_element(highScore.begin(), highScore.end());
    }
}

int main() {
    if(!is_gamedata()) makeScoreData();
    int highScore = getHighScore();

    playerShootInterval = ti.getTime();
    xpInterval = ti.getTime();
    ballShootInterval = ti.getTime();
    generationInterval = ti.getTime();
    playerDamageInterval = ti.getTime();
    stage.initL1S0(obj, mainSta, pos);
    if(DEBUG_ULTIMATE) mainSta.power = 100, std::cout << "test" << std::endl;

    // main loop for each frame
    while (eng.running())
    {   
        if(mainSta.health <= 0) deadScreen();

        eng.clear();
        eng.drawObject(obj.background1, pos.backgroundPos[0], pos.backgroundPos[1]);

        handleUserMovement();

        if(!ultimate) ultimateInterval = ti.getTime();
        initPos.updatePlayer(pos);
        checkShootingStyle();
        drawParticles();

        //switch for enemies at current level
        switch (mainSta.level)
        {
            //main menu
            case 0:
                mainMenu();
                break;

            //level 1
            case 1:
                //stage 0

                if(ti.getTime() - stageInterval >= stageDelay && mainSta.stage == 0) {
                    obj.exp.setOrigin(0.f, 0.f);
                    if(!initPos.initL1S0(pos)) stage.L1S0attack(mainSta, obj, pos, generationInterval, generationIndex);
                    cleanAssets(false);

                    collisions();
                    bool nextStage = true;
                    for(std::size_t i = 0; i < mainSta.enemyHealth.size(); i++) if(mainSta.enemyHealth[i] > 0 || !mainSta.exploded[i][0]) nextStage = false; 

                    if(nextStage) mainSta.stage++, stageInterval = ti.getTime(), clearStage(), stage.initL1S1(obj, mainSta, pos), generationIndex = 0;
                }

                //stage 1
                if(ti.getTime() - stageInterval >= stageDelay && mainSta.stage == 1) {

                    if(initPos.initL1S1(pos))
                        stage.L1S1attack(mainSta, obj, pos, generationInterval);
                    cleanAssets(true);

                    collisions();
                    bool nextStage = true;
                    for(std::size_t i = 0; i < mainSta.enemyHealth.size(); i++) 
                        if(mainSta.enemyHealth[i] > 0 || !mainSta.exploded[i][0]) nextStage = false; 

                    if(nextStage) mainSta.stage++, stageInterval = ti.getTime(), clearStage(), stage.initL1S2(obj, mainSta, pos), generationIndex = 0;
                    
                }

                //stage 2
                if(ti.getTime() - stageInterval >= stageDelay && mainSta.stage == 2) {
                    
                    if(!initPos.initL1S2(pos)) 
                        stage.L1S2attack(obj, mainSta, pos, generationInterval, generationIndex);

                    collisions();

                    cleanAssets(false);

                    bool nextStage = true;
                    for(std::size_t i = 0; i < mainSta.enemyHealth.size(); i++) if(mainSta.enemyHealth[i] > 0 || !mainSta.exploded[i][0]) nextStage = false; 

                    if(nextStage) mainSta.stage++, stageInterval = ti.getTime(), clearStage(), stage.initL1S3(obj, mainSta, pos), generationIndex = 0;
                    
                } 

                //stage 3
                if(ti.getTime() - stageInterval >= stageDelay && mainSta.stage == 3) {
                    obj.exp.setOrigin(25.f, 25.f);
                    if(!initPos.initL1S3(pos))
                        if(!initPos.updateL1S3(pos, mainSta)) stage.L1S3attack(obj, mainSta, pos, generationInterval, generationIndex, initPos);

                    collisions();
                    cleanAssets(false);

                    bool nextStage = true;
                    for(std::size_t i = 0; i < mainSta.enemyHealth.size(); i++) if(mainSta.enemyHealth[i] > 0 || !mainSta.exploded[i][0]) nextStage = false; 

                    if(nextStage) mainSta.stage++, stageInterval = ti.getTime(), clearStage(), generationIndex = 0;
                }

                drawDefault();
                eng.drawObject(obj.starship, pos.starship[0], pos.starship[1]);
                eng.drawRectangle(obj.starshipCore, pos.starshipCore[0], pos.starshipCore[1]);

                //nostage
                if(ti.getTime() - stageInterval >= stageDelay && mainSta.stage == 4) 
                    eng.drawObject(obj.nostage, pos.nostagePos[0], pos.nostagePos[1]);
                
                
                
                break;

            case 2:
                break;
                
            default:
                break;
        }

        if(ti.getTime() - xpInterval >= xpDelay) mainSta.xp++, xpInterval = ti.getTime();
        initPos.updateAttack(pos);
        if(DEBUG_PARTICLES) 
           std::cout << "Balls: " + std::to_string(obj.balls.size()) + "/Core: " + std::to_string(obj.ballCoreVector.size()) + "/Vel: " + std::to_string(pos.ballVelocity.size()) + "/Pos: " + std::to_string(pos.ballPos.size()) + "/CorePos: " + std::to_string(pos.ballCorePos.size()) << std::endl;
        
        if(DEBUG_RANDOM_MOVEMENT) {
            for(std::size_t i = 0; i < pos.newEnemyPos.size(); i++) {
                std::cout << "new enemy pos: " + std::to_string(pos.newEnemyPos[i][0]) + "/" + std::to_string(pos.newEnemyPos[i][1]) << std::endl;
                std::cout << "velocity: " + std::to_string(pos.enemyVelocity[i][0]) + "/" + std::to_string(pos.enemyVelocity[i][1]) << std::endl;
                std::cout << "current enemy pos: " + std::to_string(pos.enemies[i][0]) + "/" + std::to_string(pos.enemies[i][1]) << std::endl;
                std::cout << "new size: " + std::to_string(pos.newEnemyPos.size()) + "/velo size: " + std::to_string(pos.enemyVelocity.size()) + "/pos size: " + std::to_string(pos.enemies.size()) << std::endl;
                std::cout << std::endl;
            }
            
        }
        getScoreText(obj.score, pos.scorePos, mainSta.xp);
        getScoreText(obj.highScore, pos.highScorePos, highScore);
        handleEvents();

        eng.render();
        pos.backgroundPos[0] += pos.backgroundVelocity[0];
        pos.backgroundPos[1] += pos.backgroundVelocity[1];
    }

    return 0;
}
