#include "pch.h"
#include "generatePrimeNumbers.h"

using namespace std;

int main(int argc, char* argv[])
{
	int upperBound;

	if ((!CheckArgumentCount(argc)) || (!GetNumber(argv[1], upperBound)))
	{
		return 1;
	}

	set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	PrintPrimeNumbers(cout, primeNumbers);

	return 0;
}