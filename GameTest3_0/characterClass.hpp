#ifndef CHARACTER_CLASS_HPP
#define CHARACTER_CLASS_HPP

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "textLogger.hpp"
#include <string>

enum directionEnum{
    Up = 0,
    Down,
    Left,
    Right
};

class GameCharacter{
    public:

    GameCharacter();

    //Name
    std::string name;

    //Movement
    float       posX;
    float       posY;
    bool        moving;
    int         direction;
    float       velocity;

    //Animation
    sf::Clock   timerAnimation;
    sf::Clock   timerIdle;
    int         timeAnimation_ms;
    int         timeIdle_ms;
    int         frameCurrent;

    //Image
    sf::Sprite  sprite;
    int         width;
    int         height;
    bool        flipX;

    void        move(directionEnum dir);

    /********************************************************
    * The Update function handles animation, movement and   *
    * scaling of the character.                             *
    *                                                       *
    * -Updates animation frame if criteria is fullfilled    *
    * -Moves sprite to position posX,posY                   *
    * -Scales to scaleX and scaleY                          *
    *********************************************************/
    void        update(float scaleX, float scaleY);
};

#endif
