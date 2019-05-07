#include "pch.h"
#include "../Dictionary/dictionary.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

bool IsEqualDictionary(const Dictionary& x, const Dictionary& y)
{
	return x.dict == y.dict && x.dictionaryFileName == y.dictionaryFileName && x.wasEdited == y.wasEdited;
}

TEST_CASE("FindTranslation returns empty vector if no translation")
{
	Dictionary dictionary;
	dictionary.dict.insert({ "hamster", "хомяк" });
	std::vector<std::string> word = FindTranslation("cat", dictionary);
	std::vector<std::string> emptyVector;
	CHECK(word == emptyVector);
}

TEST_CASE("FindTranslation returns translation if translation find")
{
	Dictionary dictionary;
	dictionary.dict.insert({ "hamster", "хомяк" });
	std::vector<std::string> word = FindTranslation("hamster", dictionary);
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
	Dictionary dictionary;
	dictionary.dict.clear();

	AddNewWord("cat", "кошка", dictionary);
	std::vector<std::string> word = FindTranslation("cat", dictionary);
	std::vector<std::string> findVector = { "кошка" };
	CHECK(word == findVector);

	word = FindTranslation("кошка", dictionary);
	findVector = { "cat" };
	CHECK(word == findVector);
}
/*
// не добавляет слово, если оно уже существует в словаре !!!
TEST_CASE("AddNewWord does not add a word, if it already exists in the dictionary")
{
	Dictionary dictionary;
	dictionary.dict.insert({ "cat", "кошка" });

	AddNewWord("cat", "хомяк", dictionary);
	std::vector<std::string> word = FindTranslation("cat", dictionary);
	std::vector<std::string> findVector = { "кошка" };
	CHECK(word == findVector);
}*/
/*Создать словарь, потом черед AddNewWord добавить в него слово, потом, через size() проверить количество
элементов в словаре, потом повторить вставку того же слова через AddNewWord, потом получить количество элементов
в словаре через size() и сравнить с предыдущим*/

TEST_CASE("ReadDictionary returns an empty dictionary if the stream is empty")
{
	std::string inputStrm = "";
	std::istringstream strm(inputStrm);
	Dictionary dictionary, newDictionary;

	ReadDictionary(dictionary, strm);

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

	ReadDictionary(dictionary, strm);
	AddNewWord("hello", "привет", newDictionary);
	AddNewWord("apple", "яблоко", newDictionary);

	CHECK(IsEqualDictionary(dictionary, newDictionary));
}

TEST_CASE("WriteDictionary returns an empty stream if the dictionary is empty")
{
	std::ostringstream outStrm;
	std::string resultStream = "";
	Dictionary dictionary;

	WriteDictionary(dictionary, outStrm);
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
	Dictionary dictionary;

	AddNewWord("hello", "привет", dictionary);
	AddNewWord("apple", "яблоко", dictionary);

	WriteDictionary(dictionary, outStrm);
	CHECK(outStrm.str() == resultStream);
}
