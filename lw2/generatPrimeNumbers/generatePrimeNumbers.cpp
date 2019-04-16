#include "pch.h"
#include "generatePrimeNumbers.h"

using namespace std;

bool CheckArgumentCount(int countArgument)
{
	if (countArgument != 2)
	{
		cerr << "Invalid argument count\n"
				  << "Usage: generatePrimeNumber.exe <upper bound>" << endl;
		return false;
	}

	return true;
}

bool GetNumber(const string& arg, int& upperBound) 
{
	try
	{
		upperBound = stoi(arg);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
		return false;
	}

	if ((upperBound < 1) || (upperBound > 100000000))
	{
		cerr << "Invalid upper bound number\n"
				  << "Use a number between 1 and 100000000" << endl;
		return false;
	}

	return true;
}

void ExcludeMultiplesOf(int i, vector<bool>& isPrime)
{
	for (int j = i * i; j < isPrime.size(); j += i)
	{
		isPrime[j] = false;
	}
}

vector<bool> SiftEratosthenesSieve(int upperBound)
{
	vector<bool> isPrime(upperBound + 1, true);

	for (int i = 2; i * i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			ExcludeMultiplesOf(i, isPrime);
		}
	}

	return isPrime;
}


// emplace_hint  позволяет указать место, перед которым вставить элемент (непосредственно перед hint)
// В multimap всегда вставка произойдёт и вернётся итератор, там могут быть одинаковые пары ключ-значение
// Если в контейнере все значения уникальны, то emplace_hint не вставит элемент, если он уже существует в контейнере 
// и вернёт итератор на тот, который есть в контейнере

// std::map emplace функции возвращают std::pair<iterator,bool> 
// emplace вставляет элемент куда угодно и возвращает пару итератора и bool значения, которое говорит о том, была ли вставка

set<int> GetPrimeNumbers(const vector<bool>& isPrime)
{
	set<int> primeNumbers;

	for (int i = 2; i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}

void PrintPrimeNumbers(ostream& output, const set<int>& primeNumbers)
{
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(output, " "));
}

set<int> GeneratePrimeNumbersSet(int upperBound)
{
	vector<bool> isPrime = SiftEratosthenesSieve(upperBound);
	set<int> primeNumbers = GetPrimeNumbers(isPrime);
	return primeNumbers;
}