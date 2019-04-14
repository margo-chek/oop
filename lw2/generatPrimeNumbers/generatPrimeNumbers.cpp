#include "pch.h"
#include "generatePrimeNumbers.h"

using namespace std;

bool CheckCountArgement(int countArgument)
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

void ExcludeMultiplesOf(size_t i, vector<bool>& isPrime)
{
	for (size_t j = i * i; j < isPrime.size(); j += i)
	{
		isPrime[j] = false;
	}
}

vector<bool> SiftEratosthenesSieve(size_t upperBound)
{
	vector<bool> isPrime(upperBound + 1, true);

	for (size_t i = 2; i * i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			ExcludeMultiplesOf(i, isPrime);
		}
	}

	return isPrime;
}

set<size_t> GetPrimeNumbers(const vector<bool>& isPrime)
{
	set<size_t> primeNumbers;

	for (size_t i = 2; i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}

void PrintPrimeNumbers(ostream& output, const set<size_t>& primeNumbers)
{
	copy(primeNumbers.begin(), primeNumbers.end(), ostream_iterator<int>(output, " "));
}

set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	vector<bool> isPrime = SiftEratosthenesSieve(upperBound);
	set<size_t> primeNumbers = GetPrimeNumbers(isPrime);
	return primeNumbers;
}