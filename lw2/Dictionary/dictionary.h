#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class CDictionary
{
public:

	CDictionary() = default;

	CDictionary(const std::string& fileName, std::istream& inputStream);

	std::multimap<std::string, std::string> GetDict() const;
	std::string GetFileName() const;
	
	void AddNewWord(const std::string& word, const std::string& translation);

	std::vector<std::string> FindTranslation(const std::string& word);

	void SaveDictionary();

	bool GetWasUpdatedFlag() const;

	bool HasSameTranslation(const std::string& word, const std::string& translation) const;

private:

	std::multimap<std::string, std::string> m_dict;

	std::string m_dictionaryFileName;

	bool m_wasUpdated = false;

	void InsertIntoDictionary(const std::string& word, const std::string& translation);

	// void WriteDictionary(std::ostream& outputFile);

	void ReadDictionary(std::istream& inputFile);
};

bool IsUpperCaseCharacter(unsigned char character);

void ToLowerCase(std::string& word);

std::ifstream OpenFileForReading(const std::string& fileName);
