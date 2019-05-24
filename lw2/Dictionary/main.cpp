#include "pch.h"
#include "Dictionary.h"
#include "functions.h"
#include <Windows.h>

using namespace std;

int main(int argc, const char* argv[])
{
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	string fileName;
	CDictionary dictionary;

	try
	{
		fileName = ParseCommandLine(argc, argv);
		ifstream inputStream = OpenFileForReading(fileName);
		dictionary = CDictionary(fileName, inputStream);
	}
	catch (const invalid_argument& err)
	{
		cout << err.what() << endl;
	}

	string inputString;
	while (inputString != "...")
	{
		if (cin.eof())
		{
			cin.clear();
		}

		inputString = GetUserInput(cin);
		// cin.clear();
		ProcessUserInput(inputString, dictionary);
	}

	if (dictionary.GetWasUpdatedFlag())
	{
		dictionary.SaveDictionary(cin, cout, [](const multimap<string, string>& dict, const string& fileName) -> void {
			ofstream outputFile(fileName);
			for (auto& [word, translation] : dict)
			{
				outputFile << word << endl
					 << translation << endl;
			}
		});
		
	}
	else
	{
		cout << "Завершение работы со словарем" << endl;
	}

	return 0;
}
