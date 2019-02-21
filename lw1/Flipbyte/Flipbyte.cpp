﻿#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

uint8_t FlipByte(uint8_t byte) // uint8_t - Целый тип фиксированного размера (с положительным знаком) равный 8 битам
{
	uint8_t outputByte = 0;
	uint8_t inputByte = byte; // 1 байт = 8 бит

	for (int i = 0; i < 8; i++)
	{
		outputByte <<= 1; // Побитовый сдвиг влево, совмещённый с присваиванием
		outputByte = inputByte & 0x01 | outputByte; 
		inputByte >>= 1; // Побитовый сдвиг вправо, совмещённый с присваиванием
	}

	return outputByte;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		cout << "invalid argument count\n"
			<< "usage: flipbyte.exe <byte>";
		return 1;
	}

	try // try (пытаться) - начало блока исключений;
	{  // stoi - извлекает знаковое целое число из строки str
		int byte = std::stoi(argv[1]); // https://ru.cppreference.com/w/cpp/string/basic_string/stol
		if (byte < 0 || byte > 255)
		{
			cout << "Input number is not in byte range.\n";
			return 1;
		}
		cout << static_cast<int>(FlipByte(static_cast<uint8_t>(byte))) << "\n"; // static_cast - преобразует один статический тип, в другой
	}
	catch (const std::exception& e) // catch - начало блока, "ловящего" исключение;
	{
		cout << "!Error:" << e.what() << "!\n"; // what - Получить исключение идентификации строки
		return 1;
	}

	return 0;
}
