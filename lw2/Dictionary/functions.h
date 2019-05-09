#pragma once
#include "pch.h"
#include "Dictionary.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <string>
#include <vector>


std::string ParseCommandLine(const int argsCount, const char* argsVector[]);

void ProcessInputString(const std::string& inputString, CDictionary& dictionary);

std::string GetUserInput(std::istream& inputStream);

void ProcessUserInput(const std::string& userInput, CDictionary& dictionary);
