#include "pch.h"
#include "FindAndReplace.h"

std::string FindAndReplace(std::string const& subject, std::string const& search,
	std::string const& replace)
{
	if (search.empty())
	{
		return subject;
	}

	std::string replaceStringResult;
	size_t pos = 0;
	while (pos < subject.length())
	{
		size_t foundPos = subject.find(search, pos);
		replaceStringResult.append(subject, pos, foundPos - pos);
		if (foundPos != std::string::npos)
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