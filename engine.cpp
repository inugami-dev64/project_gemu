#include "headers/engine.h"
#include "headers/levelstaging.h"
#include <cmath>

Stage engSta;

// Function that intializes the window
void engine::initWindow() {
    this->window = nullptr;
    this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), windowTitle, sf::Style::Titlebar | sf::Style::Close);
    this->window->setVerticalSyncEnabled(true);
    this->window->setFramerateLimit(60);
}

//Function that checks if the game is running
const bool engine::running() {
    return this->window->isOpen();
}

//Function that checks for any events
const bool engine::pollevent() {
    return this->window->pollEvent(this->event);
} 

//Function that gets the event data
sf::Event::EventType engine::getEvent() {
    return this->event.type;
}


//Function that draws a sprite
void engine::drawObject(sf::Sprite& sprite, float& x_pos, float& y_pos) {
    sprite.setPosition(x_pos, y_pos);
    this->window->draw(sprite);
}

//Function that draws a rectangle 
void engine::drawRectangle(sf::RectangleShape& rectangle, float& x_pos, float& y_pos) {
    rectangle.setPosition(x_pos, y_pos);
    this->window->draw(rectangle);
}

//Function that draws a circle
void engine::drawCircle(sf::CircleShape& circle, float& x_pos, float& y_pos) {
    circle.setPosition(x_pos, y_pos);
    this->window->draw(circle);
}

//Function that draws text
void engine::drawText(sf::Text& text, float& x_pos, float& y_pos) {
    text.setPosition(x_pos, y_pos);
    this->window->draw(text);
}

//Function that renders shaders
void engine::render() {
    this->window->display();
}

//Function that clears display;
void engine::clear() {
    this->window->clear(sf::Color(0, 0, 255, 255));
}

//Function that gets the pressed key
sf::Keyboard::Key engine::getKey() {
    return this->event.key.code;
}

//Function that creates a sprite
sf::Sprite engine::makeSprite(sf::Texture texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture);

    return sprite;
}

//Function that closes the window
void engine::close() {
    this->window->close();
}

//Function that detects collition between 2 sprites
bool engine::collision(sf::Sprite& sprite1, sf::Sprite& sprite2, bool isDrawn) {
    if(isDrawn) {
        sf::Vector2f pos1 = sprite1.getPosition();
        float first[2] = {sprite1.getLocalBounds().width, sprite2.getLocalBounds().height};
        
        sf::Vector2f pos2 = sprite2.getPosition();
        float second[2] = {sprite2.getLocalBounds().width, sprite2.getLocalBounds().height};
        return this->collisionCore(pos1, pos2, first, second);
    }

    else return false;
}

//Function that checks if rectangleshape collides with a sprite
bool engine::collisionRecSpr(sf::RectangleShape& rec, sf::Sprite& sprite, bool isDrawn) {
    if(isDrawn) {
        sf::Vector2f pos1 = rec.getPosition();
        float first[2] = {rec.getLocalBounds().width, rec.getLocalBounds().height};
        
        sf::Vector2f pos2 = sprite.getPosition();
        float second[2] = {sprite.getLocalBounds().width, sprite.getLocalBounds().height};
        return this->collisionCore(pos1, pos2, first, second);
    }

    else return false;
}

//Function that checks if rectangles collide
bool engine::collisionRec(sf::RectangleShape& rec1, sf::RectangleShape& rec2, bool isDrawn) {
    if(isDrawn) {
        sf::Vector2f pos1 = rec1.getPosition();
        float first[2] = {rec1.getLocalBounds().width, rec1.getLocalBounds().height};
        
        sf::Vector2f pos2 = rec2.getPosition();
        float second[2] = {rec2.getLocalBounds().width, rec2.getLocalBounds().height};
        return this->collisionCore(pos1, pos2, first, second);
    }

    else return false;
}

bool engine::circleCollisionCore(sf::Vector2f circleCentre, sf::Vector2f recPos, float radius, float recSize[2]) {
    for(int i = 0; i < 360; i++) {
        std::vector<float> pos(2);
        pos[0] = circleCentre.x + radius*cos(engSta.degToRad(i));
        pos[1] = circleCentre.y + radius*sin(engSta.degToRad(i));

        if((recPos.x < pos[0] && pos[0] < recPos.x + recSize[0]) && (recPos.y < pos[1] && pos[1] < recPos.y + recSize[1])) return true;
        if((circleCentre.x < recPos.x && recPos.x < pos[0]) && (circleCentre.y < recPos.y && recPos.y < pos[1])) return true;
    }

    return false;
}

//Function that check if rectangle collides with circle
bool engine::collisionCirRec(sf::RectangleShape& rec, sf::CircleShape& cir) {
    float radius = cir.getLocalBounds().width/2;
    sf::Vector2f circleCentre = cir.getPosition();
    sf::Vector2f recPos = rec.getPosition();
    float recSize[2] = {rec.getLocalBounds().width, rec.getLocalBounds().height};

    return this->circleCollisionCore(circleCentre, recPos, radius, recSize);
}

//Function that check if rectangle collides with sprite
bool engine::collisionCirSpr(sf::Sprite& spr, sf::CircleShape& cir, bool isDrawn) {
    if(isDrawn) {
        float radius = cir.getLocalBounds().width/2;
        sf::Vector2f circleCentre = cir.getPosition();
        sf::Vector2f sprPos = spr.getPosition();
        float sprSize[2] = {spr.getLocalBounds().width, spr.getLocalBounds().height};

        return this->circleCollisionCore(circleCentre, sprPos, radius, sprSize);
    }

    else
    {
        return false;
    }
    
}

//Function that detects collision with given sizes and coordinates
bool engine::collisionCore(sf::Vector2f pos1, sf::Vector2f pos2, float first[2], float second[2]) {

    if((pos1.x < pos2.x && pos2.x < pos1.x + first[0]) && (pos1.y < pos2.y && pos2.y < pos1.y + first[1])) {
        if((pos1.y + first[1]) > 40 && (pos2.y + second[1]) > 40) return true;
    }
    if((pos2.x < pos1.x && pos1.x < pos2.x + second[0]) && (pos2.y < pos1.y && pos1.y < pos2.y + second[1])) {
        if((pos1.y + first[1]) > 40 && (pos2.y + second[1]) > 40) return true;
    }

    return false;
}

//Constructor
engine::engine(/* args */)
{
    this->window = nullptr;
    this->initWindow();
}

//Destructor
engine::~engine()
{
    delete this->window;
}