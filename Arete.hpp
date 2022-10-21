#ifndef Arete_HPP
#define Arete_HPP
#include "Sommet.hpp"
#include <iostream>
using namespace std;

class Arete
{
public:
    Sommet *premier_;  /* Le premier sommet d'Arete */
    int poids_;        /* Le poid du l'arête */
    Sommet *deuxieme_; /* Deuxieme sommet d'Arete */
public:

    /* Une Arete qui est définie par deux sommets et un poids */
    Arete(Sommet* premier_, int poids_, Sommet* deuxieme_);
    Arete(char* premier_, int poids_, char* deuxieme_);
    Arete(Arete&);
    ~Arete();
    Sommet* getPremier() const;
    Sommet* getDeuxieme() const;
    int getPoids() const;
    void setPoids(int val);
    friend ostream &operator<<(ostream& out, const Arete &x);

};

#endif