#include "assetManager.hpp"
#include <fstream>
#include <iostream>
#include <string>

GameAsset::GameAsset(){
    //Image data
    textureNumImages        = 0;
    textureSpriteWidth      = 0;
    textureSpriteHeight     = 0;
    textureArray            = NULL;

    //Map data
    mapWidth                = 0;
    mapHeight               = 0;
    mapActiveTextureArray   = NULL;
    mapTileArray            = NULL;
    mapPassableArray        = NULL;

    //NPC data
    npcNumSheetImages       = 0;
    npcSpriteWidth          = NULL;
    npcSpriteHeight         = NULL;
    npcSheetImageArray      = NULL;
    npcNumNPCs              = 0;
    //npcArray              = NULL;

    //Character List data
    sheetNumImages      = 0;
    sheetSpriteWidth    = NULL;
    sheetSpriteHeight   = NULL;
    sheetImageArray     = NULL;

}

bool GameAsset::loadTextMap(const char *fileName){

    logText("Opening file: ");
    logText(fileName);
    logText("\n");

    //Remove any existing texture data
    if(textureArray){
        delete[] textureArray;
    }
    textureNumImages    = 0;
    textureSpriteWidth  = 0;
    textureSpriteHeight = 0;

    //Remove any existing map data
    if(mapTileArray){
        delete[] mapTileArray;
    }
    if(mapActiveTextureArray){
        delete[] mapActiveTextureArray;
    }
    if(mapPassableArray){
        delete[] mapPassableArray;
    }
    mapWidth            = 0;
    mapHeight           = 0;



    //Open file
    std::fstream mapFile;
	mapFile.open(fileName, std::fstream::in);

	//Text map contents:
	// number of image files
	// sprite width in pixels
	// sprite height in pixels
	// Image file names number 1 to n
	// map width in tiles
	// map height in tiles
	// [texture id 1 to n, sprite number 1 to n]

	//Make sure the file is open
	if(!mapFile.is_open()){
	    logTextLine("Error: Could not open file.");
        return false;
	}

	//Read number of images to load
	std::string fileData;
	if(mapFile.good()){
        getline(mapFile, fileData);
        textureNumImages = stringToInt(fileData);
	}
	else{
	    logTextLine("\nUnexpected end of file: No number of texture images map file.");
	    mapFile.close();
        return false;
	}

    //Read width and height of tiles
    if(mapFile.good()){
        getline(mapFile, fileData);
        textureSpriteWidth = stringToInt(fileData);
    }
    else{
        logTextLine("\nUnexpected end of file: No sprite width in map file.");
        mapFile.close();
        return false;
	}
    if(mapFile.good()){
        getline(mapFile, fileData);
        textureSpriteHeight = stringToInt(fileData);
    }
    else{
        logTextLine("\nUnexpected end of file: No sprite height in map file.");
        mapFile.close();
        return false;
	}

	//Allocate space for images
    textureArray = new Texture[textureNumImages];

	//Load images
	for(int i = 0; i < textureNumImages; i++){
        if(mapFile.good()){
            //Read filename
            getline(mapFile, fileData);

            //Log name of image file to load
            logText("Texture ");
            logText(i);
            logText(": ");
            logText(fileData.c_str());
            logText("\n");

            //Load texture image
            std::string path = "Textures/";
            textureArray[i].loadFromFile(path.append(fileData));  //Orsakar krash i Windows.			
        }
        else{
            logTextLine("\nUnexpected end of file: No texture image file name in map file.");
            mapFile.close();
            return false;
        }
	}

	//Read map width and height in number of tiles
	if(mapFile.good()){
        getline(mapFile, fileData);
        mapWidth = stringToInt(fileData);
    }
    else{
        logTextLine("\nUnexpected end of file: No map width in map file.");
        mapFile.close();
        return false;
	}
    if(mapFile.good()){
        getline(mapFile, fileData);
        mapHeight = stringToInt(fileData);
    }
    else{
        logTextLine("\nUnexpected end of file: No map height in map file.");
        mapFile.close();
        return false;
	}

	//Allocate space for map
	mapTileArray            = new int[mapWidth*mapHeight];
	mapActiveTextureArray   = new int[mapWidth*mapHeight];

	//Load map
	logTextLine("Loading map data.");
	std::string whitespaces = " \t\f\v\n\r";
	for(int y = 0; y < mapHeight; y++){
	    if(mapFile.good()){
	        //Read one line of tiles
            getline(mapFile, fileData);

            //Parse data
            std::size_t first = 0;
            std::size_t last  = 0;
            for(int x = 0; x < mapWidth; x++){
                //Find texture id
                first = fileData.find_first_not_of(",", first);
                first = fileData.find_first_not_of(whitespaces, first);
                last  = fileData.find_first_of(",", first);

                //Extract texture id
                if(first != std::string::npos){
                    mapActiveTextureArray[x+y*mapWidth] = stringToInt(fileData.substr(first, (last-first)));
                }

                //Prepare for sprite id
                first = last;

                //Find sprite id
                first = fileData.find_first_not_of(",", first);
                first = fileData.find_first_not_of(whitespaces, first);
                last  = fileData.find_first_of(",", first);

                //Extract sprite id
                if(first != std::string::npos){
                    mapTileArray[x+y*mapWidth] = stringToInt(fileData.substr(first, (last-first)));
                }

                //Prepare for next texture id
                first = last;

            }
	    }
	    else{
            logTextLine("\nUnexpected end of file: No map data in map file.");
            mapFile.close();
            return false;
	    }
	}

	//Return successfull loading of map.
    return true;
}

bool GameAsset::loadTextCharacterList(const char *fileName){

    logText("Opening file: ");
    logText(fileName);
    logText("\n");

    //Remove any existing character data
    if(sheetImageArray){
        delete[] sheetImageArray;
    }
    if(sheetSpriteWidth){
        delete[] sheetSpriteWidth;
    }
    if(sheetSpriteHeight){
        delete[] sheetSpriteHeight;
    }
    sheetNumImages = 0;

    //Open file containing image file names
    std::fstream charList;
	charList.open(fileName, std::fstream::in);

    //Character file contents
    // int Number of characters to load
    // spriteWidth
    // spriteHeight
    // image filename

    //Make sure the file is open
	if(!charList.is_open()){
	    logTextLine("Error: Could not open file.");
        return false;
	}

	//Read number of character images to load
	std::string fileData;
	if(charList.good()){
        getline(charList, fileData);
        sheetNumImages = stringToInt(fileData);
	}
	else{
	    logTextLine("\nUnexpected end of file: No number of character images to load.");
	    charList.close();
        return false;
	}

	//Create room for images
	sheetImageArray     = new Texture   [sheetNumImages];
	sheetSpriteWidth    = new int       [sheetNumImages];
	sheetSpriteHeight   = new int       [sheetNumImages];

	//Load images
	for(int i = 0; i < sheetNumImages; i++){
        if(charList.good()){
            //Read sprite width
            getline(charList, fileData);
            sheetSpriteWidth[i] = stringToInt(fileData);
        }
        else{
            logTextLine("\nUnexpected end of file: No sprite width.");
            charList.close();
            return false;
        }

        if(charList.good()){
            //Read sprite height
            getline(charList, fileData);
            sheetSpriteHeight[i] = stringToInt(fileData);
        }
        else{
            logTextLine("\nUnexpected end of file: No sprite height.");
            charList.close();
            return false;
        }

        if(charList.good()){
            //Read image file name
            getline(charList, fileData);

            //Load image
            std::string path = "Textures/";
            sheetImageArray[i].loadFromFile(path.append(fileData));

            logText("Sprite ");
            logText(i);
            logText(": ");
            logText(fileData.c_str());
            logText("\n");
        }
        else{
            logTextLine("\nUnexpected end of file: No sprite image name.");
            charList.close();
            return false;
        }
	}

	return true;
}


