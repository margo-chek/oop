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

typedef std::multimap<std::string, std::string> Dictionary;

std::ifstream OpenFileForReading(const std::string& fileName);

Dictionary LoadDictionary(const std::string& fileName);

void ProcessInputString(const std::string& inputString, Dictionary& dictionary, bool& dictionaryChange);

bool HaveSameTranslation(const std::string& word, const std::string& translation, const Dictionary& dictionary);

void AddNewWord(const std::string& inputString, Dictionary& dictionary, bool& dictionaryChange);

std::vector<std::string> FindTranslation(const std::string& word, const Dictionary& dictionary);

Dictionary ReadDictionary(std::istream& inputFile);

void WriteDictionary(std::ostream& inputFile, const Dictionary& dictionary);

void SaveDictionary(std::string fileName, const Dictionary& dictionary);

bool ProcessUserInput(Dictionary& dictionary);
