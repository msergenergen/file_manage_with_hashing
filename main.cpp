#include "urun.h"
#include "HashTable.h"
#include "file_io.h"
#include "gui.h"
#include <sstream>

int main()
{

	std::string fileName = "Camera.txt";
	std::ifstream input;

	input.open(fileName, std::ios::in);		// DOSYA ACMA

	std::vector<std::string> invec; // TXT OKUNAN VERILER

	std::string in;

	while (std::getline(input, in))
	{
		invec.push_back(in); // DEGERLER OKUNUR
	}

	std::vector<URUN> urunVec; // STRİNG TO URUN
	char delimiter = '\t'; //AYRAC
	for (int i = 0; i < invec.size(); i++)
	{
		std::string isim;

		int releaseData;
		double MaXres;
		double zoom;
		double focus;
		double storege;
		double weigt;
		double price;


		size_t pos = invec[i].find(delimiter);
		std::string token = invec[i].substr(0, invec[i].find(delimiter));	// URUN ISMI AYRILIR
		invec[i].erase(0, token.size());

		std::stringstream ss(invec[i]);

		ss >> releaseData >> MaXres >> zoom >> focus >> storege >> weigt >> price; //URUN DIGER OZELLIKLERI

		URUN append;

		append.isim = token;
		append.releaseData = releaseData;
		append.MaXres = MaXres;
		append.price = price;
		append.zoom = zoom;
		append.focus = focus;
		append.storege = storege;
		append.weigt = weigt;

		urunVec.push_back(append);
	}


	urunVec.erase(urunVec.begin()); //ILK IKI VECTOR SILINIR
	urunVec.erase(urunVec.begin());

	for (int i = 0; i < urunVec.size(); i++) // SHOW URUN VEC
	{
		std::cout << i << " " << urunVec[i].isim << " " << urunVec[i].releaseData << " "
			<< urunVec[i].MaXres << " " << urunVec[i].zoom << " " << urunVec[i].focus
			<< " " << urunVec[i].storege << " " << urunVec[i].weigt << " " << urunVec[i].price << std::endl;
	}
	HashTable2 hashTable(urunVec);
	hashTable.show();
	writetoBinary(hashTable);
	std::cout << "bitti " << std::endl;
	//readfromBinary();
	
	/*
	URUN toFind;
	toFind.isim = "Fujifilm FinePix 4700 Zoom";
	auto x = findInBinary(toFind);
	deleteUrun(std::get<1>(x), std::get<2>(x));
	URUN toadd;
	toadd.isim = "MEHMET SERGEN ERGEN";
	addURUNtoBınary(toadd);
	*/


	menu_screen(urunVec);
	return 0;
}