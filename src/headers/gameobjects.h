#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include <SFML/Graphics.hpp>
#include "stats.h"

//object class for all possible game objects
class Obj
{   
    private:
        //Fonts
        sf::Font dejavu;

        //ui textures
        sf::Texture background1Tex;
        sf::Texture statsTex;
        sf::Texture mainmenuTex;
        sf::Texture pausemenuTex;
        sf::Texture deadScreenTex;
        sf::Texture deadSelectorTex;
        sf::Texture selectorTex;
        sf::Texture nostageTex;

        //starship related textures
        sf::Texture starshipTex;
        sf::Texture ultimate1Tex;
        sf::Texture ultimate2Tex;
        sf::Texture ultimate3Tex;
        sf::Texture shooting_particlesTex;

        //enemies
        sf::Texture smallEnemyTex;
        sf::Texture mediumEnemyTex;
        sf::Texture shurikenEnemyTex;

        //enemies attack
        sf::Texture fireballAttackTex;
        sf::Texture neonballAttackTex;
        sf::Texture rubyballAttackTex;
        sf::Texture blueParticleAttackTex;
        sf::Texture purpleParticleAttackTex;
        sf::Texture goldParticleAttackTex;

    public:
        //scores
        sf::Text score;
        sf::Text highScore;

        //ui sprites
        sf::Sprite background1;
        sf::Sprite stats;
        sf::RectangleShape healthbar;
        sf::RectangleShape powerbar;
        void updateBars(int health, int power);
        sf::Sprite mainmenu;
        sf::Sprite pausemenu;
        sf::Sprite deadScreen;
        sf::Sprite selector;
        sf::Sprite deadSelector;
        sf::Sprite nostage;
        

        //starship related sprites
        sf::Sprite starship;
        sf::RectangleShape starshipCore;
        sf::Sprite ultimate1;
        sf::Sprite ultimate2;
        sf::Sprite ultimate3;

        //starship shooting particles
        sf::Sprite shooting_particle;
        std::vector<sf::Sprite> shootingParticles;

        //enemies
        sf::Sprite smallEnemy;
        sf::Sprite mediumEnemy;
        sf::Sprite shurikenEnemy;

        std::vector<sf::Sprite> enemies;
        
        //enemies attack
        sf::Sprite fireballAttack;
        sf::Sprite neonballAttack;
        sf::Sprite rubyballAttack;
        sf::RectangleShape ballCore;
        sf::Sprite blueParticleAttack;
        sf::Sprite purpleParticleAttack;
        sf::Sprite goldParticleAttack;
        sf::CircleShape particleCore;

        //attack particles vectors
        std::vector<sf::Sprite> balls;
        std::vector<sf::RectangleShape> ballCoreVector;
        std::vector<sf::Sprite> rhombParticles;
        std::vector<sf::CircleShape> particleCoreVector;

        //explosion effects
        sf::Texture exp1Tex;
        sf::Texture exp2Tex;
        sf::Texture exp3Tex;
        sf::Texture exp4Tex;
        sf::Texture exp5Tex;
        sf::Texture exp6Tex;
        sf::Texture exp7Tex;
        sf::Texture exp8Tex;
        sf::Texture exp9Tex;
        sf::Texture exp10Tex;
        sf::Texture exp11Tex;
        sf::Texture exp12Tex;
        sf::Texture exp13Tex;
        sf::Texture exp14Tex;
        sf::Texture exp15Tex;
        sf::Texture exp16Tex;
        sf::Sprite explosion;
        

    Obj();
};



#endif