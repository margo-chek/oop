#include "pch.h"
#include <optional>

using namespace std;

using Args = pair<string, string>;
using Vec = vector<size_t>;

optional<Args> ParseCmdLineArgs(const int argc, char* argv[])
{
	Args argsValue;
	if (argc != 3)
	{
		cerr << "Invalid argument count\n"
			 << "Usage: findtext.exe <inputFile> <searchString>" << endl;
		return nullopt;
	}
	argsValue = make_pair(argv[1], argv[2]);

	return argsValue;
}

optional<Vec> SearchTextInFile(const string& inputFile, const string& searchString)
{
	ifstream file(inputFile); // вместо ifstream file; 	file.open(inputFile);

	if (!file.is_open())
	{
		cerr << "File not found" << endl;
		return nullopt;
	}

	if (searchString.empty())
	{
		cerr << "Searching string must be not empty" << endl;
		return nullopt;
	}

	string line;
	size_t lineNumber = 0;
	Vec numberString;

	while (getline(file, line))
	{
		++lineNumber;

		if (line.find(searchString) != string::npos)
		{
			numberString.push_back(lineNumber);
		}
	}

	if (numberString.empty())
	{
		cerr << "Text not found" << endl;
		return nullopt;
	}

	return numberString;
}

void PrintLineNumbersContainingString(ostream& output, const vector<size_t>& numberString) 
{
	cout << fixed;
	copy(numberString.begin(), numberString.end(), ostream_iterator<size_t>(output, "\n"));
	cout << endl;
}

int main(int argc, char* argv[])
{
	optional<Args> cmdLineArgs = ParseCmdLineArgs(argc, argv);

	if (!cmdLineArgs.has_value()) // Метод has_value класса std::optional, говорит, есть ли там значение. Возвращает булевое значение.
		return 1;

	// Чтобы получить доступ к значению, можно использовать метод value
	 optional<Vec> matchesCount = SearchTextInFile(cmdLineArgs.value().first, cmdLineArgs.value().second);

	 if (!matchesCount.has_value())
		 return 1;

	 PrintLineNumbersContainingString(cout, matchesCount.value());

	return 0;
}
