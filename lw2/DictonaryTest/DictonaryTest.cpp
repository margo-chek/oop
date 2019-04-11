#include "pch.h"
#include "../Dictionary/dictionary.h"
#include <sstream>

bool IsEqual(const std::string& x, const std::string& y)
{
	return x == y;
}

bool IsEqualDictionary(const Dictionary& x, const Dictionary& y)
{
	return x == y;
}

TEST_CASE("FindTranslation returns empty string if no translation")
{
	Dictionary dictionary;
	dictionary.insert({ "hamster", "хомяк" });
	auto word = FindTranslation("cat", dictionary);
	CHECK(IsEqual(word, ""));
}

TEST_CASE("FindTranslation returns translation if translation find")
{
	Dictionary dictionary;
	dictionary.insert({ "hamster", "хомяк" });
	auto word = FindTranslation("hamster", dictionary);
	CHECK(IsEqual(word, "хомяк"));
}

TEST_CASE("AddTranslation adds a two-way translation to the dictionary")
{
	Dictionary dictionary;
	dictionary.clear();

	AddTranslation("cat", "кошка", dictionary);
	auto word = FindTranslation("cat", dictionary);
	CHECK(IsEqual(word, "кошка"));

	word = FindTranslation("кошка", dictionary);
	CHECK(IsEqual(word, "cat"));
}

TEST_CASE("AddTranslation does not add a word, if it already exists in the dictionary")
{
	Dictionary dictionary;
	dictionary.insert({ "cat", "кошка" });

	AddTranslation("cat", "хомяк", dictionary);
	auto word = FindTranslation("cat", dictionary);
	CHECK(IsEqual(word, "кошка"));
}

TEST_CASE("ReadDictionary returns an empty dictionary if the stream is empty")
{
	std::string inputStrm = "";
	std::istringstream strm(inputStrm);
	Dictionary dictionary, newDictionary;

	dictionary = ReadDictionary(strm);

	CHECK(IsEqualDictionary(dictionary, newDictionary));
}

TEST_CASE("ReadDictionary returns a dictionary from the input stream")
{
	std::string inputStrm = R"(hello
привет
apple
яблоко
)";
	std::istringstream strm(inputStrm);
	Dictionary dictionary, newDictionary;

	dictionary = ReadDictionary(strm);
	AddTranslation("hello", "привет", newDictionary);
	AddTranslation("apple", "яблоко", newDictionary);

	CHECK(IsEqualDictionary(dictionary, newDictionary));
}

TEST_CASE("WriteDictionary returns an empty stream if the dictionary is empty")
{
	std::ostringstream outStrm;
	std::string resultStream = "";
	Dictionary dictionary;

	WriteDictionary(outStrm, dictionary);
	CHECK(IsEqual(outStrm.str(), resultStream));
}

TEST_CASE("WriteDictionary returns a stream from the dictionary")
{
	std::ostringstream outStrm;
	std::string resultStream = R"(apple
яблоко
hello
привет
привет
hello
яблоко
apple
)";
	Dictionary dictionary;

	AddTranslation("hello", "привет", dictionary);
	AddTranslation("apple", "яблоко", dictionary);

	WriteDictionary(outStrm, dictionary);
	CHECK(IsEqual(outStrm.str(), resultStream));
}
