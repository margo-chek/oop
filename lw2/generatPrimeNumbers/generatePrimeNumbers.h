#include "pch.h" 
#pragma once
#include <set>

bool CheckCountArgement(int countArgument);

bool GetNumber(const std::string& arg, int& upperBound);

void ExcludeMultiplesOf(size_t i, std::vector<bool>& isPrime);

std::set<size_t> GeneratePrimeNumbersSet(size_t upperBound);

std::vector<bool> SiftEratosthenesSieve(size_t upperBound);

std::set<size_t> GetPrimeNumbers(const std::vector<bool>& numbers);

void PrintPrimeNumbers(std::ostream& output, const std::set<size_t>& primeNumbers);
