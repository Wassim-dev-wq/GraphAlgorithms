#include "Graph.hpp"
#include <iostream>
#include <string.h>
using namespace std;

Graph::Graph(vector<Sommet *> sommets, int nb_sm, vector<Arete *> arrets, int nb_arr) : sommets_{sommets}, nbSommet_{nb_sm}, arrets_{arrets}, nbArrets_{nb_arr} {}
Graph::Graph(Graph *g) : sommets_(g->getSommets()), nbSommet_(g->getNbSommet()), arrets_(g->getAretes()), nbArrets_(g->getNbArete()) {}
Graph::Graph() : sommets_{vector<Sommet*>{}}, nbSommet_{0}, arrets_{vector<Arete*>{}}, nbArrets_{0} {}
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
    Graph *G = new Graph();
    vector<Sommet *> s{};
    vector<Arete *> arret{};
    /* Init les parents de tous les sommets */
    for (int i = 0; i < getNbSommet(); i++){
        initSommets(sommets_[i]);
    }
    trieArrets(); /*trier les arêtes de G par poids croissant*/
    for (int i = 0; i < getNbArete(); ++i)
    {
        if (find(arrets_[i]->getPremier()) != find(arrets_[i]->getDeuxieme()))
        {
            arret.push_back(arrets_[i]);
            Union(arrets_[i]->getPremier(), arrets_[i]->getDeuxieme());
        }
    }
    for (int i = 0; i < getNbSommet(); ++i){
        s.push_back(new Sommet(to_string(i), 0, 0));/* creation des sommets a partir de les autres sommets*/
    }
    G->arrets_ = arret;
    G->sommets_ = s;
    G->nbArrets_ = arret.size();
    G->nbSommet_ = s.size();
    return G;
}

int Graph::getSommePoids()
{
    int poids = 0;
    for (int i = 0; i < getNbArete(); i++)
        poids = poids + arrets_[i]->getPoids();
    return poids;
}

Graph::~Graph()
{
    for (int i = 0; i < getNbSommet(); i++)
    {
        delete sommets_[i];
    }
    for (int i = 0; i < getNbArete(); i++)
    {
        delete arrets_[i];
    }
}

void Graph::ajoute_sommet(string s)
{
    sommets_.push_back(new Sommet(s, 0, 0));
    nbSommet_ = sommets_.size();
}

void Graph::ajoute_sommet(Sommet *s)
{
    for (int i = 0; i < getNbSommet(); i++)
    {
        if (sommets_[i] == s)
        {
            return;
        }
    }
    sommets_.push_back(s);
    nbSommet_ = sommets_.size();
}
bool Graph::checkSommet(string s_etiquette)
{
    for (int i = 0; i < getNbSommet(); i++)
    {
        if (sommets_[i]->getEtiquette() == s_etiquette)
            return true;
    }
    return false;
}

Graph *Graph::newGraph()
{
    Graph *G = new Graph();
    vector<Sommet *> s{};
    vector<Arete *>arret{};
    
    for (int i = 0; i < getNbSommet(); i++)
    {
        s.push_back(new Sommet(sommets_[i]->getEtiquette(), 0, 0));
    }
    G->arrets_ = arret;
    G->sommets_ = s;
    G->nbSommet_ = s.size();
    G->nbArrets_ = arret.size();
    return G;
}

void Graph::ajoute_arete(Arete *a)
{
    for (int i = 0; i < getNbArete(); i++)
    {
        if (checkArret(a->getPremier(),a->getDeuxieme(), a->getPoids(),getNbArete()))
        {
            return;
        }
    }
    arrets_.push_back(a);
    this->ajoute_sommet(a->getPremier());
    this->ajoute_sommet(a->getDeuxieme());
    nbArrets_ = arrets_.size();
}
void Graph::ajoute_arete(Sommet *premier, Sommet *deuxieme, int poids)
{
    Arete *tmp = new Arete{premier, poids, deuxieme};
    this->ajoute_arete(tmp);
}
void Graph::ajoute_arete(string premier, string deuxieme, int poids)
{
    arrets_.push_back(new Arete(premier, poids, deuxieme));
    nbArrets_ = arrets_.size();
}

bool Graph::checkArret(Sommet *premier, Sommet *deuxieme, int poids, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (premier == arrets_[i]->getPremier() && deuxieme == arrets_[i]->getDeuxieme() && poids == arrets_[i]->getPoids())
        {
            return true;
        }
    }
    return false;
}
void Graph::symetrise()
{
    int count = getNbArete();

    for (int i = 0; i < count; i++)
    {
        ajoute_arete(arrets_[i]->getDeuxieme()->getEtiquette(), arrets_[i]->getPremier()->getEtiquette(), arrets_[i]->getPoids());
    }
}

void Graph::afficherSommets() const
{
    cout << "NOMBRE SOMMET = " << getNbSommet() << endl;
    for (int i = 0; i < getNbSommet(); i++)
        cout << sommets_[i]->getEtiquette() << " ";
    cout << endl;
}

void Graph::afficherGraph() const
{
    cout << "\n- Les sommets : ";
    for (int i = 0; i < getNbSommet(); i++)
        cout << sommets_[i]->getEtiquette() << " ";

    cout << "\n- Nombre d'arrets : " << getNbArete() << endl;
    cout << "[ Sommet 1, Poids, Sommet 2 ]" << endl;
    for (int j = 0; j < getNbArete(); j++)
    {
        cout << "    " << (arrets_[j])->getPremier()->getEtiquette() << ",      ";
        cout << (arrets_[j])->getPoids() << ",       ";
        cout << (arrets_[j])->getDeuxieme()->getEtiquette() << "" << endl;
    }

}

int Graph::getNbSommet() const
{
    return sommets_.size();
}

int Graph::getNbArete() const
{
    return arrets_.size();
}

vector<Sommet *> Graph::getSommets() const
{
    return sommets_;
}

vector<Arete *> Graph::getAretes() const
{
    return arrets_;
}

ostream &operator<<(ostream &out, const Graph &p)
{
    int i;
    vector<Sommet *> sommets = p.getSommets();
    vector<Arete *> aretes = p.getAretes();
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