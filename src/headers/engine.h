#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "main.h"
#include "stats.h"

class engine
{
    private:
        sf::RenderWindow *window;
        sf::Event event;
        void initWindow();

    public:
        const bool running();
        const bool pollevent();

        sf::Event::EventType getEvent();

        void close();
        void render();
        void clear();
        void drawObject(sf::Sprite& sprite, float& x_pos, float& y_pos);
        void drawRectangle(sf::RectangleShape& rectangle, float& x_pos, float& y_pos);
        void drawCircle(sf::CircleShape& circle, float& x_pos, float& y_pos);
        void drawText(sf::Text& text, float& x_pos, float& y_pos);
        bool collision(sf::Sprite& sprite1, sf::Sprite& sprite2, bool isDrawn);
        bool collisionRec(sf::RectangleShape& rec1, sf::RectangleShape& rec2, bool isDrawn);
        bool collisionCirRec(sf::RectangleShape& rec, sf::CircleShape& cir);
        bool collisionCirSpr(sf::Sprite& spr, sf::CircleShape& cir, bool isDrawn);
        bool circleCollisionCore(sf::Vector2f circleCentre, sf::Vector2f recPos, float radius, float recSize[2]);
        bool collisionCore(sf::Vector2f pos1, sf::Vector2f pos2, float first[2], float second[2]);
        bool collisionRecSpr(sf::RectangleShape& rec, sf::Sprite& sprite, bool isDrawn); 
        sf::Keyboard::Key getKey();
        sf::Sprite makeSprite(sf::Texture texture);
        engine(/* args */);
        ~engine();
    
};



#endif