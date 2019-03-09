#pragma once

#include "pch.h"

// int GetSymbol(int ch);


std::vector<double> GetVector(std::istream &input);

void ProcessVector(std::vector<double> &numbers);

void SortVector(std::vector<double>& data);

void PrintVector(std::ostream &output, const std::vector<double> &numbers);

