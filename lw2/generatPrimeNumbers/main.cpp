#include "pch.h"
#include "generatePrimeNumbers.h"

using namespace std;

int main(int argc, char* argv[])
{
	int upperBound;

	if (!GetNumber(argv[1], upperBound) || (!CheckCountArgement(argc)))
	{
		return 1;
	}

	set<size_t> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(cout, primeNumbers);

	return 0;
}