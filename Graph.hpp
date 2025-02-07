#ifndef GRAPH_H
#define GRAPH_H
#include "Sommet.hpp"
#include "Arete.hpp"
#include<vector>

class Graph
{
private:
    vector<Sommet*> sommets_; /* Les sommets du graph [Tableau de sommets]*/
    int nbSommet_;     /* Nombre de sommet dans le Graph G */
    vector<Arete *> arrets_;   /* Les arretes du graph [Tab des arretes] */
    int nbArrets_;     /* Nombre des arretes */
public:
    Graph(vector<Sommet*> sommets, int nbSommet, vector<Arete *> arrets, int nbArrets);
    Graph(const Graph&);
    Graph();
    Graph(Graph *g);
    Graph* kruskal();
    void afficherSommets() const;
    void afficherGraph() const;
    bool checkSommet(string s);
    Graph* newGraph();
    void trieArrets();
    bool checkArret(Sommet *premier,Sommet* deuxieme, int poids,int count);
    
    void ajoute_sommet(string s);
    void ajoute_sommet(Sommet *s);

    void ajoute_arete(Arete* a);
    void ajoute_arete(Sommet *premier,Sommet* deuxieme, int poids);
    void ajoute_arete(string premier,string deuxieme, int poids);

    void symetrise();

    int getNbSommet() const;
    int getNbArete() const;
    vector<Sommet *> getSommets() const;
    vector<Arete *> getAretes() const;
    friend ostream &operator<<(ostream& out, const Graph &p);
    int getSommePoids();
    virtual ~Graph();

};

#endif