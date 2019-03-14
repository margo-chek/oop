#include "pch.h"

#include "../process_vector/process_vector.h"

using namespace std;

const double EPS = 0.0001;


bool ArraysAreEqual(const vector<double>& input, const vector<double>& output)
{
	if (input.size() != output.size())
	{
		return false;
	}
	for (size_t i = 0; i < input.size(); i++)
	{
		if (fabs(input[i] - output[i]) >= EPS)
		{
			return false;
		}
	}
	return true;
}

TEST_CASE("input - empty vector, output - empty vector")
{
	vector<double> numbers = {};
	ProcessVector(numbers);
	CHECK(ArraysAreEqual(numbers, {}));
}

TEST_CASE("all elements are multiplied by the minimum")
{
	vector<double> numbers = { 10, 15, 13 };
	ProcessVector(numbers);
	CHECK(ArraysAreEqual(numbers, { 100, 150, 130 }));
}

TEST_CASE("all elements are multiplied by the minimum(double elements)")
{
	vector<double> numbers = { -3.1, 2.1, 3.7 };
	ProcessVector(numbers);
	CHECK(ArraysAreEqual(numbers,
		{ (-3.1 * (-3.1)), (2.1 * (-3.1)), (3.7 * (-3.1)) }));
}
