#include "pch.h"

using namespace std;

struct Args { string fileName; string searchString; };

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

bool CheckArgumentCount(const int argumentCount)
{

	if (argumentCount != 3)
	{
		cerr << "Invalid argument count\n"
			 << "Usage: findtext.exe <inputFile> <searchString>" << endl;
		return false;
	}
	return true;
}

bool IsCommandLine(const string& inputFile, const string& searchString)
{
	ifstream file;
	file.open(inputFile);
	if (!file.is_open())

	{
		cout << "File not found" << endl;
		return false;
	}

	// string searchString;
	if (searchString.empty())
	{
		cout << "Searching string must be not empty" << endl;
		return false;
	}

	return true;
}

// optional<string> ParseCmdLineArgs(argc, argv);
/*optional<Args> parseCmdLineArgs(int argc, char* argv[])
{
  if (argc == 3)
    return Args{argv[1], argv[2]};
  return null_opt;
}*/
bool ParseCmdLineArgs(int argc, char* argv[], Args& args)
{
	if (argc == 3)
	{
		args = Args{ argv[1], argv[2] };
		return true;
	}
	return false;
}

int main(int argc, char* argv[])
{
	if (!CheckArgumentCount(argc))
	{
		return 1;
	}
	
	if (!ParseCmdLineArgs(argc, argv, args))
	{
		return 1;
	}

	pair<string, string> inputArguments = ParseCmdLineArgs(argc, argv);
	int matchesCount = SearchInFile(inputArguments.first, inputArguments.second); // SearchTextInFile

	return 0;
}
