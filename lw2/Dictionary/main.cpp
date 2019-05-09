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

	try
	{
		fileName = ParseCommandLine(argc, argv);
	}
	catch (const invalid_argument& err)
	{
		cout << err.what() << endl;

		return 1;
	}

	CDictionary dictionary = new CDictionary(fileName);

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
		SaveDictionary();
	}
	else
	{
		cout << "Завершение работы со словарем" << endl;
	}

	return 0;
}

