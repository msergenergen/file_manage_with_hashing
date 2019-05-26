#pragma once
#include "urun.h"
#include <list>
#include <vector>
#include <iterator>

class HashTable2
{
public:

	std::list<URUN> hashNodes[97];

	HashTable2(std::vector<URUN> products) {

		std::cout << "size of vector" << products.size() << std::endl;
		for (int i = 0; i < products.size(); i++)
		{

			if (hashNodes[products[i].getHashValue()].size() < 3)
			{
				hashNodes[products[i].getHashValue()].push_back(products[i]);
			}
			else {

				int index = 0;
				index = products[i].getHashValue();
				index += products[i].getHashValue2();
				while (hashNodes[index % 97].size() >= 3)
				{
					index += products[i].getHashValue2();
				}
				hashNodes[index % 97].push_back(products[i]);
			}

		}
		fillHashTable();
	}
	void showlist(std::list <URUN> g)
	{
		std::list<URUN>::iterator it;

		for (it = g.begin(); it != g.end(); it++)
		{
			std::cout << it->isim << std::endl;
		}
	}

	void fillHashTable() {
		char buffer[80] = { '\0' };
		URUN nullURUN = charArraytoURUN_80(buffer);

		for (int i = 0; i < 97; i++)
		{
			if (hashNodes[i].size() < 3)
			{
				while (hashNodes[i].size() < 3) {
					hashNodes[i].push_back(nullURUN);
				}

			}
		}
	}
	void show() {

		for (int i = 0; i < 97; i++)
		{

			showlist(hashNodes[i]);

		}

	}

};