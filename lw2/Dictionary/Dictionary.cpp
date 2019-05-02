#include "pch.h"
#include "dictionary.h"

using namespace std;

string ParseCommandLine(const int argsCount, const char* argsVector[])
{
	if (argsCount != 2)
		throw invalid_argument("Try to run program follow this template:\n Dictionary.exe <dictionary file>");
	
	string fileNameArg = argsVector[1];

	return fileNameArg;
}

ifstream OpenFileForReading(const string& fileName)
{
	ifstream strm(fileName);

	if (!strm.is_open())
		cerr << "Failed to open " << fileName << "\n";

	// ToLowerCase(strm);

	return strm;
}

Dictionary LoadDictionary(const string& fileName)
{
	Dictionary dictionary{};
	dictionary.dictionaryFileName = fileName;

	ReadDictionary(dictionary);

	return dictionary;
}

bool HaveSameTranslation(const string& word, const string& translation, const Dictionary& dictionary)
{
	auto range = dictionary.dict.equal_range(word);
	if (distance(range.first, range.second) == 0)
		return false;

	return any_of(range.first, range.second, [&](const auto& wordTranslationPair) -> bool {
		return wordTranslationPair.second == translation;
	});
}


vector<string> FindTranslation(const string& word, const Dictionary& dictionary)
{
	auto rangeWordTranslation = dictionary.dict.equal_range(word);

	if (distance(rangeWordTranslation.first, rangeWordTranslation.second) == 0) 
	{
		return {};
	}

	vector<string> translation;

	for_each(rangeWordTranslation.first, rangeWordTranslation.second, [&](const auto& currPair) -> void {
		translation.push_back(currPair.second);
	});
	return translation;
	
}
/*
string const ToLower(const string& str)
{
	wstring strToTransform = L"str";
	transform(strToTransform.begin(), strToTransform.end(), strToTransform.begin(), ::tolower);
	string strToTransform2(strToTransform.begin(), strToTransform.end());
	return strToTransform2;
}

string const ToLower(string& str)
{
	for_each(str.begin(), str.end(), [](char& strToTransform)
	{ strToTransform = tolower(static_cast<unsigned char>(strToTransform)); });
	return strToTransform;
}
*/
bool isUpperCaseCharacter(unsigned char character)
{
	return (character >= 0x41 && character <= 0x5A) || (character >= 0xC0 && character <= 0xDF) || character == 0xA8;
}

void ToLowerCase(string& word)
{
	for (size_t i = 0; i < word.length(); i++)
	{
		auto currentCharacter = static_cast<unsigned char>(word[i]);

		if (isUpperCaseCharacter(currentCharacter))
		{
			currentCharacter == 0xA8 ? currentCharacter += 16 : currentCharacter += 32;
			word[i] = currentCharacter;
		}
	}
}

void ReadDictionary(Dictionary& dictionary)
{
	ifstream inputFile = OpenFileForReading(dictionary.dictionaryFileName);

	string word, translation;

	while (std::getline(inputFile, word) && std::getline(inputFile, translation))
	{
		ToLowerCase(word);
		ToLowerCase(translation);
		if (!HaveSameTranslation(word, translation, dictionary))
		{
			dictionary.dict.insert({ word, translation });
		}

		if (!HaveSameTranslation(translation, word, dictionary))
		{
			dictionary.dict.insert({ translation, word });
		}	
	}
}

void WriteDictionary(const Dictionary& dictionary)
{
	ofstream outputFile(dictionary.dictionaryFileName); 

	for (auto& range : dictionary.dict)
	{
		outputFile << range.first << endl
				  << range.second << endl;
	}
}

void AddNewWord(const string& word, Dictionary& dictionary)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	cout << ">";
	string translation;
	std::getline(cin, translation);

	ToLowerCase(translation);

	if (!translation.empty())
	{
		dictionary.dict.insert({ word, translation });
		dictionary.dict.insert({ translation, word });

		cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << endl;
		dictionary.wasEdited = true;
	}
	else
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
	}
}

void ProcessInputString(const string& inputString, Dictionary& dictionary)
{
	vector<string> foundWords = FindTranslation(inputString, dictionary); 

	if (!foundWords.empty())
	{
		copy(foundWords.begin(), foundWords.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
	else
	{
		AddNewWord(inputString, dictionary);
	}
}

void SaveDictionary(Dictionary& dictionary)
{
	char exit;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;

	cout << ">";
	cin >> exit;

	if ((exit == 'Y') || (exit == 'y'))
	{
		if (dictionary.dictionaryFileName.empty())
		{
			cout << "Введите название словаря." << endl;
			cout << ">";
			cin >> dictionary.dictionaryFileName;
		}

		WriteDictionary(dictionary);
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не сохранены. До свидания." << endl;
	}
}

string GetUserInput(istream& inputStream)
{
	string inputString;

	cout << ">";
	std::getline(inputStream, inputString);


	return inputString;
}

void ProcessUserInput(const string& userInput, Dictionary& dictionary)
{
	if (userInput == "..." || userInput == "")
		return;
	
	ProcessInputString(userInput, dictionary);

}

