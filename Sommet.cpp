#include "Sommet.hpp"
#include<iostream>
using namespace std;

Sommet::Sommet(string etiquette,Sommet* parent, int rang):
etiquette_(etiquette),parent_(parent),rang_(rang){}

Sommet::Sommet(const Sommet* s): etiquette_{s->getEtiquette()}, parent_{s->parent_} {}

Sommet::Sommet(const Sommet& l){}
Sommet::~Sommet(){
}

string Sommet::getEtiquette() const{
    return etiquette_;
}

void Sommet::setEtiquette(char* val){
    etiquette_ = val;
}


ostream &operator<<(ostream& out, const Sommet &p){
    out << p.getEtiquette() << endl;
    return out;
} 