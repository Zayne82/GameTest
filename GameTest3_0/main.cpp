#include "textLogger.hpp"
#include "assetManager.hpp"
#include "configManager.hpp"
#include "characterClass.hpp"
#include "dialoguePanel.hpp"

int main(){
    //Start main
    logTextLine("Program Start", true, true);

    int noll    = 0;
    int ett     = 1;

    bool sant   = true;
    bool falskt = false;

    if(noll){
        logTextLine("noll");
    }
    if(ett){
        logTextLine("ett");
    }
    logText("true = ");
    logText(sant);
    logText("\nfalse = ");
    logText(falskt);
    logText("\n");

    logTextLine("Start function");

    logTextLine("Creating map");
    GameAsset map;
    logTextLine("Creating settings");
    ConfigManager settings;
	
    //Loading map
    logTextLine("Loading map");
    map.loadTextMap("Maps/map1.txt");

    //Loading playable character images
    logTextLine("Loading character images");
    map.loadTextCharacterList("Sprites/CharacterList.txt");

    /********************************************************
    * Create character                                      *
    *********************************************************/
    //Creating character
    logTextLine("Creating character");
    int characterImage = 2;
    GameCharacter character;
    character.name  = "Player";
    character.posX  = 4.0f*map.textureSpriteWidth;
    character.posY  = 4.0f*map.textureSpriteHeight;
    //Check that the character image exists
    if(map.sheetNumImages > characterImage){
        character.sprite.setTexture(map.sheetImageArray[characterImage]);
        character.width  = map.sheetSpriteWidth[characterImage];
        character.height = map.sheetSpriteHeight[characterImage];
    }


    //Loading settings
    logTextLine("Loading settings");
    settings.loadConfigFromFile("settings.txt");

    //Drawing map
    logTextLine("Start graphic rendering.");

    /********************************************************
    * Create Game Window                                    *
    *********************************************************/
    //Window
    bool fullScreen = false;
    sf::RenderWindow    window;

    //Get current desktop video mode
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	//Get video settings from config manager
	switch(settings.winMode){
	case 1:
		//Windowed
		logText("Window mode: Windowed (");
		logText(settings.winX);
        logText("x");
        logText(settings.winY);
        logText(")\n");
        window.create(sf::VideoMode(settings.winX, settings.winY), "Game Test 3.0");
        window.setPosition(sf::Vector2i((videoMode.width/2)-(settings.winX/2),(videoMode.height/2)-(settings.winY/2)));
		break;
	case 2:
		//Fullscreen
		logText("Window mode: Fullscreen (");
		logText(settings.winX);
        logText("x");
        logText(settings.winY);
        logText(")\n");
		window.create(sf::VideoMode(settings.winX, settings.winY), "Game Test 3.0", sf::Style::Fullscreen);
		window.setPosition(sf::Vector2i(0, 0));
		window.setMouseCursorVisible(false);
		fullScreen = true;
		break;
	case 3:
		//Windowed fullscreen
		logText("Window mode: Windowed Fullscreen (");
		logText(videoMode.width);
        logText("x");
        logText(videoMode.height);
        logText(")\n");
		window.create(sf::VideoMode(videoMode.width, videoMode.height), "Game Test 3.0", sf::Style::None);
		window.setPosition(sf::Vector2i(0, 0));
		window.setMouseCursorVisible(false);
		fullScreen = true;
		break;
	default:
		//Windowed
		logText("Window mode: Default (480x480)\n");
		window.create(sf::VideoMode(480, 480), "Game Test 3.0");
		window.setPosition(sf::Vector2i((videoMode.width/2)-240,(videoMode.height/2)-240));
		break;
	}

	//Set vertical sync
	window.setVerticalSyncEnabled(true);

    /********************************************************
    * Event Loop, rendering                                 *
    *********************************************************/

    //Log start event loop
    logTextLine("Eventloop started", true, true);

    //Create sprite to draw map with
    sf::Sprite sprite;

    //Create default scale
    float scale = 3.0f;

    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            // Close window : exit
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)){
                window.close();
            }
            //Switch Fullscreen / Windowed mode
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F && event.key.control)){
                fullScreen = !fullScreen;
                if(fullScreen){
                    //Set fullscreen mode
                    if(settings.winMode == 2){
                        //Fullscreen
                        logText("Toggle window mode: Fullscreen (");
                        logText(settings.winX);
                        logText("x");
                        logText(settings.winY);
                        logText(")\n");
                        window.create(sf::VideoMode(settings.winX, settings.winY), "Game Test 3.0", sf::Style::Fullscreen);
                        window.setPosition(sf::Vector2i(0, 0));
                        window.setMouseCursorVisible(false);
                    }else{
                        //Windowed fullscreen
                        logText("Toggle window mode: Windowed Fullscreen (");
                        logText(videoMode.width);
                        logText("x");
                        logText(videoMode.height);
                        logText(")\n");
                        window.create(sf::VideoMode(videoMode.width, videoMode.height), "Game Test 3.0", sf::Style::None);
                        window.setPosition(sf::Vector2i(0, 0));
                        window.setMouseCursorVisible(false);
                    }
                }else{
                    //Set windowed mode
                    //Windowed
                    logText("Toggle window mode: Windowed (");
                    logText(settings.winX);
                    logText("x");
                    logText(settings.winY);
                    logText(")\n");
                    window.create(sf::VideoMode(settings.winX, settings.winY), "Game Test 3.0");
                    window.setPosition(sf::Vector2i((videoMode.width/2)-(settings.winX/2),(videoMode.height/2)-(settings.winY/2)));
                }
            }

        }
	
        /********************************************************
        * Draw Map                                              *
        *********************************************************/
        // Clear screen
        window.clear();

        // Draw the map
        for(int y = 0; y < map.mapHeight; y++){
            for(int x = 0; x < map.mapWidth; x++){

                //Get sprite ID and active texture
                int spriteID = map.mapTileArray[x+y*map.mapWidth];
                int textureActive = map.mapActiveTextureArray[x+y*map.mapWidth];

                //Set texture image
                sprite.setTexture(map.textureArray[textureActive]);

                //Set sub rectangle
                sprite.setTextureRect(sf::IntRect(
                                                  (spriteID%(map.textureArray[textureActive].getSize().x/map.textureSpriteWidth))*map.textureSpriteWidth,
                                                  (spriteID/(map.textureArray[textureActive].getSize().x/map.textureSpriteWidth))*map.textureSpriteHeight,
                                                  map.textureSpriteWidth,
                                                  map.textureSpriteHeight
                                                  ));
                //Set position
                sprite.setPosition(scale*x*map.textureSpriteWidth, scale*y*map.textureSpriteHeight);

                //Set scale
                sprite.setScale(scale, scale);

                //Draw sprite
                window.draw(sprite);



            }

        }

        /********************************************************
        * Draw Character                                        *
        *********************************************************/
        //Walk up
        //character.move(Up);
        //Check keyboard
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            character.move(Left);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            character.move(Up);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            character.move(Right);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            character.move(Down);
        }

        //Update character
        character.update(scale, scale);

        // Draw the character
        window.draw(character.sprite);

        /********************************************************
        * Draw Text panels                                      *
        *********************************************************/
        sf::Text textString;
        sf::Font font;
        font.loadFromFile("FreeMonoBold.ttf");
        //sf::Font font = sf::Font::getDefaultFont();
        textString.setFont(font);
        textString.setString("Test");
        textString.setPosition(40,40);
        textString.setColor(sf::Color::White);
        textString.setCharacterSize(30);

        window.draw(textString);

        // Update the window
        window.display();
    }
    //Log stop event loop
    logTextLine("Eventloop stopped", true, true);


    logTextLine("Stop function");
    logTextLine("Program Terminate", true, true);
    return 0;
}
