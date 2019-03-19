#include "pch.h"

using namespace std;

bool FindStringInFile(const string& line, const string& searchString)
{
	if (line.find(searchString) != string::npos)
	{
		return true;
	}
	else
		return false;
}

bool PrintLineNumbersContainingString(istream& input, const string& searchString)
{
	string line;
	int lineNumber = 0;
	bool textWasFound = false;

	while (getline(input, line))
	{
		++lineNumber;

		if (FindStringInFile(line, searchString))
		{
			cout << lineNumber << endl;
			textWasFound = true;
		}
	}

	return textWasFound;
}

int SearchTextInFile(istream& inputFile, const string& searchString)
{
	if (!PrintLineNumbersContainingString(inputFile, searchString))
	{
		cout << "Text not found" << endl;
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		cout << "Invalid argument count\n"
				  << "Usage: findtext.exe <inputFile> <searchString>" << endl;
		return 1;
	}

	ifstream inputFile;

	inputFile.open(argv[1]);

	if (!inputFile)
	{
		cout << "File not found" << endl;
		return 1;
	}

	string search = argv[2];

	if (search.empty())
	{
		cout << "Searching string must be not empty" << endl;
		return 1;
	}

	return SearchTextInFile(inputFile, search);
}