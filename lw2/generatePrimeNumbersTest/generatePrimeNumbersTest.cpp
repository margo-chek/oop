#include "pch.h"
#include "../generatePrimeNumbers/generatePrimeNumbers.h"

bool IsEqual(const std::set<size_t>& x, const std::set<size_t>& y)
{
	return x == y;
}

TEST_CASE("Checking the correctness of the passed argument")
{
	int upperBond;

	CHECK(GetNumber("", upperBond) == false);
	CHECK(GetNumber("0", upperBond) == false);
	CHECK(GetNumber("100000001", upperBond) == false);
	CHECK(GetNumber("1", upperBond) == true);
	CHECK(GetNumber("100000000", upperBond) == true);
	CHECK(GetNumber("cat", upperBond) == false);
}

TEST_CASE("Test GeneratePrimeNumbersSet")
{
	CHECK(IsEqual(GeneratePrimeNumbersSet(10), { 2, 3, 5, 7 }));
	CHECK(IsEqual(GeneratePrimeNumbersSet(1), {}));
	CHECK(IsEqual(GeneratePrimeNumbersSet(0), {}));
	CHECK(IsEqual(GeneratePrimeNumbersSet(2), { 2 }));
	CHECK(IsEqual(GeneratePrimeNumbersSet(7), { 2, 3, 5, 7 }));
	CHECK(IsEqual(GeneratePrimeNumbersSet(17), { 2, 3, 5, 7, 11, 13, 17 }));
}

#ifndef _DEBUG
TEST_CASE("count the number of primes")
{
	CHECK(GeneratePrimeNumbersSet(100000000).size() == 5761455);
}
#endif