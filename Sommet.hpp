#ifndef SOMMET_HPP
#define SOMMET_HPP
#include <iostream>
using namespace std;

class Sommet
{   
    string etiquette_; /* etiquette du sommet */

public:   
    Sommet* parent_;
    int rang_;        
    Sommet(string etiquette,Sommet* parent = 0,int rang = 0); /* Sommet avec une étiquette */
    // Sommet(const Sommet* s);
    // Sommet(const Sommet&); /* Sommet(copie) */
    virtual ~Sommet();
    string getEtiquette() const;
    void setEtiquette(string val);
    friend ostream &operator<<(ostream& out, const Sommet &x);
};

#endif