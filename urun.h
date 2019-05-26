#pragma once

#include <string>
#include <string.h>
#include <iostream>

typedef struct urun {

	std::string isim;
	int releaseData;
	double MaXres;
	double zoom;
	double focus;
	double storege;
	double weigt;
	double price;
	int hash1;
	int hash2;
	int getHashValue()
	{
		int value = 0;
		for (int i = 0; i < isim.size(); i++)
		{
			value += isim.at(i);
		}

		hash1 = value % 97;
		return value % 97;
	}

	int getHashValue2()
	{
		int value = 0;
		for (int i = 0; i < isim.size(); i++)
		{
			value += isim.at(i);
		}

		value = (value / 97) % 97;

		return value;
	}

	char* uruntoCharArray() {
		char* returnarrayPointer;
		double doubleValues[6];

		returnarrayPointer = new char[28 + (sizeof(int) * 2) + (sizeof(double) * 6)];

		doubleValues[0] = MaXres;
		doubleValues[1] = zoom;
		doubleValues[2] = focus;
		doubleValues[3] = storege;
		doubleValues[4] = weigt;
		doubleValues[5] = price;

		memmove(returnarrayPointer, isim.data(), 28);
		memmove(returnarrayPointer + 28, (char*)& this->releaseData, sizeof(int));
		memmove(returnarrayPointer + 32, (char*)& doubleValues, sizeof(double) * 6);

		return returnarrayPointer;
	}

	void toShow() {
		std::cout << std::endl << this->isim << " " << this->releaseData << " " <<
			this->zoom << " " << this->focus << " " << this->storege <<
			" " << this->weigt << " " << this->price << std::endl;
	}
}URUN;

URUN charArraytoURUN_80(char* buffer)
{
	// arrayin uzunlugu seksen olmalýdýr
	char* isim = new char[28];
	memcpy(isim, buffer, 28);
	URUN readURUN;
	readURUN.isim = isim;
	readURUN.releaseData = *(int*)& buffer[28];
	readURUN.MaXres = *(double*)& buffer[32];
	readURUN.zoom = *(double*)& buffer[40];
	readURUN.focus = *(double*)& buffer[48];
	readURUN.storege = *(double*)& buffer[56];
	readURUN.weigt = *(double*)& buffer[64];
	readURUN.price = *(double*)& buffer[72];

	//readURUN.toShow();
	return readURUN;
}
