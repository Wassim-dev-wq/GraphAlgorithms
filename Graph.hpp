#ifndef GRAPH_H
#define GRAPH_H
#include "Sommet.hpp"
#include "Arete.hpp"

class Graph
{
private:
    Sommet **sommets_; /* Les sommets du graph [Tableau de sommets]*/
    int nbSommet_;     /* Nombre de sommet dans le Graph G */
    Arete **arrets_;   /* Les arretes du graph [Tab des arretes] */
    int nbArrets_;     /* Nombre des arretes */
public:
    Graph(Sommet **sommets, int nbSommet, Arete **arrets, int nbArrets);
    Graph* kruskal();
    void afficherSommets() const;
    int getSommePoids();
    void afficherGraph() const;
    ~Graph();

};

#endif