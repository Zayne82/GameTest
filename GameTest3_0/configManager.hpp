#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <SFML/Window.hpp>

class ConfigManager{
public:
	//Function for loading settings file
	bool				loadConfigFromFile(const char *fileName);

	//Misc Settings
	int					winX;
	int					winY;
	int					winMode;						//1=Windowed, 2=Fullscreen, 3=WindowedFullscreen
	bool				winScale;
	bool                winAspLim;
	std::string			characterName;

	//Keyboard settings
	sf::Keyboard::Key	keyboardUp;
	sf::Keyboard::Key	keyboardDown;
	sf::Keyboard::Key	keyboardLeft;
	sf::Keyboard::Key	keyboardRight;
	sf::Keyboard::Key	keyboardBtn1;
	sf::Keyboard::Key	keyboardBtn2;
	sf::Keyboard::Key	keyboardBtn3;
	sf::Keyboard::Key	keyboardBtn4;
	sf::Keyboard::Key	keyboardBtnL;
	sf::Keyboard::Key	keyboardBtnR;
	sf::Keyboard::Key	keyboardStart;
	sf::Keyboard::Key	keyboardSelect;

	//Joystick settings
	int					joystickUp;
	int					joystickDown;
	int					joystickLeft;
	int					joystickRight;
	int					joystickBtn1;
	int					joystickBtn2;
	int					joystickBtn3;
	int					joystickBtn4;
	int					joystickBtnL;
	int					joystickBtnR;
	int					joystickStart;
	int					joystickSelect;

	//Functions for parsing lines read from config file
	std::string			retrieveProperyName(std::string &lineString);
	std::string			retrieveProperyValue(std::string &lineString);
	std::string			isolateNumber(std::string value);

	//Reads string and returns keyboard key
	sf::Keyboard::Key	bindKey(std::string &key);
};

#endif
