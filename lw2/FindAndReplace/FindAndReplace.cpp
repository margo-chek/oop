#include "pch.h"
#include "FindAndReplace.h"

using namespace std;

string FindAndReplace(string const& subject, string const& search,
	string const& replace)
{
	if (search.empty())
	{
		return subject;
	}

	string replaceStringResult;
	size_t pos = 0;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(search, pos);
		replaceStringResult.append(subject, pos, foundPos - pos);
		if (foundPos != string::npos)
		{
			replaceStringResult.append(replace);
			pos = foundPos + search.size();
		}
		else
		{
			break;
		}
	}

	return replaceStringResult;
}