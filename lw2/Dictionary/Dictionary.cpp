#include "pch.h"
#include "dictionary.h"

std::ifstream OpenFileForReading(const std::string& fileName)
{
	std::ifstream strm(fileName);

	if (!strm.is_open())
		std::cout << "Failed to open " << fileName << "\n";

	return strm;
}

Dictionary LoadDictionary(const std::string& fileName)
{
	std::ifstream inputFile;
	Dictionary dictionary;

	inputFile = OpenFileForReading(fileName);

	if (inputFile)
	{
		dictionary = ReadDictionary(inputFile);
		inputFile.close();
	}

	return dictionary;
}

void AddTranslation(const std::string& word, const std::string& translation, Dictionary& dictionary)
{
	dictionary.insert({ word, translation });
	dictionary.insert({ translation, word });
}

std::string FindTranslation(const std::string& word, const Dictionary& dictionary)
{
	auto pairWordTranslation = dictionary.find(word);

	if (pairWordTranslation != dictionary.end())
	{
		return { (*pairWordTranslation).second };
	}
	else
		return {};
}

Dictionary ReadDictionary(std::istream& inputFile)
{
	std::string word, translation;
	Dictionary dictionary;

	dictionary.clear();

	while (getline(inputFile, word) && (getline(inputFile, translation)))
	{
		std::string foundWord = FindTranslation(word, dictionary);

		if (foundWord.empty())
		{
			AddTranslation(word, translation, dictionary);
		}
	}

	return dictionary;
}

void WriteDictionary(std::ostream& inputFile, const Dictionary& dictionary)
{
	for (auto& word : dictionary)
	{
		inputFile << word.first << std::endl
				  << word.second << std::endl;
	}
}

void AddNewWord(const std::string& word, Dictionary& dictionary, bool& dictionaryChange)
{
	std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << std::endl;
	std::cout << ">";
	std::string translation;
	getline(std::cin, translation);

	if (!translation.empty())
	{
		AddTranslation(word, translation, dictionary);
		std::cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << std::endl;
		dictionaryChange = true;
	}
	else
	{
		std::cout << "Слово \"" << word << "\" проигнорировано." << std::endl;
		dictionaryChange = false;
	}
}

void ProcessInputString(const std::string& inputString, Dictionary& dictionary, bool& dictionaryChange)
{
	std::string foundWord = FindTranslation(inputString, dictionary);

	if (!foundWord.empty())
	{
		std::cout << foundWord << std::endl;
	}
	else
	{
		AddNewWord(inputString, dictionary, dictionaryChange);
	}
}

void SaveDictionary(std::string inputFileName, const Dictionary& dictionary)
{
	char exit;
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << std::endl;

	std::cout << ">";
	std::cin >> exit;

	if ((exit == 'Y') || (exit == 'y'))
	{
		if (inputFileName.empty())
		{
			std::cout << "Введите название словаря." << std::endl;
			std::cout << ">";
			std::cin >> inputFileName;
		}

		std::ofstream inputFile(inputFileName);
		WriteDictionary(inputFile, dictionary);
		std::cout << "Изменения сохранены. До свидания." << std::endl;
	}
	else
	{
		std::cout << "Изменения не сохранены. До свидания." << std::endl;
	}
}

bool ProcessUserInput(Dictionary& dictionary)
{
	std::string inputString;
	bool dictionaryChange = false;

	while (inputString != "...")
	{
		std::cout << ">";
		getline(std::cin, inputString);

		if ((inputString != "...") && (inputString != ""))
		{
			ProcessInputString(inputString, dictionary, dictionaryChange);
		}
	}

	return dictionaryChange;
}
