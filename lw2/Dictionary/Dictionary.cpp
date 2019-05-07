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
	
	return strm;
}

Dictionary LoadDictionary(const string& fileName)
{
	Dictionary dictionary{};
	dictionary.dictionaryFileName = fileName;

	ifstream inputFile = OpenFileForReading(dictionary.dictionaryFileName);
	Dictionary loadDictionary = ReadDictionary(dictionary, inputFile);

	return loadDictionary;
}

bool HasSameTranslation(const Dictionary& dictionary, const string& word, const string& translation)
{
	auto range = dictionary.dict.equal_range(word);
	if (distance(range.first, range.second) == 0)
		return false;

	return any_of(range.first, range.second, [&](const auto& wordTranslationPair) -> bool {
		return wordTranslationPair.second == translation;
	});
}


vector<string> FindTranslation(const Dictionary& dictionary, const string& word)
{
	auto rangeWordTranslation = dictionary.dict.equal_range(word);

	if (distance(rangeWordTranslation.first, rangeWordTranslation.second) == 0) 
	{
		return {};
	}

	vector<string> translation;

	for_each(rangeWordTranslation.first, rangeWordTranslation.second, [&](const auto& currPair) 
	{
		translation.push_back(currPair.second);
	});
	return translation;
}

bool IsUpperCaseCharacter(unsigned char character)
{
	return (character >= 0x41 && character <= 0x5A) || (character >= 0xC0 && character <= 0xDF) || character == 0xA8;
}

void ToLowerCase(string& word)
{
	for (size_t i = 0; i < word.length(); i++)
	{
		auto currentCharacter = static_cast<unsigned char>(word[i]);

		if (IsUpperCaseCharacter(currentCharacter))
		{
			currentCharacter == 0xA8 ? currentCharacter += 16 : currentCharacter += 32;
			word[i] = currentCharacter;
		}
	}
}

Dictionary InsertIntoDictionary(Dictionary& dictionary, const string& word, const string& translation)
{
	if (!HasSameTranslation(dictionary, word, translation))
	{
		dictionary.dict.insert({ word, translation });
	}
}

Dictionary ReadDictionary(Dictionary& dictionary, istream& inputFile)
{
	string word, translation;

	while (std::getline(inputFile, word) && std::getline(inputFile, translation))
	{
		ToLowerCase(word);
		ToLowerCase(translation);

		InsertIntoDictionary(dictionary, word, translation);
		InsertIntoDictionary(dictionary, translation, word);	
	}
	
	return dictionary;
}


void WriteDictionary(const Dictionary& dictionary, ostream& outputFile)
{
	for (auto& [word, translation] : dictionary.dict)
	{
		outputFile << word << endl
				   << translation << endl;
	}
}

void AddNewWord(Dictionary& dictionary, const string& word, const string& translation)
{
	if (translation.empty())
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
	}

	InsertIntoDictionary(dictionary, word, translation);
	InsertIntoDictionary(dictionary, translation, word);

	cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << endl;
	dictionary.wasUpdated = true;
}


void ProcessInputString(const string& inputString, Dictionary& dictionary)
{
	vector<string> foundWords = FindTranslation(dictionary, inputString); 

	if (!foundWords.empty())
	{
		copy(foundWords.begin(), foundWords.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
	else
	{
		cout << "Неизвестное слово \"" << inputString << "\". Введите перевод или пустую строку для отказа." << endl;
		string translation = GetUserInput(cin);
		AddNewWord(dictionary, inputString, translation);
	}
}

/*void SaveDictionary(string inputFileName, istream& input, ostream& output, 
	const function<void(const string& fileName)>& saver)*/

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

		ofstream outputFile(dictionary.dictionaryFileName);
		WriteDictionary(dictionary, outputFile);
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

	ToLowerCase(inputString);

	return inputString;
}

void ProcessUserInput(const string& userInput, Dictionary& dictionary)
{
	if (userInput == "...")
		return;
	
	ProcessInputString(userInput, dictionary);
}
