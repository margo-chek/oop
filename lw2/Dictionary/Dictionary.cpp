#include "pch.h"
#include "dictionary.h"

using namespace std;

ifstream OpenFileForReading(const string& fileName)
{
	ifstream strm(fileName);

	if (!strm.is_open())
		cerr << "Failed to open " << fileName << "\n";

	return strm;
}

Dictionary LoadDictionary(const string& fileName)
{
	ifstream inputFile;
	Dictionary dictionary;

	inputFile = OpenFileForReading(fileName);

	if (inputFile)
	{
		dictionary = ReadDictionary(inputFile);
		inputFile.close();
	}

	return dictionary;
}

bool HaveSameTranslation(const string& word, const string& translation, const Dictionary& dictionary)
{
	auto range = dictionary.equal_range(word);
	if (distance(range.first, range.second) == 0)
		return false;

	return any_of(range.first, range.second, [&](const auto& wordTranslationPair) -> bool {
		return wordTranslationPair.second == translation;
	});
}


vector<string> FindTranslation(const string& word, const Dictionary& dictionary)
{
	auto rangeWordTranslation = dictionary.equal_range(word);
	vector<string> translation;

	if (distance(rangeWordTranslation.first, rangeWordTranslation.second) != 0) 
	{
		for_each(rangeWordTranslation.first, rangeWordTranslation.second, [&](const auto& currPair) -> void {
			translation.push_back(currPair.second);
		});
		return translation;
	}
	else
		return {};
}


Dictionary ReadDictionary(istream& inputFile)
{
	string word, translation;
	Dictionary dictionary;

	while (getline(inputFile, word) && (getline(inputFile, translation)))
	{
		if (!HaveSameTranslation(word, translation, dictionary))
		{
			dictionary.insert({ word, translation });
		}

		if (!HaveSameTranslation(translation, word, dictionary))
		{
			dictionary.insert({ translation, word });
		}	
	}

	return dictionary;
}

void WriteDictionary(ostream& inputFile, const Dictionary& dictionary)
{
	for (auto& word : dictionary)
	{
		inputFile << word.first << endl
				  << word.second << endl;
	}
}

void AddNewWord(const string& word, Dictionary& dictionary, bool& dictionaryChange)
{
	cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа." << endl;
	cout << ">";
	string translation;
	getline(cin, translation);

	if (!translation.empty())
	{
		dictionary.insert({ word, translation });
		dictionary.insert({ translation, word });

		cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << endl;
		dictionaryChange = true;
	}
	else
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
	}
}

void ProcessInputString(const string& inputString, Dictionary& dictionary, bool& dictionaryChange)
{
	vector<string> foundWords = FindTranslation(inputString, dictionary); 

	if (!foundWords.empty())
	{
		copy(foundWords.begin(), foundWords.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
	else
	{
		AddNewWord(inputString, dictionary, dictionaryChange);
	}
}

void SaveDictionary(string inputFileName, const Dictionary& dictionary)
{
	char exit;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;

	cout << ">";
	cin >> exit;

	if ((exit == 'Y') || (exit == 'y'))
	{
		if (inputFileName.empty())
		{
			cout << "Введите название словаря." << endl;
			cout << ">";
			cin >> inputFileName;
		}

		ofstream inputFile(inputFileName);
		WriteDictionary(inputFile, dictionary);
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не сохранены. До свидания." << endl;
	}
}

bool ProcessUserInput(Dictionary& dictionary)
{
	string inputString;
	bool dictionaryChange = false;

	while (inputString != "...")
	{
		cout << ">";
		getline(cin, inputString);

		if ((inputString != "...") && (inputString != ""))
		{
			ProcessInputString(inputString, dictionary, dictionaryChange);
		}
	}

	return dictionaryChange;
}
