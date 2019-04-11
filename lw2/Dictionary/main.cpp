#include "pch.h"
#include "dictionary.h"

using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	string fileName;
	Dictionary dictionary;
	bool isChangeDictionary = false;

	if (argc == 2)
	{
		fileName = argv[1];
		dictionary = LoadDictionary(fileName);
	}

	isChangeDictionary = ProcessUserInput(dictionary);

	if (isChangeDictionary)
	{
		SaveDictionary(fileName, dictionary);
	}
	else
	{
		cout << "Завершение работы со словарем" << endl;
	}

	return 0;
}
