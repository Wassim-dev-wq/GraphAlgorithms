#include "Graph.hpp"
#include <iostream>
#include <string.h>
using namespace std;

Graph::Graph(Sommet **sommets, int nb_sm, Arete **arrets, int nb_arr) : sommets_(sommets), nbSommet_(nb_sm), arrets_(arrets), nbArrets_(nb_arr) {}

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
        if (find(arrets_[i]->premier_) != find(arrets_[i]->deuxieme_))
        {
            arret[nbSommet_kruskal] = arrets_[i];
            nbSommet_kruskal++;
            Union(arrets_[i]->premier_, arrets_[i]->deuxieme_);
            nbArrets_kruskal++;
        }
    }
    for (int i = 0; i < nbSommet_; i++)
        s[i] = new Sommet((char *)"1", 0, 0);/* creation des sommets a partir de les autres sommets*/
    return new Graph(s, nbSommet_kruskal, arret,nbArrets_kruskal);
}

int Graph::getSommePoids()
{
    int poids = 0;
    for (int i = 0; i < nbArrets_; i++)
        poids = poids + arrets_[i]->getPoids();
    return poids;
}

void Graph::afficherSommets() const
{
    for (int i = 0; i < nbSommet_; i++)
        cout << sommets_[i]->getEtiquette() << endl;
}

void Graph::afficherGraph() const
{
    cout << "\nSommet: ";
    for (int i = 0; i < nbSommet_; i++)
        cout << sommets_[i]->getEtiquette() << " ";

    cout << "\nArrets: " << nbArrets_ << endl;
    for (int j = 0; j < nbArrets_; j++)
    {   
        cout << (arrets_[j])->premier_->getEtiquette() << ", ";
        cout << (arrets_[j])->poids_ << ", ";
        cout << (arrets_[j])->deuxieme_->getEtiquette() << endl;
    }
}

Graph::~Graph(){
    for(int i=0; i <nbSommet_;i++){
        delete sommets_[i];
        /*  [ERROOR] 0 Object deleted !!!!!!!!!! */
        cout << "Destruction sommet : "<< sommets_[i]->getEtiquette() << endl;
    }
    for (int j = 0; j < nbArrets_; j++)
    {
        delete arrets_[j];
    }
    
}