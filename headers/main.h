#ifndef MAIN_H
#define MAIN_H
#define PI 3.14159265
#include <string>

//player space in game
#define minPosX 0
#define minPosY 0
#define maxPosX 550
#define maxPosY 550

//window
#define windowWidth 800
#define windowHeight 600
#define windowTitle "super game :DDD!"

//game
#define maxHealth 100
#define maxPower 100
#define playerMoveSpeed 7.5
#define laserParticleSpeed 20
#define laserParticleDamage 2
#define particleSpeed 3 //pixels per frame
#define enemyMoveSpeed 3.3
#define enemyRotationSpeed 3 //degrees per frame
#define enemyRotationAttackFrq 12 //times in 360 degrees

//delays ms
#define damageDelay 500 
#define playerShootDelay 50 
#define ballSingleAttackDelay 200
#define ballMultiAttackDelay 800
#define ballFlowerAttackDelay 55
#define xpDelay 300
#define particleRingDelay 500
#define stageDelay 500
#define ultimateTime 5000
#define explosionEffectDelay 17

//enemy damage to player
#define ballDamage 20 //hp
#define particleDamage 20

//key for encrypting high score data
#define cryptKey "3:&-+<4dB!,&]Ha:"

 


#endif