#pragma once

#include "urun.h"
#include "HashTable.h"
#include <fstream>
#include <tuple>



void writetoBinary(HashTable2 table)
{
	std::string fileName = "CameraHash.bin";

	std::ofstream fileo;

	fileo.open(fileName, std::ios::binary | std::ios::out);

	for (int i = 0; i < 97; i++)
	{
		std::list<URUN>::iterator it;
		for (it = table.hashNodes[i].begin(); it != table.hashNodes[i].end(); it++)
		{
			char* ptr = it->uruntoCharArray();
			fileo.write(ptr, 80);
		}
	}
	fileo.close();
}

void readfromBinary()
{
	std::string fileName = "CameraHash.bin";

	std::ifstream fileo;

	fileo.open(fileName, std::ios::binary | std::ios::in);

	fileo.seekg(80 * 3 * 2);
	char buffer[80];
	fileo.read(buffer, 80);
	URUN readURUN = charArraytoURUN_80(buffer);
	//readURUN.toShow();

	fileo.close();
}




void deleteUrun(int row, int col) {

	std::string fileName = "CameraHash.bin";
	std::fstream fileo;
	fileo.open(fileName, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);



	fileo.seekp(row * 240 + col * 80);
	std::vector<char> buffer(80, '#');
	fileo.write(buffer.data(), 80);

	fileo.close();

}

std::pair<bool, int> findInList(URUN toFind, char* buffer) {
	// buffer ýn boyutu 240

	std::pair<bool, int> stateIndexPair;
	if (toFind.isim._Equal(charArraytoURUN_80(buffer).isim))
	{
		stateIndexPair.first = true;
		stateIndexPair.second = 0;
	}
	else if (toFind.isim._Equal(charArraytoURUN_80(buffer + 80).isim))
	{
		stateIndexPair.first = true;
		stateIndexPair.second = 1;
	}
	else if (toFind.isim._Equal(charArraytoURUN_80(buffer + 160).isim))
	{
		stateIndexPair.first = true;
		stateIndexPair.second = 2;
	}
	else
	{
		stateIndexPair.first = false;
		stateIndexPair.second = -1;
	}

	return stateIndexPair;
}

std::tuple<bool, int, int,int> findInBinary(URUN toFindURUN)
{
	// ARAMA YAPMAK ICIN STRÝNG DEGERININ GIRILMESI YETERLI

	std::fstream stream;
	stream.open("CameraHash.bin", std::ios::in | std::ios::binary);

	int indexTable = 0;
	bool returnState = false;
	if (stream.is_open()){}
	else
	{
		stream.open("CameraHash.bin", std::ios::in | std::ios::binary);
	}

	indexTable = toFindURUN.getHashValue();
	int pos = indexTable * 3 * 80;
	stream.seekg(pos);
	int appendValue = toFindURUN.getHashValue2();

	// Kaç sorguda bulunduðu ?
	int query_value = 0;

	bool state = true;
	int i = 1;
	do
	{
		char buffer[240];
		stream.read(buffer, 240);
		std::pair<bool, int> control = findInList(toFindURUN, buffer);
		if (control.first == false)
		{
			int append_pos = (appendValue - 1) * 3 * 80;
			int location = stream.tellg();
			int newPos = location + append_pos;
			stream.seekg(newPos);
			indexTable += appendValue;
			indexTable %= 97;
		}
		else {

			//std::cout << "BULUNAN " << indexTable << " " << control.second << std::endl;
			returnState = true;
			stream.close();
			std::cout << "< " << (i * 3) + control.second << " >" << " SORGU ARADI " << std::endl;
			return std::make_tuple(returnState, indexTable, control.second,(i*3) + control.second);
			//break;
		}

		i++;

	} while (state && i < 33);

	std::cout << "< "<< i * 3 <<" >"<< " SORGU ARADI " << " AMA BULAMADIM "<< std::endl;

	stream.close();

	return std::make_tuple(false, -1, -1,i);
}


void addURUNtoBýnary(URUN addURUN) {

	char* array = addURUN.uruntoCharArray();

	std::string fileName = "CameraHash.bin";
	std::fstream fileo;
	fileo.open(fileName, std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
	char buffer[80] = { '\0' };
	URUN nullURUN = charArraytoURUN_80(buffer);

	int i = 0;
	do
	{
		char bufferBýnary[240];
		fileo.seekg(addURUN.getHashValue() * 80 * 3 + i * 240);

		fileo.read(bufferBýnary, 240);
		std::pair<bool, int> control = findInList(nullURUN, bufferBýnary);
		if (control.first == true)
		{
			int location = fileo.tellg();
			location -= (3 - control.second) * 80;

			fileo.seekg(location);
			fileo.write(array, 80);
			fileo.close();
			break;
		}
		i++;
	} while (i < 97);
	fileo.close();
}