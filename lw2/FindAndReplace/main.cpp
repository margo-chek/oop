#include "pch.h"

using namespace std;

bool CheckArgumentCount(const int argumentCount)
{

	if (argumentCount != 4)
	{
		cerr << "Invalid count of arguments." << endl
			 << "Usage: FindAndReplace.exe <input string> <search string> <replace string>"
			 << endl;
		return false;
	}
	return true;
}


int main(int argc, char* argv[])
{
	if (!CheckArgumentCount(argc))
	{
		return 1;
	}
	string subject;
	while (getline(cin, subject))
	{
		cout << FindAndReplace(subject, argv[2], argv[3]) << endl;
	}
	return 0;
}