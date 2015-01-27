#ifndef ASSET_MANAGER_HPP
#define ASSET_MANAGER_HPP

#include "SFML/Graphics.hpp"
#include "textLogger.hpp"
#include "stringToInt.hpp"

using namespace sf;

class GameAsset{
    public:

    //Constructor initializes all variables to zero.
    GameAsset();

    //Unloads any existing map, then loads the map from fileName
    bool loadTextMap(const char *fileName);  //Map in .txt file format
    bool loadMap(const char *fileName);      //Map in binary file format

    //Unloads any existing character images, then loads images defined in fileName
    bool loadTextCharacterList(const char *fileName);

    //Map image data
    int         textureNumImages;
    int         textureSpriteWidth;
    int         textureSpriteHeight;
    Texture    *textureArray;

    //Map data
    int         mapWidth;
    int         mapHeight;
    int        *mapActiveTextureArray;
    int        *mapTileArray;
    bool       *mapPassableArray;

    //NPC data
    int         npcNumSheetImages;
    int        *npcSpriteWidth;
    int        *npcSpriteHeight;
    int        *npcSheetImageArray;
    int         npcNumNPCs;
    //NPC      *npcArray;

    //Trigger data

    //Character sheet data
    int         sheetNumImages;
    int        *sheetSpriteWidth;
    int        *sheetSpriteHeight;
    Texture    *sheetImageArray;

};

#endif
