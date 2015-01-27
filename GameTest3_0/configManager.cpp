#include "configManager.hpp"
#include "stringToInt.hpp"
#include "textLogger.hpp"
#include <fstream>
#include <iostream>

bool ConfigManager::loadConfigFromFile(const char *fileName){
    /********************************************************
    * Set Default Controls                                  *
    *********************************************************/
    //Misc Settings
	winX            = 800;
	winY            = 600;
	winMode         = 1;						//1=Windowed, 2=Fullscreen, 3=WindowedFullscreen
	winScale        = true;
	winAspLim       = true;
	characterName   = "Locke";

	//Keyboard settings
	keyboardUp      = sf::Keyboard::Up;
	keyboardDown    = sf::Keyboard::Down;
	keyboardLeft    = sf::Keyboard::Left;
	keyboardRight   = sf::Keyboard::Right;
	keyboardBtn1    = sf::Keyboard::Z;
	keyboardBtn2    = sf::Keyboard::S;
	keyboardBtn3    = sf::Keyboard::A;
	keyboardBtn4    = sf::Keyboard::W;
	keyboardBtnL    = sf::Keyboard::Q;
	keyboardBtnR    = sf::Keyboard::E;
	keyboardStart   = sf::Keyboard::Return;
	keyboardSelect  = sf::Keyboard::Space;

	//Joystick settings
	joystickUp      = 1;
	joystickDown    = 2;
	joystickLeft    = 3;
	joystickRight   = 4;
	joystickBtn1    = 5;
	joystickBtn2    = 6;
	joystickBtn3    = 7;
	joystickBtn4    = 8;
	joystickBtnL    = 9;
	joystickBtnR    = 10;
	joystickStart   = 11;
	joystickSelect  = 12;

    /********************************************************
    * Read Config file                                      *
    *********************************************************/
    //Open file for reading
	std::fstream configFile;
	configFile.open(fileName, std::fstream::in);

	//Make sure the file is open
	if(!configFile.is_open()){
        //Try to create default settings file

        //TODO: Save values to file.

		return false;
	}
	//Strings used while reading settings file
    std::string line;
	std::string propertyName;
	std::string propertyValue;
	std::string prefixes = "JKW";

	//Read file, replacing default values
    while(configFile.good()){
        //Reset property and value
        propertyValue = "";
        propertyName  = "";
        //Read line from config file
		std::getline(configFile, line);
		//Get property name
		propertyName = retrieveProperyName(line);
		//If we got a property name...
		if(propertyName.length() > 0){
			//Get the corresponding value
			propertyValue = retrieveProperyValue(line);
			//If we got a value...
			if(propertyValue.length() > 0){
                //Check if name indicates binding a key
                if(propertyName.at(0) == prefixes.at(0)){
                    //Joystick settings

                    //If the property name is known, set the button id
                    if(propertyName == "JoystickUp"){
                        joystickUp = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickDown"){
                        joystickDown = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickLeft"){
                        joystickLeft = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickRight"){
                        joystickRight = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickBtn1"){
                        joystickBtn1 = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickBtn2"){
                        joystickBtn2 = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickBtn3"){
                        joystickBtn3 = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickBtn4"){
                        joystickBtn4 = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickBtnL"){
                        joystickBtnL = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickBtnR"){
                        joystickBtnR = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickStart"){
                        joystickStart = stringToInt(isolateNumber(propertyValue));
                    }else if(propertyName == "JoystickSelect"){
                        joystickSelect = stringToInt(isolateNumber(propertyValue));
                    }else{
                        //Else do nothing
                        logText("Unknown binding: ");
                        logText(propertyName.c_str());
                        logText("\n");
                    }
                }else if(propertyName.at(0) == prefixes.at(1)){
                    //Keyboard settings

                    //If the property name is known, bind the key
                    if(propertyName == "KeyboardUp"){
                        keyboardUp = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardDown"){
                        keyboardDown = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardLeft"){
                        keyboardLeft = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardRight"){
                        keyboardRight = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardBtn1"){
                        keyboardBtn1 = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardBtn2"){
                        keyboardBtn2 = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardBtn3"){
                        keyboardBtn3 = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardBtn4"){
                        keyboardBtn4 = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardBtnL"){
                        keyboardBtnL = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardBtnR"){
                        keyboardBtnR = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardStart"){
                        keyboardStart = bindKey(propertyValue);
                    }else if(propertyName == "KeyboardSelect"){
                        keyboardSelect = bindKey(propertyValue);
                    }else{
                        //Else do nothing
                        logText("Unknown binding: ");
                        logText(propertyName.c_str());
                        logText("\n");
                    }
                }else if(propertyName.at(0) == prefixes.at(2)){
                    //Window settings

                    //If the property name is known, save the setting
                    if(propertyName == "WindowMode"){
                        //Check the value of WindowMode
                        if(propertyValue == "Windowed"){
                            winMode = 1;
                        }else if(propertyValue == "Fullscreen"){
                            winMode = 2;
                        }else if(propertyValue == "WindowedFullscreen"){
                            winMode = 3;
                        }else{
                            //Unknown video mode, use windowed
                            winMode = 1;
                        }
                    }else if(propertyName == "WindowResX"){
                        winX = stringToInt(propertyValue);
                    }else if(propertyName == "WindowResY"){
                        winY = stringToInt(propertyValue);
                    }else if(propertyName == "WindowScale"){
                        //Check the value of WindowScale
                        if(propertyValue == "true"){
                            winScale = true;
                        }else{
                            winScale = false;
                        }
                    }else if(propertyName == "WindowAspectLim"){
                        //Check the value of WindowAspectLim
                        if(propertyValue == "true"){
                            winAspLim = true;
                        }else{
                            winAspLim = false;
                        }
                    }else{
                        //Else do nothing
                        logText("Unknown binding: ");
                        logText(propertyName.c_str());
                        logText("\n");
                    }
                }else{
                    //Other settings
                    //setCharacterControls(propertyName, propertyValue);

                    //If the property name is known, save the setting
                    if(propertyName == "Character"){
                        characterName = propertyValue;
                    }else{
                        //Else do nothing
                        logText("Unknown binding: ");
                        logText(propertyName.c_str());
                        logText("\n");
                    }
                }
			}
		}
	}

	//Close file
	configFile.close();
	return true;
}

std::string ConfigManager::retrieveProperyName(std::string &lineString){
	//Prepare empty string to return
	std::string propertyName = "";
	//String of whitespaces
	std::string whiteSpaces = " \t\f\v\n\r";
	//Character indicating a comment
	std::string commentCharacter = "#";
	//Character indicating a segment
	std::string segmentCharacter = "[";
	//Positions for extracting property name
	std::size_t first;
	std::size_t last;

	if(lineString.length() > 0){
		//Check first character that is not a space
		first = lineString.find_first_not_of(whiteSpaces);
		if(first == std::string::npos){
			//Nothing other than spaces in this line
			return propertyName;
		}
		//Check if the line should be ignored
		if(lineString.at(first) == commentCharacter.at(0) || lineString.at(first) == segmentCharacter.at(0)){
			//Not a property name
			return propertyName;
		}
		//Find position of last character not a space before the equals sign.
		last = lineString.find_first_of("=");
		last = lineString.find_last_not_of(whiteSpaces,last-1);
		if(last == std::string::npos){
			//Something went wrong
			return propertyName;
		}
		//Extract the property name
		propertyName = lineString.substr(first,last-first+1);
	}
	return propertyName;
}

std::string ConfigManager::retrieveProperyValue(std::string &lineString){
	//Prepare empty string to return
	std::string propertyValue = "";
	//String of whitespaces
	std::string whiteSpaces = " \t\f\v\n\r";
	//Character indicating a comment
	std::string commentCharacter = "#";
	//Positions for extracting property value
	std::size_t first;
	std::size_t last;
	//Find position of first character not a space after the equals sign.
	first = lineString.find_first_of("=");
	first = lineString.find_first_not_of(whiteSpaces, first+1);
	//Check that we got a value
	if(first == std::string::npos){
		//There is no value
		return propertyValue;
	}
	//Check if there is a comment after the value
	last = lineString.find_first_of(commentCharacter);
	if(last == std::string::npos){
		//Set last to end of string +1
		last = lineString.length()+1;
	}
	//Find last character not a space
	last = lineString.find_last_not_of(whiteSpaces, last-1);
	//Check that we got a value
	if(last == std::string::npos || last < first){
		//Something went wrong or there is no property value
		return propertyValue;
	}
	//Extract the property value and return it
	propertyValue = lineString.substr(first, last-first+1);
	return propertyValue;
}

std::string ConfigManager::isolateNumber(std::string value){
	//Find first and last number in value
	std::size_t first = value.find_first_of("0123456789");
	std::size_t last  = value.find_last_of("0123456789");
	//Extract the number in between the first and last position
	if(first != std::string::npos && last != std::string::npos){
		return value.substr(first, last-first+1);
	}
	//No number in value, return empty string
	return "";
}

sf::Keyboard::Key ConfigManager::bindKey(std::string &key){
	//Check length of key string
	if(key.length() > 1){
		//Check Arrow keys
		if(key == "Up"){        return sf::Keyboard::Up;        }
		if(key == "Down"){	    return sf::Keyboard::Down;	    }
		if(key == "Left"){	    return sf::Keyboard::Left;	    }
		if(key == "Right"){	    return sf::Keyboard::Right;	    }
		//Check Numpad
		if(key == "Numpad0"){   return sf::Keyboard::Numpad0;	}
		if(key == "Numpad1"){	return sf::Keyboard::Numpad1;	}
		if(key == "Numpad2"){	return sf::Keyboard::Numpad2;	}
		if(key == "Numpad3"){	return sf::Keyboard::Numpad3;	}
		if(key == "Numpad4"){	return sf::Keyboard::Numpad4;	}
		if(key == "Numpad5"){	return sf::Keyboard::Numpad5;	}
		if(key == "Numpad6"){	return sf::Keyboard::Numpad6;	}
		if(key == "Numpad7"){	return sf::Keyboard::Numpad7;	}
		if(key == "Numpad8"){	return sf::Keyboard::Numpad8;	}
		if(key == "Numpad9"){	return sf::Keyboard::Numpad9;	}
		//Check number keys
		if(key == "Num0"){		return sf::Keyboard::Num0;		}
		if(key == "Num1"){		return sf::Keyboard::Num1;		}
		if(key == "Num2"){		return sf::Keyboard::Num2;		}
		if(key == "Num3"){		return sf::Keyboard::Num3;		}
		if(key == "Num4"){		return sf::Keyboard::Num4;		}
		if(key == "Num5"){		return sf::Keyboard::Num5;		}
		if(key == "Num6"){		return sf::Keyboard::Num6;		}
		if(key == "Num7"){		return sf::Keyboard::Num7;		}
		if(key == "Num8"){		return sf::Keyboard::Num8;		}
		if(key == "Num9"){		return sf::Keyboard::Num9;		}
		//Check F keys
		if(key == "F1"){		return sf::Keyboard::F1;		}
		if(key == "F2"){		return sf::Keyboard::F2;		}
		if(key == "F3"){		return sf::Keyboard::F3;		}
		if(key == "F4"){		return sf::Keyboard::F4;		}
		if(key == "F5"){		return sf::Keyboard::F5;		}
		if(key == "F6"){		return sf::Keyboard::F6;		}
		if(key == "F7"){		return sf::Keyboard::F7;		}
		if(key == "F8"){		return sf::Keyboard::F8;		}
		if(key == "F9"){		return sf::Keyboard::F9;		}
		if(key == "F10"){		return sf::Keyboard::F10;		}
		if(key == "F11"){		return sf::Keyboard::F11;		}
		if(key == "F12"){		return sf::Keyboard::F12;		}
		//Check other keys
		if(key == "Escape"){	return sf::Keyboard::Escape;	}
		if(key == "LControl"){	return sf::Keyboard::LControl;	}
		if(key == "LShift"){	return sf::Keyboard::LShift;	}
		if(key == "LAlt"){		return sf::Keyboard::LAlt;		}
		if(key == "LSystem"){	return sf::Keyboard::LSystem;	}
		if(key == "RControl"){	return sf::Keyboard::RControl;	}
		if(key == "RShift"){	return sf::Keyboard::RShift;	}
		if(key == "RAlt"){		return sf::Keyboard::RAlt;		}
		if(key == "RSystem"){	return sf::Keyboard::RSystem;	}
		if(key == "Menu"){		return sf::Keyboard::Menu;		}
		if(key == "LBracket"){	return sf::Keyboard::LBracket;	}
		if(key == "RBracket"){	return sf::Keyboard::RBracket;	}
		if(key == "SemiColon"){	return sf::Keyboard::SemiColon;	}
		if(key == "Comma"){		return sf::Keyboard::Comma;		}
		if(key == "Period"){	return sf::Keyboard::Period;	}
		if(key == "Quote"){		return sf::Keyboard::Quote;		}
		if(key == "Slash"){		return sf::Keyboard::Slash;		}
		if(key == "BackSlash"){	return sf::Keyboard::BackSlash;	}
		if(key == "Tilde"){		return sf::Keyboard::Tilde;		}
		if(key == "Equal"){		return sf::Keyboard::Equal;		}
		if(key == "Dash"){		return sf::Keyboard::Dash;		}
		if(key == "Space"){		return sf::Keyboard::Space;		}
		if(key == "Return"){	return sf::Keyboard::Return;	}
		if(key == "BackSpace"){	return sf::Keyboard::BackSpace; }
		if(key == "Tab"){		return sf::Keyboard::Tab;		}
		if(key == "PageUp"){	return sf::Keyboard::PageUp;	}
		if(key == "PageDown"){	return sf::Keyboard::PageDown;	}
		if(key == "End"){		return sf::Keyboard::End;		}
		if(key == "Home"){		return sf::Keyboard::Home;		}
		if(key == "Insert"){	return sf::Keyboard::Insert;	}
		if(key == "Delete"){	return sf::Keyboard::Delete;	}
		if(key == "Add"){		return sf::Keyboard::Add;		}
		if(key == "Subtract"){	return sf::Keyboard::Subtract;	}
		if(key == "Multiply"){	return sf::Keyboard::Multiply;	}
		if(key == "Divide"){	return sf::Keyboard::Divide;	}
		if(key == "Pause"){		return sf::Keyboard::Pause;		}
	}else{
		//Check alphabet
		if(key == "A"){			return sf::Keyboard::A;		    }
		if(key == "B"){			return sf::Keyboard::B;		    }
		if(key == "C"){			return sf::Keyboard::C;		    }
		if(key == "D"){			return sf::Keyboard::D;		    }
		if(key == "E"){			return sf::Keyboard::E;		    }
		if(key == "F"){			return sf::Keyboard::F;		    }
		if(key == "G"){			return sf::Keyboard::G;		    }
		if(key == "H"){			return sf::Keyboard::H;		    }
		if(key == "I"){			return sf::Keyboard::I;		    }
		if(key == "J"){			return sf::Keyboard::J;		    }
		if(key == "K"){			return sf::Keyboard::K;		    }
		if(key == "L"){			return sf::Keyboard::L;		    }
		if(key == "M"){			return sf::Keyboard::M;		    }
		if(key == "N"){			return sf::Keyboard::N;		    }
		if(key == "O"){			return sf::Keyboard::O;		    }
		if(key == "P"){			return sf::Keyboard::P;		    }
		if(key == "Q"){			return sf::Keyboard::Q;		    }
		if(key == "R"){			return sf::Keyboard::R;		    }
		if(key == "S"){			return sf::Keyboard::S;		    }
		if(key == "T"){			return sf::Keyboard::T;		    }
		if(key == "U"){			return sf::Keyboard::U;		    }
		if(key == "V"){			return sf::Keyboard::V;		    }
		if(key == "W"){			return sf::Keyboard::W;		    }
		if(key == "X"){			return sf::Keyboard::X;		    }
		if(key == "Y"){			return sf::Keyboard::Y;		    }
		if(key == "Z"){			return sf::Keyboard::Z;		    }
	}
	//Could not match key
	return sf::Keyboard::Escape;
}
