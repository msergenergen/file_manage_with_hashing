#pragma once
#include "urun.h"
#include "file_io.h"
#include "HashTable.h"
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
using namespace std;

void menu_screen(std::vector<URUN> urunVec)
{
	URUN adiniSenKoy;
	std::tuple<bool, int, int,int> tuple_find;
	char op = 's';
	std::string mystr;
	std::string file_name;
	int release_date;
	double max_resolution;
	double zoom_wide;
	double focuc_range;
	double storage_memory;
	double weight;
	double price;

	int foundCount = 0;
	while (op != 'Q')
	{
		cout << "Veri Y�netimi ve Dosya Yap�lar� �dev-3 Hash ile Dosya ��lemleri " << endl;
		cout << "***************************************************************" << endl;
		cout << "L�tfen i�lem se�iniz." << endl;
		cout << " 1) Kay�t Arama " << endl;
		cout << " 2) Kay�t Silme" << endl;
		cout << " 3) Kay�t Ekleme" << endl;
		cout << " 4) Dosya �nceleme" << endl;
		cout << " Q) ��k�� " << endl;

		//op = getch();
		cin >> op;
		switch (op)
		{

		case '1':
			cout << "************************* KAYIT ARAMA ************************* " << endl;
			cout << " Aranacak kay�t ismini giriniz." ;

			cin.ignore();
			getline(cin , file_name , '\n');
			
			adiniSenKoy.isim = file_name;
			tuple_find = findInBinary(adiniSenKoy);
			cout << "BULUNMA DURUMU " << std::get<0>(tuple_find) << endl << "TABLO YERI ( " << std::get<1>(tuple_find) << " , " << std::get<2>(tuple_find) << " )" << endl;

			cout << "Kay�t sorgu say�s�: ";
			break;

		case '2':
			cout << "************************* KAYIT S�LME ************************* " << endl;
			cout << " Silinecek kay�t ismini giriniz. " ;
			

			cin.ignore();
			getline(cin, file_name, '\n');

			adiniSenKoy.isim = file_name;
			tuple_find = findInBinary(adiniSenKoy);
			deleteUrun(std::get<1>(tuple_find), std::get<2>(tuple_find));

			break;

		case '3':
			cout << "************************* KAYIT EKLEME ************************* " << endl;
			cout << " Eklenecek �r�n i�in model ismini giriniz.";

			cin.ignore();
			getline(cin, file_name, '\n');
			
			adiniSenKoy.isim = file_name;
			cout << " Eklenecek �r�n i�in ��k�� tarihini giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			//getline(cin, mystr);
			stringstream(mystr) >> release_date;
			adiniSenKoy.releaseData = release_date;
			cout << " Eklenecek �r�n i�in maksimum ��z�n�rl���n� giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> max_resolution;
			adiniSenKoy.MaXres = max_resolution;
			cout << " Eklenecek �r�n i�in zoom de�eri giriniz.";

			cin.ignore();
			getline(cin, mystr, '\n');

			
			stringstream(mystr) >> zoom_wide;
			adiniSenKoy.zoom = zoom_wide;
			cout << " Eklenecek �r�n i�in focus de�eri giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> focuc_range;
			adiniSenKoy.focus = focuc_range;
			cout << " Eklenecek �r�n i�in depolama miktar� giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> storage_memory;
			adiniSenKoy.storege = storage_memory;
			cout << " Eklenecek �r�n i�in a��rl�k de�eri giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> weight;
			adiniSenKoy.weigt = weight;
			cout << " Eklenecek �r�n i�in fiyat de�eri giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> price;
			adiniSenKoy.price = price;


			addURUNtoB�nary(adiniSenKoy);

			cout << "Kay�t ba�ar� ile eklenmi�tir.";
			break;

		case '4':
			cout << "************************* KAYIT �NCELEME ************************* " << endl;
			
			
			for (int i = 0; i < urunVec.size(); i++)
			{
				foundCount += std::get<3>(findInBinary(urunVec[i]));
			}

			cout << "ORTALAMA ARAMA UZUNLU�U: " << foundCount/urunVec.size() <<endl;
			
			break;
		case 'Q':
			cout << "DOSYA ��LEMLER� MEN�S� SONA ERD�R�L�YOR." << endl;
			return;
		default:
			cout << "Ge�ersiz i�lem l�tfen ge�erli bir i�lem giriniz.";
		}
	}
}
	