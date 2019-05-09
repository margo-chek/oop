#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

class ÑDictionary
{
	public:

		ÑDictionary(const std::string& fileName);

		void AddNewWord(const std::string& word, const std::string& translation);

		std::vector<std::string> FindTranslation(const std::string& word);

		void SaveDictionary();

		bool GetWasUpdatedFlag();

	private:

		std::multimap<std::string, std::string> m_dict;

		std::string m_dictionaryFileName;

		bool m_wasUpdated = false;

		void InsertIntoDictionary(const std::string& word, const std::string& translation);

		bool HasSameTranslation(const std::string& word, const std::string& translation);

		void WriteDictionary(std::ostream& outputFile);

		void ReadDictionary(std::istream& inputFile);

};

bool IsUpperCaseCharacter(unsigned char character);

void ToLowerCase(std::string& word);

std::ifstream OpenFileForReading(const std::string& fileName);

