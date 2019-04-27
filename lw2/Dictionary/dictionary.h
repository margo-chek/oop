#pragma once
#include <Windows.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <iterator>
#include <map>
#include <string>
#include <vector>


struct Dictionary
{
	std::multimap<std::string, std::string> dict = {};

	std::string dictionaryFileName;

	bool wasEdited = false;
};

std::string ParseCommandLine(const int argsCount, const char* argsVector[]);

std::ifstream OpenFileForReading(const std::string& fileName);

Dictionary LoadDictionary(const std::string& fileName);

void ProcessInputString(const std::string& inputString, Dictionary& dictionary);

bool HaveSameTranslation(const std::string& word, const std::string& translation, const Dictionary& dictionary);

void AddNewWord(const std::string& inputString, Dictionary& dictionary);

std::vector<std::string> FindTranslation(const std::string& word, const Dictionary& dictionary);

void ToLower(std::string& str);

Dictionary ReadDictionary(Dictionary& dictionary);

void WriteDictionary(const Dictionary& dictionary);

void SaveDictionary(Dictionary& dictionary);

std::string GetUserInput(std::istream& inputStream);

void ProcessUserInput(const std::string& userInput, Dictionary& dictionary);
