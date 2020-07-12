#include "headers/main.h"
#include "headers/levelstaging.h"
#include "../aes128cbc/aes.h"
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
#define DEBUG_ENEMIES 0
#define DEBUG_STAGES 0
#define DEBUG_RANDOM_MOVEMENT 1

bool immortal = false;
bool ultimate = false;

//timing intervals
long playerShootInterval;
long xpInterval;
long ballShootInterval;
long generationInterval;
long stageInterval;
long playerDamageInterval;
long ultimateInterval;
float playerMoveDiagSpeed = sqrt(pow(playerMoveSpeed, 2)/4);

int ultStyle = 1;
std::size_t generationIndex = 0;

Levels lvls;
ManageVectors manage;
Calc calc;
Obj obj;
Pos pos;
StagePos stagePos;
Move move;
engine eng;
Stats mainSta;

//roundkey vector
std::vector<std::vector<std::vector<unsigned char>>> roundKeys = aes::expandKey(cryptKey);

//Function that explodes enemies if their health is zero
void explode(int index) {
    if(calc.getTime() - mainSta.exploded[index][2] >= explosionEffectDelay) {
        mainSta.exploded[index][1]++;
        mainSta.exploded[index][2] = calc.getTime();
    }
    switch (mainSta.exploded[index][1])
    {
    case 1:
        obj.explosion.setTexture(obj.exp1Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 2:
        obj.explosion.setTexture(obj.exp2Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 3:
        obj.explosion.setTexture(obj.exp3Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;
        
    case 4:
        obj.explosion.setTexture(obj.exp4Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 5:
        obj.explosion.setTexture(obj.exp5Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 6:
        obj.explosion.setTexture(obj.exp6Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 7:
        obj.explosion.setTexture(obj.exp7Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 8:
        obj.explosion.setTexture(obj.exp8Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 9:
        obj.explosion.setTexture(obj.exp9Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 10:
        obj.explosion.setTexture(obj.exp10Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 11:
        obj.explosion.setTexture(obj.exp11Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 12:
        obj.explosion.setTexture(obj.exp12Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 13:
        obj.explosion.setTexture(obj.exp13Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 14:
        obj.explosion.setTexture(obj.exp14Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 15:
        obj.explosion.setTexture(obj.exp15Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
        break;

    case 16:
        obj.explosion.setTexture(obj.exp16Tex);
        eng.drawObject(obj.explosion, pos.enemies[index][0], pos.enemies[index][1]);
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
    move.update(pos, mainSta);
    eng.drawRectangle(obj.healthbar, pos.healthBar[0], pos.healthBar[1]);
    eng.drawRectangle(obj.powerbar, pos.powerBar[0], pos.powerBar[1]);    
}

//Function that draws new particles for shooting
void generateParticles() {
    if(calc.getTime() - playerShootInterval >= playerShootDelay) {
        obj.shootingParticles.push_back(obj.shooting_particle);
        obj.shootingParticles.push_back(obj.shooting_particle);
        obj.shootingParticles.push_back(obj.shooting_particle);
        obj.shootingParticles.push_back(obj.shooting_particle);
        move.setPlayerShooting(pos);
        playerShootInterval = calc.getTime();
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
        if(calc.getTime() - ultimateInterval < ultimateTime) {
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

        else if(!DEBUG_ULTIMATE) immortal = false, ultimate = false;
        else ultimate = false;        
        
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) generateParticles();
}

//Function that initialises game to start from stage 0
void initZero() {
    manage.clearStage(pos, obj, mainSta); 
    ultimate = false;
    mainSta = Stats();
    manage.clearParticles(pos, obj);
    mainSta.level = 1;
    mainSta.stage = 0;
    pos.backgroundPos[0] = 0;
    pos.backgroundPos[1] = -5400;
    lvls.lvlOne.initLvl(obj, mainSta, pos, calc);
    stageInterval = calc.getTime(); 
    playerShootInterval = calc.getTime();
    xpInterval = calc.getTime();
    ballShootInterval = calc.getTime();
    generationInterval = calc.getTime();
    playerDamageInterval = calc.getTime();
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
                else selX += pos.nextSel[0];
            }
            else if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::A || eng.getKey() == sf::Keyboard::Left)) {
                if(selX > pos.menuselector[0]) selX-=pos.nextSel[0];
                else selX += pos.nextSel[0];
                
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


                    /*  pause menu contains
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
        if(eng.collisionRec(rec, obj.starshipCore, true) && calc.getTime() - playerDamageInterval >= damageDelay) {
            if(!immortal) mainSta.health -= ballDamage;
            if(mainSta.health < 0) mainSta.health = 0; 
            playerDamageInterval = calc.getTime();
        }
    }

    //player collision with rhomb particles
    for(std::size_t i = 0; i < obj.rhombParticles.size(); i++) {
        if(eng.collisionCirRec(obj.starshipCore, obj.particleCoreVector[i]) && calc.getTime() - playerDamageInterval >= damageDelay) {
            if(!immortal) mainSta.health -= particleDamage;
            if(mainSta.health < 0) mainSta.health = 0; 
            playerDamageInterval = calc.getTime();
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
                else selY += pos.nextSel[1];
            }
            else if(eng.getEvent() == sf::Event::KeyPressed && (eng.getKey() == sf::Keyboard::W || eng.getKey() == sf::Keyboard::Up)) {
                if(selY == pos.menuselector[1]) selY+=pos.nextSel[1];
                else selY -= pos.nextSel[1];
                
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
    if(DEBUG_ULTIMATE) mainSta.power = 100;

    // main loop for each frame
    while (eng.running())
    {   
        if(mainSta.health <= 0) deadScreen();

        eng.clear();
        eng.drawObject(obj.background1, pos.backgroundPos[0], pos.backgroundPos[1]);

        move.handleMovement(pos, playerMoveDiagSpeed);

        if(!ultimate) ultimateInterval = calc.getTime();
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
                lvls.lvlOne.handleLvl(obj, mainSta, pos, calc, stagePos, generationInterval, stageInterval, generationIndex);
                break;

            case 2:
                break;
                
            default:
                break;
        }

        collisions();
        drawDefault();
        eng.drawObject(obj.starship, pos.starship[0], pos.starship[1]);
        eng.drawRectangle(obj.starshipCore, pos.starshipCore[0], pos.starshipCore[1]);

        if(calc.getTime() - xpInterval >= xpDelay) mainSta.xp++, xpInterval = calc.getTime();
        if(DEBUG_PARTICLES) 
           std::cout << "Balls: " + std::to_string(obj.balls.size()) + "/Core: " + std::to_string(obj.ballCoreVector.size()) + "/Vel: " + std::to_string(pos.ballVelocity.size()) + "/Pos: " + std::to_string(pos.ballPos.size()) + "/CorePos: " + std::to_string(pos.ballCorePos.size()) << std::endl;
        
        if(DEBUG_ENEMIES)
            std::cout << "Enemies: " + std::to_string(obj.enemies.size()) + "/Vel: " + std::to_string(pos.enemyVelocity.size()) + "/Pos: " + std::to_string(pos.enemies.size()) + "/CorePos: " << std::endl;

        if(DEBUG_STAGES)
            std::cout << "Stage: " + std::to_string(mainSta.stage) << std::endl;
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
