#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

struct PairSearchReplace
{
	std::string searchElement;
	std::string replaceableElement;
};

std::string HtmlDecode(const std::string& html);
