#include "pch.h"
#include <optional>

using namespace std;

using Args = pair<string, string>;
using Vec = vector<size_t>;

void PrintLineNumbersContainingString(ostream& output, const vector<size_t>& numberString) // 1 вариант
{
	cout << fixed;
	copy(numberString.begin(), numberString.end(), ostream_iterator<size_t>(output));
	cout << endl;
}

void PrintLineNumbersContainingString(ostream& output, const vector<size_t>& numberString) // 2 вариант
{
	for (size_t n : numberString)
	{
		cout << n << '\n';
	}
}


//optional<Vec> SearchTextInFile(const string& inputFile, const string& searchString, vector<size_t>& numberString) - надо выход?
optional<Vec> SearchTextInFile(const string& inputFile, const string& searchString)
{
	ifstream file;
	file.open(inputFile);
	string line;
	size_t lineNumber = 0;
	bool textWasFound = false;
	Vec numberString = {};

	if (!file.is_open())
	{
		cerr << "File not found" << endl;
		return {};
	}

	if (searchString.empty())
	{
		cerr << "Searching string must be not empty" << endl;
		return {};
	}

	if (line.find(searchString) == string::npos)
	{
		cerr << "Text not found" << endl;
		return {};
	}

	while (getline(inputFile, line))
	{
		++lineNumber;

		if (line.find(searchString) != string::npos)
		{
			// vector<size_t> numberString(istream_iterator<size_t>(lineNumber), (istream_iterator<size_t>())); - не знаю, как надо
			numberString.push_back(lineNumber);
			textWasFound = true;
		}
	}

	return numberString;
}

optional<Args> ParseCmdLineArgs(const int argc, char* argv[])
{
	Args argsValue;
	if (argc != 3)
	{
		cerr << "Invalid argument count\n"
			 << "Usage: findtext.exe <inputFile> <searchString>" << endl;
		return {}; // return null_opt;
	}
	argsValue = make_pair(argv[1], argv[2]);

	return argsValue;
}

int main(int argc, char* argv[])
{
	optional<Args> cmdLineArgs = ParseCmdLineArgs(argc, argv);

	if (!cmdLineArgs.has_value()) // Метод has_value класса std::optional, говорит, есть ли там значение. Возвращает булевое значение.
		return 1;

	// Args args = cmdLineArgs.value(); // Чтобы получить доступ к значению, можно использовать метод value

	 optional<Vec> matchesCount = SearchTextInFile(cmdLineArgs.first, cmdLineArgs.second);

	 /*if (!matchesCount.has_value())
		 return 1;*/

	 PrintLineNumbersContainingString(matchesCount);

	return 0;
}
