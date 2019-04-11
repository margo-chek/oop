#include "pch.h"
#include "generatePrimeNumbers.h"
#include <iostream>
#include <iterator>
#include <set>

bool CheckCountArgement(int countArgument)
{
	if (countArgument != 2)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: generatePrimeNumber.exe <upper bound>" << std::endl;
		return false;
	}

	return true;
}

bool GetNumber(const std::string& arg, int& upperBound)
{
	try
	{
		upperBound = std::stoi(arg);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	if ((upperBound < 1) || (upperBound > 100000000))
	{
		std::cout << "Invalid upper bound number\n"
				  << "Use a number between 1 and 100000000" << std::endl;
		return false;
	}

	return true;
}

void ExcludeMultiplesOf(size_t i, std::vector<bool>& isPrime)
{
	for (size_t j = i * i; j < isPrime.size(); j += i)
	{
		isPrime[j] = false;
	}
}

std::vector<bool> SiftEratosthenesSieve(size_t upperBound)
{
	std::vector<bool> isPrime(upperBound + 1, true);

	for (size_t i = 2; i * i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			ExcludeMultiplesOf(i, isPrime);
		}
	}

	return isPrime;
}

std::set<size_t> GetPrimeNumbers(const std::vector<bool>& isPrime)
{
	std::set<size_t> primeNumbers;

	for (size_t i = 2; i < isPrime.size(); ++i)
	{
		if (isPrime[i])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}

void PrintPrimeNumbers(std::ostream& output, const std::set<size_t>& primeNumbers)
{
	std::copy(primeNumbers.begin(), primeNumbers.end(), std::ostream_iterator<int>(output, " "));
}

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound)
{
	std::vector<bool> isPrime = SiftEratosthenesSieve(upperBound);
	std::set<size_t> primeNumbers = GetPrimeNumbers(isPrime);
	return primeNumbers;
}