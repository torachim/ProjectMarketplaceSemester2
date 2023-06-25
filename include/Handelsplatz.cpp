#include <iostream>
#include<list>
using namespace std; 
namespace ProjectAlpha2{
class Handelsplatz{

    std::list<string> List;

    void anpassenListe(string Produkt,bool add){
    
            if(add==1){
                List.add(Produkt);
            }
            else{
                List.remove(Produkt);
            }
        }
    };
}
