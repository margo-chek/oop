#include "pch.h"
#include "dictionary.h"

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string fileName;
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
		std::cout << "Завершение работы со словарем" << std::endl;
	}

	return 0;
}
