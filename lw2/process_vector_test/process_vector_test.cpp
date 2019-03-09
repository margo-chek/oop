#include "pch.h"

#include "../process_vector/process_vector.h"

using namespace std;

// TEST_CASE("testing")
// {
//	REQUIRE(1 == GetSymbol(1));
//	REQUIRE(2 == GetSymbol(1));
// }

bool IsEqually(const vector<double> &input, const vector<double> &output)
{
	return input == output;
}

TEST_CASE("input - empty vector, output - empty vector")
{
	vector<double> numbers = {};
	ProcessVector(numbers);
	CHECK(IsEqually(numbers, {}));
}

TEST_CASE("all elements are multiplied by the minimum")
{
	vector<double> numbers = { 10, 15, 13 };
	ProcessVector(numbers);
	CHECK(IsEqually(numbers, { 100, 150, 130 }));
}


TEST_CASE("all elements are multiplied by the minimum = 0")
{
	vector<double> numbers = { 5, 0, 5.5 };
	ProcessVector(numbers);
	CHECK(IsEqually(numbers, { 0, 0, 0 }));
}


TEST_CASE("all elements are multiplied by the minimum(double elements)")
{
	vector<double> numbers = { -3.1, 2.1, 3.7 };
	ProcessVector(numbers);
	CHECK(IsEqually(numbers, { (-3.1*(-3.1)), (2.1*(-3.1)), (3.7*(-3.1)) }));
}


