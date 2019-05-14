#include "pch.h"
#include "../Dictionary/Dictionary.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

bool IsEqualDictionary(const CDictionary& x, const CDictionary& y)
{
	return x.m_dict == y.m_dict;
}

TEST_CASE("FindTranslation returns empty vector if no translation")
{
	CDictionary dictionary;
	dictionary.m_dict.insert({ "hamster", "хомяк" });
	std::vector<std::string> word = dictionary.FindTranslation("cat");
	std::vector<std::string> emptyVector;
	CHECK(word == emptyVector);
}

TEST_CASE("FindTranslation returns translation if translation find")
{
	CDictionary dictionary;
	dictionary.dict.insert({ "hamster", "хомяк" });
	std::vector<std::string> word = dictionary.FindTranslation("hamster");
	std::vector<std::string> findVector = { "хомяк" };
	CHECK(word == findVector);
}

TEST_CASE("ToLowerCase transforms word in lower case")
{
	std::string word = "Cat";
	ToLowerCase(word);
	std::string wordInLowerCase = "cat";
	CHECK(word == wordInLowerCase);
}

TEST_CASE("AddNewWord adds a two-way translation to the dictionary") // двухсторонний перевод
{
	CDictionary dictionary;
	dictionary.m_dict.clear();

	dictionary.AddNewWord("cat", "кошка");
	std::vector<std::string> word = dictionary.FindTranslation("cat");
	std::vector<std::string> findVector = { "кошка" };
	CHECK(word == findVector);

	word = dictionary.FindTranslation("кошка");
	findVector = { "cat" };
	CHECK(word == findVector);
}

// не добавляет слово, если оно уже существует в словаре !!!
TEST_CASE("AddNewWord does not add a word, if it already exists in the dictionary")
{
	CDictionary dictionary;
	dictionary.dict.clear();

	dictionary.AddNewWord("cat", "кошка");
	size_t elementsAmount = dictionary.dict.size();
	dictionary.AddNewWord("cat", "кошка");
	size_t dubbleElementsAmount = dictionary.dict.size();
	CHECK(elementsAmount == dubbleElementsAmount);
}

TEST_CASE("ReadDictionary returns an empty dictionary if the stream is empty")
{
	std::string inputStrm = "";
	std::istringstream strm(inputStrm);
	CDictionary dictionary, newDictionary;// ??

	dictionary.ReadDictionary(dictionary, strm); //?? 

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
	CDictionary dictionary, newDictionary;

	dictionary.ReadDictionary(dictionary, strm);// ??
	dictionary.AddNewWord("hello", "привет");
	dictionary.AddNewWord("apple", "яблоко");

	CHECK(IsEqualDictionary(dictionary, newDictionary));
}

TEST_CASE("WriteDictionary returns an empty stream if the dictionary is empty")
{
	std::ostringstream outStrm;
	std::string resultStream = "";
	CDictionary dictionary;

	dictionary.WriteDictionary(dictionary, outStrm);// ??
	CHECK(outStrm.str() == resultStream);
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
	CDictionary dictionary;

	dictionary.AddNewWord("hello", "привет");
	Adictionary.ddNewWord("apple", "яблоко");

	dictionary.WriteDictionary(dictionary, outStrm);// ??
	CHECK(outStrm.str() == resultStream);
}
