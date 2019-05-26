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
		cout << "Veri Yönetimi ve Dosya Yapýlarý Ödev-3 Hash ile Dosya Ýþlemleri " << endl;
		cout << "***************************************************************" << endl;
		cout << "Lütfen iþlem seçiniz." << endl;
		cout << " 1) Kayýt Arama " << endl;
		cout << " 2) Kayýt Silme" << endl;
		cout << " 3) Kayýt Ekleme" << endl;
		cout << " 4) Dosya Ýnceleme" << endl;
		cout << " Q) Çýkýþ " << endl;

		//op = getch();
		cin >> op;
		switch (op)
		{

		case '1':
			cout << "************************* KAYIT ARAMA ************************* " << endl;
			cout << " Aranacak kayýt ismini giriniz." ;

			cin.ignore();
			getline(cin , file_name , '\n');
			
			adiniSenKoy.isim = file_name;
			tuple_find = findInBinary(adiniSenKoy);
			cout << "BULUNMA DURUMU " << std::get<0>(tuple_find) << endl << "TABLO YERI ( " << std::get<1>(tuple_find) << " , " << std::get<2>(tuple_find) << " )" << endl;

			cout << "Kayýt sorgu sayýsý: ";
			break;

		case '2':
			cout << "************************* KAYIT SÝLME ************************* " << endl;
			cout << " Silinecek kayýt ismini giriniz. " ;
			

			cin.ignore();
			getline(cin, file_name, '\n');

			adiniSenKoy.isim = file_name;
			tuple_find = findInBinary(adiniSenKoy);
			deleteUrun(std::get<1>(tuple_find), std::get<2>(tuple_find));

			break;

		case '3':
			cout << "************************* KAYIT EKLEME ************************* " << endl;
			cout << " Eklenecek ürün için model ismini giriniz.";

			cin.ignore();
			getline(cin, file_name, '\n');
			
			adiniSenKoy.isim = file_name;
			cout << " Eklenecek ürün için çýkýþ tarihini giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			//getline(cin, mystr);
			stringstream(mystr) >> release_date;
			adiniSenKoy.releaseData = release_date;
			cout << " Eklenecek ürün için maksimum çözünürlüðünü giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> max_resolution;
			adiniSenKoy.MaXres = max_resolution;
			cout << " Eklenecek ürün için zoom deðeri giriniz.";

			cin.ignore();
			getline(cin, mystr, '\n');

			
			stringstream(mystr) >> zoom_wide;
			adiniSenKoy.zoom = zoom_wide;
			cout << " Eklenecek ürün için focus deðeri giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> focuc_range;
			adiniSenKoy.focus = focuc_range;
			cout << " Eklenecek ürün için depolama miktarý giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> storage_memory;
			adiniSenKoy.storege = storage_memory;
			cout << " Eklenecek ürün için aðýrlýk deðeri giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> weight;
			adiniSenKoy.weigt = weight;
			cout << " Eklenecek ürün için fiyat deðeri giriniz.";
			
			cin.ignore();
			getline(cin, mystr, '\n');


			stringstream(mystr) >> price;
			adiniSenKoy.price = price;


			addURUNtoBýnary(adiniSenKoy);

			cout << "Kayýt baþarý ile eklenmiþtir.";
			break;

		case '4':
			cout << "************************* KAYIT ÝNCELEME ************************* " << endl;
			
			
			for (int i = 0; i < urunVec.size(); i++)
			{
				foundCount += std::get<3>(findInBinary(urunVec[i]));
			}

			cout << "ORTALAMA ARAMA UZUNLUÐU: " << foundCount/urunVec.size() <<endl;
			
			break;
		case 'Q':
			cout << "DOSYA ÝÞLEMLERÝ MENÜSÜ SONA ERDÝRÝLÝYOR." << endl;
			return;
		default:
			cout << "Geçersiz iþlem lütfen geçerli bir iþlem giriniz.";
		}
	}
}
	