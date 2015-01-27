#include "textLogger.hpp"


/*
bool initLogFile(){
	//If logToFile
	if (logToFile){
		//Open file for writing
		logFile.open("log.txt", std::fstream::out | std::fstream::trunc );

		//Make sure the file is open
		if (!logFile.is_open()){
			//Try to create default settings file

			//TODO: Save values to file.

			return false;
		}
		return true;
	}
	return false;
}

void closeLogFile(){
	if (logToFile){
		logFile.close();
	}

}
*/
void logTextLine(const char *text, bool centered, bool lines){
    int lineLength = 50;
    if(lines){
        for(int i = 0; i < lineLength; i++){
            std::cout << "-";
        }
        std::cout << std::endl;
    }
    if(centered){
        int length = 0;
        for(int i = 0; i < lineLength; i++){
            if(text[i] == '\0'){
                break;
            }
            length++;
        }
        for(int i = 0; i < (lineLength-length)/2; i++){
            std::cout << " ";
        }
        std::cout << text << std::endl;
    }else{
        std::cout << text << std::endl;
    }
    if(lines){
        for(int i = 0; i < lineLength; i++){
            std::cout << "-";
        }
        std::cout << std::endl;
    }
}
void logText(const char *text){
    std::cout << text;
}
void logText(int number){
    std::cout << number;
}

