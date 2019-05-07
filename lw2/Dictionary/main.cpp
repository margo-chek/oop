#include "pch.h"
#include "dictionary.h"


using namespace std;

int main(int argc, const char* argv[])
{
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	string fileName;
	Dictionary dictionary{};

	try
	{
		fileName = ParseCommandLine(argc, argv);

		dictionary = LoadDictionary(fileName);
	}
	catch (const invalid_argument& err)
	{
		cout << err.what() << endl;

		return 1;
	}

	string inputString;
	while (inputString != "...")
	{
		inputString = GetUserInput(cin);
		ProcessUserInput(inputString, dictionary);
	}

	if (dictionary.wasUpdated)
	{
		SaveDictionary(dictionary);
	}
	else
	{
		cout << "Завершение работы со словарем" << endl;
	}

	return 0;
}

