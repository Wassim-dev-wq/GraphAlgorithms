#include "Graph.hpp"
#include<iostream>
using namespace std;


Graph::Graph(Sommet** sommets,int nb_sm,Arete** arrets,int nb_arr):
sommets_(sommets),nbSommet_(nb_sm),arrets_(arrets),nbArrets_(nb_arr){}

/* Initialisation de chaque sommet */
void initSommets(Sommet* s){
    s->parent_ = s;
    s->rang_ = 0;
}


Sommet* find(Sommet* s){
    if(s->parent_!= s){
        s->parent_ = find(s);
    }
    return s->parent_;
}

void Union(Sommet* s1,Sommet* s2){
    Sommet* s1Racine = find(s1);
    Sommet* s2Racine = find(s2);
    if(s1Racine != s2Racine){
        if (s1Racine->rang_ < s2Racine->rang_)
        {
            s1Racine->parent_ = s2Racine;
        }
        else{
            s2Racine->parent_=s1Racine;
            if(s1Racine->rang_==s2Racine->rang_){
                s1Racine->rang_ = s2Racine->rang_ + 1;
            }
        }
        
    }
}

/*trier les arêtes de G par poids croissant*/
void Graph::trieArretes(){
    for(int i =1;i<nbArrets_;i++){

    }
}

Graph* Graph::kruskal(){
    Sommet** s = new Sommet*[nbSommet_];
    Arete** arret = new Arete*[nbArrets_];
    /* Init les parents de tous les sommets */
    for (int i = 0; i < nbSommet_; i++)
    {
        initSommets(sommets_[i]);
    }
    trieArretes(); /*trier les arêtes de G par poids croissant*/
    for(int i=0; i<nbArrets_;i++){
        if(find(arret[i]->premier_)!=find(arret[i]->deuxieme_)){ 
            // arret
            
        }
    }
    // return new Graph(sommet,nb_sommet,Aretes,nb_arretes)
}


int Graph::getSommePoids(){
    int poids=0;
    for(int i=0; i<nbArrets_ ; i++){
        poids = poids + arrets_[i]->getPoids();
    }
    return poids;
}


void Graph::afficherSommets() const{
    for (int i = 0; i < nbSommet_; i++)
    {
        cout << sommets_[i]->getEtiquette() << endl;
    }
    
}


Graph::~Graph(){}