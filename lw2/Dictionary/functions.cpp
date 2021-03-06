#include "pch.h" 
#include "functions.h"

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


void ProcessInputString(const string& inputString, CDictionary& dictionary)
{
	vector<string> foundWords = dictionary.FindTranslation(inputString);

	if (!foundWords.empty())
	{
		copy(foundWords.begin(), foundWords.end() - 1, ostream_iterator<string>(cout, ", "));
		cout << foundWords.back() << endl;
	}
	else
	{
		cout << "����������� ����� \"" << inputString << "\". ������� ������� ��� ������ ������ ��� ������." << endl;
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
