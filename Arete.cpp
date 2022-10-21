#include "Arete.hpp"
#include<iostream>
using namespace std;


Arete::Arete(Sommet* premier,int poids,Sommet* deuxieme):
premier_(premier),poids_(poids),deuxieme_(deuxieme){}

/* Creation des sommets au moment du création de l'arrete */
Arete::Arete(char* premier,int poids,char* deuxieme):
premier_(new Sommet{premier,0,0}),poids_(poids),deuxieme_(new Sommet{deuxieme,0,0}){}

Arete::Arete(Arete& a){
    *this = a;
}

Sommet* Arete::getPremier() const {
    return premier_;
}

Sommet* Arete::getDeuxieme() const {
    return deuxieme_;
}

int Arete::getPoids() const {
    return poids_;
}

void Arete::setPoids(int val){
    poids_ = val;
}

Arete::~Arete(){
}

ostream &operator<<(ostream& out, const Arete &p){
    out << p.getPremier()->getEtiquette() << " -- " << p.getPoids() << " --> " << p.getDeuxieme()->getEtiquette() << endl;
    return out;
}