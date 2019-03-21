#include "pch.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid count of arguments." << endl
				  << "Usage: FindAndReplace.exe <input string> <search string> <replace string>"
				  << endl;
		return 1;
	}
	string subject;
	while (getline(cin, subject))
	{
		cout << FindAndReplace(subject, argv[2], argv[3]) << endl;
	}
	return 0;
}