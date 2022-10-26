#include "Graph.hpp"
#include <iostream>
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
        s->parent_ = find(s);
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


int partition(Arete **arr, int debut, int fin)
{

    int pivot = arr[debut]->getPoids();

    int count = 0;
    for (int i = debut + 1; i <= fin; i++)
    {
        cout << "i" << i<<"fin" << fin<< endl;
        cout << "poids " << arr[i]->getPoids() << "pivot "<< pivot << "arr[i]" << arr[i]->premier_->getEtiquette() << endl;
        if (arr[i]->getPoids() <= pivot){
            cout<< count <<endl;
            count++;}

    }
    // Giving pivot element its correct position
    int pivotIndex = debut + count;
    swap(arr[pivotIndex], arr[debut]);

    // Sorting left and right parts of the pivot element
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

    // base case
    if (debut >= fin)
        return;

    // partitioning the array
    int p = partition(arr, debut, fin);

    // Sorting the left part
    quickSort(arr, debut, p - 1);

    // Sorting the right part
    quickSort(arr, p + 1, fin);
}

void Graph::kruskal()
{
    // Sommet **s = new Sommet *[nbSommet_];
    // Arete **arret = new Arete *[nbArrets_];
    // int nbSommet_kruskal = 0;
    // /* Init les parents de tous les sommets */
    // for (int i = 0; i < nbSommet_; i++)
    // {
    //     initSommets(sommets_[i]);
    // }
    cout<<"avant"<<endl;
    quickSort(arrets_, 0, nbArrets_); /*trier les arêtes de G par poids croissant*/
    cout<<"apres"<<endl;
    // for (int i = 0; i < nbArrets_; i++)
    // {
    //     if (find(arret[i]->premier_) != find(arret[i]->deuxieme_))
    //     {
    //         arret[nbSommet_kruskal] = arret[i];
    //         nbSommet_kruskal++;
    //         // Union(arret[i]->premier_, arret[i]->deuxieme_);
    //     }
    // }
    // for (int i = 0; i < nbSommet_; i++)
    // {
    //     s[i] = new Sommet((char *)0, 0, 0);
    // }
    //return new Graph(s,nbSommet_kruskal,arret,nbArrets_);
}

int Graph::getSommePoids()
{
    int poids = 0;
    for (int i = 0; i < nbArrets_; i++)
    {
        poids = poids + arrets_[i]->getPoids();
    }
    return poids;
}

void Graph::afficherSommets() const
{
    for (int i = 0; i < nbSommet_; i++)
    {
        cout << sommets_[i]->getEtiquette() << endl;
    }
}

Graph::~Graph() {}