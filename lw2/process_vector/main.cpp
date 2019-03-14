#include "pch.h"
#include "process_vector.h"

using namespace std;

int main()
{
	cout << "Enter your array: \n";
	vector<double> numbers;

	numbers = GetNumbers(cin);
	ProcessVector(numbers);
	SortVector(numbers);
	PrintVector(cout, numbers);

	return 0;
}

