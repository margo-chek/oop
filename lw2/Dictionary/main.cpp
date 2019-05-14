#include "pch.h"
#include "Dictionary.h"
#include "functions.h"
#include <Windows.h>

using namespace std;

int main(int argc, const char* argv[])
{
	SetConsoleCP(1251); // ��������� ������� �������� win-cp 1251 � ����� �����
	SetConsoleOutputCP(1251); // ��������� ������� �������� win-cp 1251 � ����� ������

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
		dictionary.SaveDictionary();
	}
	else
	{
		cout << "���������� ������ �� ��������" << endl;
	}

	return 0;
}

