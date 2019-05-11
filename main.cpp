#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <list>
#include <iterator>

typedef struct urun{
    
    std::string isim;
    int releaseData;
    double MaXres;
    double zoom;
    double focus;
    double storege;
    double weigt;
    double price;

    int getHashValue()
    {
        int value;
        for (int i = 0; i < isim.size(); i++)
        {
            value += isim.at(i);
        }
        
        return value % 97;
    }

    

}URUN;

typedef struct HashNode{

    URUN *nodeValue = nullptr;
    int key = -1;
    struct HashNode * next = nullptr;
    
    void datainit(URUN _urun)
    {
        nodeValue = new URUN;
        nodeValue->isim = _urun.isim;
        nodeValue->releaseData = _urun.releaseData;
        nodeValue->MaXres = _urun.MaXres;
        nodeValue->price = _urun.price;
        nodeValue->zoom = _urun.zoom;
        nodeValue->focus = _urun.focus;
        nodeValue->storege = _urun.storege;
        nodeValue->weigt = _urun.weigt;
        key = _urun.getHashValue();
    }

    void addNode(URUN _urun){
        if(this->nodeValue == nullptr)
        {
            datainit(_urun);
        }
        else
        {
        struct HashNode * tmp;
        tmp = this;
        while (tmp->next != nullptr)
        {
            tmp = tmp->next;
        }

        tmp->next = new struct HashNode;
        tmp->next->datainit(_urun);

        }
                    
    }

}HASHNODE;


class HashTable
{
    public:

    HashNode nodes[97];
    
    HashTable(std::vector<URUN> products){
        
        std::cout << "size of vector" << products.size()<<std::endl; 
        for (int i = 0; i < products.size(); i++)
        {
            nodes[products[i].getHashValue()].addNode(products[i]);
        }
        
    }

    void show(){
        int toplam = 0;
        for(int i = 0 ; i < 97 ; i++)
        {   

            HashNode *tmp;
            tmp = &nodes[i];
            if(tmp == nullptr)
            {
                continue;
            }
            while(tmp->next != nullptr)
            {
                std::cout <<i << " " <<nodes->nodeValue->isim <<" "<<tmp->nodeValue->price << std::endl;
                tmp = tmp->next;
                toplam++;
            }
        }
        std::cout << toplam << std::endl;
    }
};




class HashTable2
{
    public:

    std::list<URUN> hashNodes[97];
    
    HashTable2(std::vector<URUN> products){
        
        std::cout << "size of vector" << products.size()<<std::endl; 
        for (int i = 0; i < products.size(); i++)
        {
            hashNodes[products[i].getHashValue()].push_back(products[i]);
        }
        
    }
    void showlist(std::list <URUN> g) 
    {   
        st::list<URUN>::
        for()
    } 
    void show(){
        
        for (int i = 0; i < 97; i++)
        {
            for (int j = 0; i < hashNodes[i].size(); j++)
            {
                showlist(hashNodes[i]);
            }
            
        }
        
    }
};




int main()
{
    std::string fileName = "Camera.txt";
    std::ifstream input;

    input.open(fileName, std::ios::in);

    std::vector<std::string> invec;

    std::string in;
    
    while (std::getline(input, in))
    {
        invec.push_back(in);
    }

    std::vector<URUN> urunVec;
    char delimiter = '\t';
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
      

        size_t pos =invec[i].find(delimiter);
        std::string token = invec[i].substr(0, invec[i].find(delimiter));
        invec[i].erase(0,token.size());
        
        std::stringstream ss(invec[i]);
        
        ss >> releaseData >> MaXres >> zoom >> focus >> storege >> weigt >> price;
        
        

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
    
    for (int i = 0; i < urunVec.size(); i++)
    {
        std::cout << i << " " << urunVec[i].isim <<" "<<urunVec[i].releaseData<<" " 
            <<urunVec[i].MaXres<<" "<< urunVec[i].zoom<<" "<< urunVec[i].focus
            <<" "<<urunVec[i].storege << " " << urunVec[i].weigt << " " << urunVec[i].price<< std::endl;
    }
    
    HashTable2 hashTable(urunVec);
    hashTable.show();
    
    std::cout << "bitti " << std::endl;
    return 0;
}