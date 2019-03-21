#include "pch.h"

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout << "Invalid count of arguments." << std::endl
				  << "Usage: FindAndReplace.exe <input string> <search string> <replace string>"
				  << std::endl;
		return 1;
	}
	std::string subject;
	while (std::getline(std::cin, subject))
	{
		std::cout << FindAndReplace(subject, argv[2], argv[3]) << std::endl;
	}
	return 0;
}