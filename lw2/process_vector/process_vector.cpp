#include "pch.h"
#include "process_vector.h"

using namespace std;


vector<double> GetVector(istream &input)
{
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	return numbers;
}

void SortVector(vector<double>& data)
{
	sort(data.begin(), data.end());
}

void ProcessVector(vector<double> &numbers)
{
	if (numbers.empty())
	{
		return;
	}

	const double minElement = *min_element(numbers.begin(), numbers.end());
	transform(numbers.begin(), numbers.end(), numbers.begin(), [=](double number) {return number = number * minElement; });
}

void PrintVector(ostream &output, const vector<double> &numbers)
{
	cout << fixed << setprecision(3);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(output, " "));
	cout << endl;
}
