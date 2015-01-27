#ifndef DIALOGUE_PANEL_HPP
#define DIALOGUE_PANEL_HPP

#include "SFML/Graphics.hpp"

class dialoguePanel{

    sf::Font    font;
    sf::Text    text;
    sf::Sprite  sprite;
    float       posX;
    float       posY;
    int         width;
    int         height;
    int         padding;

};

#endif
