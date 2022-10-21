#include "Sommet.hpp"
#include<iostream>
using namespace std;

Sommet::Sommet(char* const etiquette,Sommet* parent, int rang):
etiquette_(etiquette),parent_(parent),rang_(rang){}

Sommet::Sommet(const Sommet& l){
    *this = l;
}
Sommet::~Sommet(){}

char* Sommet::getEtiquette() const{
    return etiquette_;
}

void Sommet::setEtiquette(char* val){
    etiquette_ = val;
}


ostream &operator<<(ostream& out, const Sommet &p){
    out << p.getEtiquette() << endl;
    return out;
} 