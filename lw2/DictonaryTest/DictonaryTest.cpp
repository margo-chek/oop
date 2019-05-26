#include "pch.h"
#include "../Dictionary/Dictionary.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void ExpectOperationSuccess(CDictionary& dictionary, const function<bool(CDictionary& dictionary)>& op, multimap<string, string> expectedDict,
	string expectedFileName, void expectedAddNewWord(const string& word, const string& translation), vector<string> expectedFindTranslation(const string& word),
	void expectedSaveDictionary(istream& inputStream, ostream& outputStream, const function<void(const multimap<string, string>& dict, const string& fileName)>& saverFunc))
{
	CHECK(op(dictionary));
	CHECK(dictionary.GetDict() == expectedDict);
	CHECK(dictionary.GetFileName() == expectedFileName);
	CHECK(dictionary.AddNewWord("cat", "кот") == expectedAddNewWord);
	CHECK(dictionary.FindTranslation("cat") == expectedFindTranslation);
	CHECK(dictionary.SaveDictionary(...) == expectedSaveDictionary);
}

void ExpectOperationFailure(const CDictionary& dictionary, const function<bool(CDictionary& dictionary)>& op)
{
	auto clone(dictionary);
	CHECK(!op(clone));
	CHECK(clone.GetDict() == dictionary.GetDict());
	CHECK(clone.GetFileName() == dictionary.GetFileName());
	CHECK(clone.AddNewWord(...) == dictionary.AddNewWord(...));
	CHECK(clone.FindTranslation(...) == dictionary.FindTranslation(...));
	CHECK(clone.SaveDictionary(...) == dictionary.SaveDictionary(...));
}

TEST_CASE("ToLowerCase transforms word in lower case")
{
	string word = "Cat";
	ToLowerCase(word);
	string wordInLowerCase = "cat";
	CHECK(word == wordInLowerCase);
}

TEST_CASE("FindTranslation returns empty vector if no translation")
{
	CDictionary dictionary;
	dictionary.GetDict.insert({ "hamster", "хомяк" });
	vector<string> word = dictionary.FindTranslation("cat");
	vector<string> emptyVector;
	CHECK(word == emptyVector);
}

TEST_CASE("FindTranslation returns translation if translation find")
{
	CDictionary dictionary;
	dictionary.GetDict.insert({ "hamster", "хомяк" });
	vector<string> word = dictionary.FindTranslation("hamster");
	vector<string> findVector = { "хомяк" };
	CHECK(word == findVector);
}


TEST_CASE("AddNewWord adds a two-way translation to the dictionary") // двухсторонний перевод
{
	CDictionary dictionary;
	dictionary.GetDict.clear();

	dictionary.AddNewWord("cat", "кошка");
	vector<string> word = dictionary.FindTranslation("cat");
	vector<string> findVector = { "кошка" };
	CHECK(word == findVector);

	word = dictionary.FindTranslation("кошка");
	findVector = { "cat" };
	CHECK(word == findVector);
}

// не добавляет слово, если оно уже существует в словаре !!!
TEST_CASE("AddNewWord does not add a word, if it already exists in the dictionary")
{
	CDictionary dictionary;
	dictionary.GetDict.clear();

	dictionary.AddNewWord("cat", "кошка");
	size_t elementsAmount = dictionary.GetDict.size();
	dictionary.AddNewWord("cat", "кошка");
	size_t dubbleElementsAmount = dictionary.GetDict.size();
	CHECK(elementsAmount == dubbleElementsAmount);
}

TEST_CASE("ReadDictionary returns an empty dictionary if the stream is empty")
{
	CDictionary dictionary;
	string inputStrm = "";
	istringstream strm(inputStrm);
	CDictionary dictionary, newDictionary;// ??

	dictionary.ReadDictionary(dictionary, strm); //?? 

	CHECK(IsEqualDictionary(dictionary, newDictionary));
}

TEST_CASE("ReadDictionary returns a dictionary from the input stream")
{
	CDictionary dictionary;
	string inputStrm = R"(hello
привет
apple
яблоко
)";
	istringstream strm(inputStrm);
	CDictionary dictionary, newDictionary;

	dictionary.ReadDictionary(dictionary, strm);// ??
	dictionary.AddNewWord("hello", "привет");
	dictionary.AddNewWord("apple", "яблоко");

	CHECK(IsEqualDictionary(dictionary, newDictionary));
}

TEST_CASE("WriteDictionary returns an empty stream if the dictionary is empty")
{
	ostringstream outStrm;
	string resultStream = "";
	CDictionary dictionary;

	dictionary.WriteDictionary(dictionary, outStrm);// нет??
	CHECK(outStrm.str() == resultStream);
}

TEST_CASE("WriteDictionary returns a stream from the dictionary")
{
	ostringstream outStrm;
	string resultStream = R"(apple
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

	dictionary.WriteDictionary(dictionary, outStrm);// нет??
	CHECK(outStrm.str() == resultStream);
}

SCENARIO("Dictionary saving")
{
	CDictionary dictionary;
	
	stringstream input;
	stringstream output;
	input << "Y";
	string outputFileName;
	dictionary.SaveDictionary("dictionary1.txt", input, output, [&outputFileName](const string& name) {
		outputFileName = name;
	});
	CHECK(input.eof());
	CHECK(outputFileName == "dictionary1.txt");
	CHECK(output.str() == "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом\n"
						  "Изменения сохранены. До свидания.\n");
}
