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
	std::multimap<std::string, std::string> dict; 

	std::string dictionaryFileName;

	bool wasUpdated = false;
};

std::string ParseCommandLine(const int argsCount, const char* argsVector[]);

std::ifstream OpenFileForReading(const std::string& fileName);

Dictionary LoadDictionary(const std::string& fileName);

void ProcessInputString(const std::string& inputString, Dictionary& dictionary);

bool HasSameTranslation(const Dictionary& dictionary, const std::string& word, const std::string& translation);

void AddNewWord(Dictionary& dictionary, const std::string& word, const std::string& translation);

std::vector<std::string> FindTranslation(const Dictionary& dictionary, const std::string& word);

bool IsUpperCaseCharacter(unsigned char character);

void ToLowerCase(std::string& word);

Dictionary ReadDictionary(Dictionary& dictionary, std::istream& inputFile);

void WriteDictionary(const Dictionary& dictionary, std::ostream& outputFile);

void SaveDictionary(Dictionary& dictionary);

std::string GetUserInput(std::istream& inputStream);

void ProcessUserInput(const std::string& userInput, Dictionary& dictionary);
