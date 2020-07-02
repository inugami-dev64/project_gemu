#include "headers/gameobjects.h"
#include <iostream>


Obj::Obj() {
    /*init textures */
    dejavu.loadFromFile("res/fonts/dejavu.ttf");

    //ui related
    this->background1Tex.loadFromFile("res/background_demo.tga");
    this->statsTex.loadFromFile("res/stats.tga");
    this->mainmenuTex.loadFromFile("res/mainmenu.tga");
    this->pausemenuTex.loadFromFile("res/pause.tga");
    this->deadScreenTex.loadFromFile("res/youdead.tga");
    this->selectorTex.loadFromFile("res/selector.tga");
    this->deadSelectorTex.loadFromFile("res/deadselector.tga");
    this->nostageTex.loadFromFile("res/nostage.tga");

    //player
    this->starshipTex.loadFromFile("res/starship.tga");
    this->ultimate1Tex.loadFromFile("res/ultimate.tga");
    this->ultimate2Tex.loadFromFile("res/ultimate2.tga");
    this->ultimate3Tex.loadFromFile("res/ultimate3.tga");
    this->shooting_particlesTex.loadFromFile("res/starship_particle.tga");

    //enemies
    this->smallEnemyTex.loadFromFile("res/enemy2.tga");
    this->mediumEnemyTex.loadFromFile("res/enemy1.tga");
    this->shurikenEnemyTex.loadFromFile("res/shuriken_enemy.tga");

    //enemies attack
    this->fireballAttackTex.loadFromFile("res/fireball.tga");
    this->neonballAttackTex.loadFromFile("res/neonball.tga");
    this->rubyballAttackTex.loadFromFile("res/rubyball.tga");
    this->blueParticleAttackTex.loadFromFile("res/blue_particle.tga");
    this->purpleParticleAttackTex.loadFromFile("res/purple_particle.tga");
    this->goldParticleAttackTex.loadFromFile("res/gold_particle.tga");

    //explosions
    this->exp1Tex.loadFromFile("res/explosions/exp1.tga");
    this->exp2Tex.loadFromFile("res/explosions/exp2.tga");
    this->exp3Tex.loadFromFile("res/explosions/exp3.tga");
    this->exp4Tex.loadFromFile("res/explosions/exp4.tga");
    this->exp5Tex.loadFromFile("res/explosions/exp5.tga");
    this->exp6Tex.loadFromFile("res/explosions/exp6.tga");
    this->exp7Tex.loadFromFile("res/explosions/exp7.tga");
    this->exp8Tex.loadFromFile("res/explosions/exp8.tga");
    this->exp9Tex.loadFromFile("res/explosions/exp9.tga");
    this->exp10Tex.loadFromFile("res/explosions/exp10.tga");
    this->exp11Tex.loadFromFile("res/explosions/exp11.tga");
    this->exp12Tex.loadFromFile("res/explosions/exp12.tga");
    this->exp13Tex.loadFromFile("res/explosions/exp13.tga");
    this->exp14Tex.loadFromFile("res/explosions/exp14.tga");
    this->exp15Tex.loadFromFile("res/explosions/exp15.tga");
    this->exp16Tex.loadFromFile("res/explosions/exp16.tga");


    /*init sprites */
    this->score.setFont(dejavu);
    this->highScore.setFont(dejavu);
    this->score.setCharacterSize(15);
    this->highScore.setCharacterSize(15);
    this->score.setStyle(sf::Text::Bold);
    this->highScore.setStyle(sf::Text::Bold);

    //ui related
    this->background1.setTexture(background1Tex);
    this->stats.setTexture(statsTex);
    this->mainmenu.setTexture(mainmenuTex);
    this->pausemenu.setTexture(pausemenuTex);
    this->deadScreen.setTexture(deadScreenTex);
    this->selector.setTexture(selectorTex);
    this->deadSelector.setTexture(deadSelectorTex);
    this->nostage.setTexture(nostageTex);

    //player
    this->starship.setTexture(starshipTex);
    this->starshipCore.setSize(sf::Vector2f(20, 20));
    this->starshipCore.setFillColor(sf::Color(255, 255, 255, 0));
    this->ultimate1.setTexture(ultimate1Tex);
    this->ultimate2.setTexture(ultimate2Tex);
    this->ultimate3.setTexture(ultimate3Tex);

    //player attack
    this->shooting_particle.setTexture(shooting_particlesTex);

    //enemies
    this->smallEnemy.setTexture(smallEnemyTex);
    this->mediumEnemy.setTexture(mediumEnemyTex);
    this->shurikenEnemy.setTexture(shurikenEnemyTex);

    //enemies attack
    this->fireballAttack.setTexture(fireballAttackTex);
    this->neonballAttack.setTexture(neonballAttackTex);
    this->rubyballAttack.setTexture(rubyballAttackTex);
    this->ballCore.setSize(sf::Vector2f(5, 5));
    this->ballCore.setFillColor(sf::Color(255, 255, 255, 0));

    this->blueParticleAttack.setTexture(blueParticleAttackTex);
    this->purpleParticleAttack.setTexture(purpleParticleAttackTex);
    this->goldParticleAttack.setTexture(goldParticleAttackTex);
    this->particleCore.setRadius(3.f);
    this->particleCore.setFillColor(sf::Color(255, 255, 255, 0));

    //explosions

}

//Function that updates healthbar and powerbar stats to display
void Obj::updateBars(int health, int power) {
    this->healthbar.setSize(sf::Vector2f(25, 3.57 * health));
    this->powerbar.setSize(sf::Vector2f(25, 3.57 * power));
    this->healthbar.setFillColor(sf::Color(255, 0, 0, 255));
    this->powerbar.setFillColor(sf::Color(22, 217, 237, 255));
}
