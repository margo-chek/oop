#include "pch.h"
#include <iostream>
#include <fstream>

using namespace std;

//лучше bool CopyFile(const string& inFileName, const string& outFileName)  // par1 = inFileName, par2 = outFileName
bool CopyFile(int parc, char * par1, char * par2)
{
	if (parc != 3)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: copyfile.exe <input file> <output file>\n";
		return false;
	}

	// Объявили переменную типа ifstream 
	// (input file stream, поток для чтения из файла), проинициализировав его именем входного файла
	ifstream input(par1);

	// вызываем метод is_open() у объекта input, который вернет true, если файл был открыт
	if (!input.is_open())
	{
		cout << "Failed to open " << par1 << " for reading\n";
		return false;
	}

	// создали поток для записи в выходной файл
	ofstream output(par2);
	if (!output.is_open())
	{
		cout << "Failed to open " << par2 << " for writing\n";
		return false;
	}

	char ch;
	// Считываем в переменную ch символ из входного потока
	// возвращаем значение, приводимое к bool, которое сигнализирует об успехе
	while (input.get(ch))
	{
		if (!output.put((char)toupper(ch)))
		{
			cout << "Failed to save data on disk\n";
			return false;
		}
	}

	if (!output.flush()) // Если не удалось сбросить данные на диск
	{
		cout << "Failed to save data on disk\n";
		return false;
	}

	return true;
}

int main(int argc, char * argv[])
{
	if (CopyFile(argc, argv[1], argv[2]))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}