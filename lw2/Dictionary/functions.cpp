#include "functions.h"

using namespace std;

string ParseCommandLine(const int argsCount, const char* argsVector[])
{
	if (argsCount != 2)
		throw invalid_argument("Try to run program follow this template:\n Dictionary.exe <dictionary file>");

	string fileNameArg = argsVector[1];

	return fileNameArg;
}


void ProcessInputString(const string& inputString, CDictionary& dictionary)
{
	vector<string> foundWords = dictionary.FindTranslation(inputString);

	if (!foundWords.empty())
	{
		copy(foundWords.begin(), foundWords.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
	}
	else
	{
		cout << "Неизвестное слово \"" << inputString << "\". Введите перевод или пустую строку для отказа." << endl;
		string translation = GetUserInput(cin);
		// cin.clear();
		dictionary.AddNewWord(inputString, translation);
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

void ProcessUserInput(const string& userInput, CDictionary& dictionary)
{
	if (userInput == "...")
		return;

	ProcessInputString(userInput, dictionary);
}
