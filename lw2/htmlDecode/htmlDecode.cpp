#include "pch.h"
#include "htmlDecode.h"
#include "iterator"

const std::vector<PairSearchReplace> htmlEntities = {
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

void Replace(std::string& str, const std::string& searchElement, const std::string& replaceableElement)
{
	if (searchElement.empty())
	{
		return;
	}

	size_t position = 0;
	size_t foundPos;
	std::string resultString;

	while (position < str.size())
	{
		foundPos = str.find(searchElement, position);
		resultString.append(str, position, foundPos - position);

		if (foundPos != std::string::npos)
		{
			resultString.append(replaceableElement);
			position = foundPos + searchElement.size();
		}
		else
		{
			break;
		}
	}

	str.swap(resultString);
}

std::string HtmlDecode(const std::string& html)
{
	std::string outString = html;

	for (auto& htmlEntity : htmlEntities)
	{
		Replace(outString, htmlEntity.searchElement, htmlEntity.replaceableElement);
	}

	return outString;
}
