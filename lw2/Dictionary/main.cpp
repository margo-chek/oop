#include "pch.h"
#include "dictionary.h"

using namespace std;

int main(int argc, const char* argv[])
{
	SetConsoleCP(1251); // ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

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

	bool didDictionaryChange = false;

	didDictionaryChange = ProcessUserInput(dictionary);

	if (didDictionaryChange)
	{
		SaveDictionary(fileName, dictionary);
	}
	else
	{
		cout << "���������� ������ �� ��������" << endl;
	}

	return 0;
}
