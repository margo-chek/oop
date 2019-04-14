#include "pch.h"
#include "Car.h"
#include "DriveCar.h"

using namespace std;

int main()
{
	CCar car;
	CDriveCar driveCar(car, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!driveCar.ExecuteCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
}


