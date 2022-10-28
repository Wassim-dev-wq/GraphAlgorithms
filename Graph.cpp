#include "Graph.hpp"
#include <iostream>
#include <string.h>
using namespace std;

Graph::Graph(Sommet **sommets, int nb_sm, Arete **arrets, int nb_arr) : sommets_(sommets), nbSommet_(nb_sm), arrets_(arrets), nbArrets_(nb_arr) {}
Graph::Graph(Graph* g) : sommets_(g->getSommets()), nbSommet_(g->getNbSommet()), arrets_(g->getAretes()), nbArrets_(g->getNbArete()) {}
Graph::Graph(const Graph& g){}

/* Initialisation de chaque sommet */
void initSommets(Sommet *s)
{
    s->parent_ = s;
    s->rang_ = 0;
}

Sommet *find(Sommet *s)
{
    if (s->parent_ != s)
    {
        s->parent_ = find(s->parent_);
    }
    return s->parent_;
}

void Union(Sommet *s1, Sommet *s2)
{
    Sommet *s1Racine = find(s1);
    Sommet *s2Racine = find(s2);
    if (s1Racine != s2Racine)
    {
        if (s1Racine->rang_ < s2Racine->rang_)
        {
            s1Racine->parent_ = s2Racine;
        }
        else
        {
            s2Racine->parent_ = s1Racine;
            if (s1Racine->rang_ == s2Racine->rang_)
            {
                s1Racine->rang_ = s2Racine->rang_ + 1;
            }
        }
    }
}

/* https://www.geeksforgeeks.org/cpp-program-for-quicksort/ || Source algo*/
int partition(Arete **arr, int debut, int fin)
{

    int pivot = arr[debut]->getPoids();

    int count = 0;
    for (int i = debut + 1; i <= fin; ++i)
    {
        if (arr[i]->getPoids() <= pivot)
        {
            count++;
        }
    }
    int pivotIndex = debut + count;
    swap(arr[pivotIndex], arr[debut]);

    int i = debut, j = fin;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i]->getPoids() <= pivot)
        {
            i++;
        }

        while (arr[j]->getPoids() > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(Arete **arr, int debut, int fin)
{

    if (debut >= fin)
        return;

    int p = partition(arr, debut, fin - 1);

    quickSort(arr, debut, p - 1);

    quickSort(arr, p + 1, fin);
}

Graph *Graph::kruskal()
{
    Sommet **s = new Sommet *[nbSommet_];
    Arete **arret = new Arete *[nbArrets_];
    int nbSommet_kruskal = 0; /* A CHANGER " DOIT ETRE ETIQUETTE */
    int nbArrets_kruskal = 0;
    /* Init les parents de tous les sommets */
    for (int i = 0; i < nbSommet_; i++)
        initSommets(sommets_[i]);
    quickSort(arrets_, 0, nbArrets_); /*trier les arêtes de G par poids croissant*/

    for (int i = 0; i < nbArrets_; i++)
    {
        if (find(arrets_[i]->getPremier()) != find(arrets_[i]->getDeuxieme()))
        {
            arret[nbSommet_kruskal] = arrets_[i];
            nbSommet_kruskal++;
            Union(arrets_[i]->getPremier(), arrets_[i]->getDeuxieme());
            nbArrets_kruskal++;
        }
    }
    for (int i = 0; i < nbSommet_; i++)
        s[i] = new Sommet(to_string(i), 0, 0);/* creation des sommets a partir de les autres sommets*/
    return new Graph(s, nbSommet_kruskal, arret,nbArrets_kruskal);
}

int Graph::getSommePoids()
{
    int poids = 0;
    for (int i = 0; i < nbArrets_; i++)
        poids = poids + arrets_[i]->getPoids();
    return poids;
}

Graph::~Graph(){  
    delete[] sommets_;  
    delete[] arrets_;
}

void Graph::ajoute_sommet(string s){
    Sommet* tmp = new Sommet{s};
    this->ajoute_sommet(tmp);
}

void Graph::ajoute_sommet(Sommet *s){
    for (int i = 0; i < nbSommet_; i++){
        if(sommets_[i] == s){
            return;
        }
    }
    sommets_[nbSommet_] = s;
    nbSommet_++;
}

void Graph::ajoute_arete(Arete* a){
    for (int i = 0; i < nbArrets_; i++){
        if(arrets_[i] == a){
            return;
        }
    }
    arrets_[nbArrets_] = a;
    nbArrets_++;
    
}
void Graph::ajoute_arete(Sommet *premier,Sommet* deuxieme, int poids){
    Arete* tmp = new Arete{premier,poids,deuxieme};
    this->ajoute_arete(tmp);
    this->ajoute_sommet(premier);
    this->ajoute_sommet(deuxieme);
    
}
void Graph::ajoute_arete(string premier,string deuxieme, int poids){
    Sommet* tmp1 = new Sommet{premier};
    Sommet* tmp2 = new Sommet{deuxieme};
    this->ajoute_arete(tmp1,tmp2,poids);
}

void Graph::symetrise(){
    int count = nbArrets_;
    for (int i = 0; i < 3; i++){ 
        ajoute_arete(arrets_[i]->getDeuxieme(),arrets_[i]->getPremier(),arrets_[i]->getPoids());
    }
    cout << nbArrets_ << endl;
}

void Graph::afficherSommets() const
{
    for (int i = 0; i < nbSommet_; i++)
        cout << sommets_[i]->getEtiquette()<<" ";
    cout << endl;
}

int Graph::getNbSommet() const{
    return nbSommet_;
}

int Graph::getNbArete() const{
    return nbArrets_;
}

Sommet** Graph::getSommets() const{
    return sommets_;
}

Arete** Graph::getAretes() const{
    return arrets_;
}

ostream &operator<<(ostream& out, const Graph &p){
    int i;
    Sommet** sommets = p.getSommets();
    Arete** aretes = p.getAretes();
    out << "Sommet : ";
    
    for (i = 0; i < p.getNbSommet()-1 ; i++){
        out << sommets[i]->getEtiquette() << ", ";
    }
    out << sommets[i]->getEtiquette() << endl;

    out << "Aretes : " << endl;
    for (i = 0; i < p.getNbArete() ; i++){
        out << aretes[i]->getPremier()->getEtiquette() << " -- " << aretes[i]->getPoids() <<" --> " << aretes[i]->getDeuxieme()->getEtiquette() << endl;
    }
    return out;
}