#include "pch.h"
#include "Dictionary.h"

using namespace std;

CDictionary::CDictionary(const string& fileName, istream& inputStream)
{
	m_dictionaryFileName = fileName;

	ReadDictionary(inputStream);

}


void CDictionary::AddNewWord(const string& word, const string& translation)
{
	if (translation.empty())
	{
		cout << "Слово \"" << word << "\" проигнорировано." << endl;
	}

	InsertIntoDictionary(word, translation);
	InsertIntoDictionary(translation, word);

	cout << "Слово \"" << word << "\" сохранено в словаре как \"" << translation << "\"." << endl;
	m_wasUpdated = true;
}


vector<string> CDictionary::FindTranslation(const string& word)
{
	auto rangeWordTranslation = m_dict.equal_range(word);

	if (distance(rangeWordTranslation.first, rangeWordTranslation.second) == 0) 
	{
		return {};
	}

	vector<string> translation;

	for_each(rangeWordTranslation.first, rangeWordTranslation.second, [&](const auto& currPair) 
	{
		translation.push_back(currPair.second);
	});
	return translation;
}

void CDictionary::SaveDictionary()
{
	char exit;
	cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом." << endl;

	cout << ">";
	cin >> exit;

	if ((exit == 'Y') || (exit == 'y'))
	{
		if (m_dictionaryFileName.empty())
		{
			cout << "Введите название словаря." << endl;
			cout << ">";
			cin >> m_dictionaryFileName;
		}

		ofstream outputFile(m_dictionaryFileName);
		// WriteDictionary(outputFile);
		cout << "Изменения сохранены. До свидания." << endl;
	}
	else
	{
		cout << "Изменения не сохранены. До свидания." << endl;
	}
}

bool CDictionary::GetWasUpdatedFlag() const
{
	return m_wasUpdated;
}


void CDictionary::InsertIntoDictionary(const string& word, const string& translation)
{
	if (!HasSameTranslation(word, translation))
	{
		m_dict.insert({ word, translation });
	}
}


bool CDictionary::HasSameTranslation(const string& word, const string& translation) const
{
	auto range = m_dict.equal_range(word);
	if (distance(range.first, range.second) == 0)
		return false;

	return any_of(range.first, range.second, [&](const auto& wordTranslationPair) -> bool {
		return wordTranslationPair.second == translation;
	});
}


/*void CDictionary::WriteDictionary(ostream& outputFile)
{
	for (auto& [word, translation] : m_dict)
	{
		outputFile << word << endl
				   << translation << endl;
	}
}*/

void CDictionary::ReadDictionary(istream& inputFile)
{
	string word, translation;

	while (std::getline(inputFile, word) && std::getline(inputFile, translation))
	{
		ToLowerCase(word);
		ToLowerCase(translation);

		InsertIntoDictionary(word, translation);
		InsertIntoDictionary(translation, word);	
	}

}

bool IsUpperCaseCharacter(unsigned char character)
{
	return (character >= 0x41 && character <= 0x5A) || (character >= 0xC0 && character <= 0xDF) || character == 0xA8;
}

void ToLowerCase(string& word)
{
	for (size_t i = 0; i < word.length(); i++)
	{
		auto currentCharacter = static_cast<unsigned char>(word[i]);

		if (IsUpperCaseCharacter(currentCharacter))
		{
			currentCharacter == 0xA8 ? currentCharacter += 16 : currentCharacter += 32;
			word[i] = currentCharacter;
		}
	}
}

