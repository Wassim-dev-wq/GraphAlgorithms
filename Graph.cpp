#include "Graph.hpp"
#include <iostream>
#include <string.h>
using namespace std;

Graph::Graph(Sommet **sommets, int nb_sm, Arete **arrets, int nb_arr) : sommets_(sommets), nbSommet_(nb_sm), arrets_(arrets), nbArrets_(nb_arr) {}
Graph::Graph(Graph *g) : sommets_(g->getSommets()), nbSommet_(g->getNbSommet()), arrets_(g->getAretes()), nbArrets_(g->getNbArete()) {}
Graph::Graph(const Graph &g) {}

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
            s1Racine->parent_ = s2Racine;
            if (s1Racine->rang_ == s2Racine->rang_)
            {
                s2Racine->rang_++;
            }
        }
    }
}

/* Insertion sort */
void Graph::trieArrets()
{
    int i, j;
    Arete *ei;
    for (i = 1; i < nbArrets_; i++)
    {
        ei = arrets_[i];
        j = i - 1;
        while (j >= 0 && arrets_[j]->getPoids() > ei->getPoids())
        {
            arrets_[j + 1] = arrets_[j];
            j--;
        }
        arrets_[j + 1] = ei;
    }
}

Graph *Graph::kruskal()
{
    Graph *G = new Graph(NULL, 0, NULL, 0);
    Sommet **s = new Sommet *[nbSommet_];
    Arete **arret = new Arete *[nbArrets_];
    int nbArrets_kruskal = 0;
    /* Init les parents de tous les sommets */
    for (int i = 0; i < nbSommet_; i++)
        initSommets(sommets_[i]);
    trieArrets(); /*trier les arêtes de G par poids croissant*/
    for (int i = 0; i < nbArrets_; ++i)
    {
        if (find(arrets_[i]->getPremier()) != find(arrets_[i]->getDeuxieme()))
        {
            arret[nbArrets_kruskal] = arrets_[i];
            nbArrets_kruskal++;
            Union(arrets_[i]->getPremier(), arrets_[i]->getDeuxieme());
        }
    }
    for (int i = 0; i < nbSommet_; ++i)
        s[i] = new Sommet(to_string(i), 0, 0); /* creation des sommets a partir de les autres sommets*/
    G->arrets_ = arret;
    G->sommets_ = s;
    G->nbArrets_ = nbArrets_kruskal;
    G->nbSommet_ = nbSommet_;
    return G;
}

int Graph::getSommePoids()
{
    int poids = 0;
    for (int i = 0; i < nbArrets_; i++)
        poids = poids + arrets_[i]->getPoids();
    return poids;
}

Graph::~Graph()
{
    delete[] sommets_;
    delete[] arrets_;
}

void Graph::ajoute_sommet(string s)
{
    sommets_[nbSommet_] = new Sommet(s, 0, 0);
    nbSommet_++;
}

void Graph::ajoute_sommet(Sommet *s)
{
    for (int i = 0; i < nbSommet_; i++)
    {
        if (sommets_[i] == s)
        {
            return;
        }
    }
    sommets_[nbSommet_] = s;
    nbSommet_++;
}
bool Graph::checkSommet(string s_etiquette)
{
    for (int i = 0; i < nbSommet_; i++)
    {
        if (sommets_[i]->getEtiquette() == s_etiquette)
            return true;
    }
    return false;
}

void Graph::ajoute_arete(Arete *a)
{
    for (int i = 0; i < nbArrets_; i++)
    {
        if (arrets_[i] == a)
        {
            return;
        }
    }
    arrets_[nbArrets_] = a;
    nbArrets_++;
}
void Graph::ajoute_arete(Sommet *premier, Sommet *deuxieme, int poids)
{
    Arete *tmp = new Arete{premier, poids, deuxieme};
    this->ajoute_arete(tmp);
    this->ajoute_sommet(premier);
    this->ajoute_sommet(deuxieme);
}
void Graph::ajoute_arete(string premier, string deuxieme, int poids)
{
    arrets_[nbArrets_] = new Arete(premier, poids, deuxieme);
    nbArrets_++;
}

bool Graph::checkArret(Sommet *premier, Sommet *deuxieme, int poids,int count)
{
    for (int i = 0; i < count; i++)
    {
        if (premier == arrets_[i]->getPremier() && deuxieme == arrets_[i]->getDeuxieme() && poids == arrets_[i]->getPoids()){
            return true;
        }
    }
    return false;
}
void Graph::symetrise()
{
    Graph *G = new Graph(NULL, 0, NULL, 0);
    Sommet **s = new Sommet *[nbSommet_];
    Arete **arret = new Arete *();
    int count = nbArrets_;
    for (int i = 0; i < count; i++)
    {
        
        if ((checkArret(arrets_[i]->getDeuxieme(), arrets_[i]->getPremier(), arrets_[i]->getPoids(),count))==false){
            ajoute_arete(arrets_[i]->getDeuxieme(), arrets_[i]->getPremier(), arrets_[i]->getPoids());
            nbArrets_ ++;
        }
    }
    cout << nbArrets_ << endl;
    // G->arrets_ = arret;
    // G->sommets_ = s;
    // G->nbArrets_ = count;
    // G->nbSommet_ = nbSommet_;
    // return G;
}

void Graph::afficherSommets() const
{
    for (int i = 0; i < nbSommet_; i++)
        cout << sommets_[i]->getEtiquette() << " ";
    cout << endl;
}

void Graph::afficherGraph() const
{
    cout << "\n- Les sommets : ";
    for (int i = 0; i < nbSommet_; i++)
        cout << sommets_[i]->getEtiquette() << " ";

    cout << "\n- Nombre d'arrets : " << nbArrets_ << endl;
    cout << "[ Sommet 1, Poids, Sommet 2 ]" << endl;
    for (int j = 0; j < nbArrets_; j++)
    {
        cout << "    " << (arrets_[j])->getPremier()->getEtiquette() << ",      ";
        cout << (arrets_[j])->getPoids() << ",       ";
        cout << (arrets_[j])->getDeuxieme()->getEtiquette() << "" << endl;
    }
}

int Graph::getNbSommet() const
{
    return nbSommet_;
}

int Graph::getNbArete() const
{
    return nbArrets_;
}

Sommet **Graph::getSommets() const
{
    return sommets_;
}

Arete **Graph::getAretes() const
{
    return arrets_;
}

ostream &operator<<(ostream &out, const Graph &p)
{
    int i;
    Sommet **sommets = p.getSommets();
    Arete **aretes = p.getAretes();
    out << "Sommet : ";

    for (i = 0; i < p.getNbSommet() - 1; i++)
    {
        out << sommets[i]->getEtiquette() << ", ";
    }
    out << sommets[i]->getEtiquette() << endl;

    out << "Aretes : " << endl;
    for (i = 0; i < p.getNbArete(); i++)
    {
        out << aretes[i]->getPremier()->getEtiquette() << " -- " << aretes[i]->getPoids() << " --> " << aretes[i]->getDeuxieme()->getEtiquette() << endl;
    }
    return out;
}