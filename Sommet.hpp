#ifndef SOMMET_HPP
#define SOMMET_HPP
#include <iostream>
using namespace std;

class Sommet
{   
    char* etiquette_; /* etiquette du sommet */

public:   
    Sommet* parent_;
    int rang_;        
    Sommet(char* const etiquette,Sommet* parent = 0,int rang = 0); /* Sommet avec une étiquette */
    Sommet(const Sommet&); /* Sommet à partir d'un autre sommet (copie) */
    virtual ~Sommet();
    char* getEtiquette() const;
    void setEtiquette(char* val);
    friend ostream &operator<<(ostream& out, const Sommet &x);
};

#endif