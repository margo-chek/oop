#include "pch.h"
#pragma once
#include <set>

bool CheckArgumentCount(int countArgument);

bool GetNumber(const std::string& arg, int& upperBound);

void ExcludeMultiplesOf(int i, std::vector<bool>& isPrime);

std::set<int> GeneratePrimeNumbersSet(int upperBound);

std::vector<bool> SiftEratosthenesSieve(int upperBound);

std::set<int> GetPrimeNumbers(const std::vector<bool>& numbers);

void PrintPrimeNumbers(std::ostream& output, const std::set<int>& primeNumbers);
