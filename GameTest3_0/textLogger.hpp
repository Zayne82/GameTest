#ifndef TEXTLOGGER_HPP
#define TEXTLOGGER_HPP

#include <iostream>
#include <fstream>


void logTextLine(const char *text, bool centered = false, bool lines = false);
void logText(const char *text);
void logText(int number);

bool initLogFile();
void closeLogFile();

//bool logToFile;
//std::fstream logFile;

//Create a logFile-class that handles the log writing.

#endif
