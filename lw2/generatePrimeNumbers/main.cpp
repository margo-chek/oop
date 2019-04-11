#include "pch.h"
#include "generatePrimeNumbers.h"

int main(int argc, char* argv[])
{
	int upperBound;

	if (!GetNumber(argv[1], upperBound) || (!CheckCountArgement(argc)))
	{
		return 1;
	}

	std::set<size_t> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(std::cout, primeNumbers);

	return 0;
}