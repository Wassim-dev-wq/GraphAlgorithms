#include "./Graph.hpp"
#include <iostream>
using namespace std;

int main()
{
    /*EXAMPLE*/
    int n_sommet = 4; /* Nombre de sommets */
    Sommet **s = new Sommet *[n_sommet];
    cout << s[0] << endl;
    s[0] = new Sommet((char *)"0", 0, 0); /*Creation du sommet */
    s[1] = new Sommet((char *)"1", 0, 0);
    s[2] = new Sommet((char *)"2", 0, 0);
    s[3] = new Sommet((char *)"3", 0, 0); /*Creation du sommet */
    int m_arretes = 4; /* Nombre d'arrete */
    Arete **aretes = new Arete *[m_arretes];
    aretes[0] = new Arete(s[2], 5, s[0]);               /* Arete(Sommet_1, Poids, Sommet_2) */
    aretes[1] = new Arete(s[1], 3, s[2]); /* Creation d'une arrete avec des sommets qui n'existe pas */
    aretes[2] = new Arete(s[0], 7, s[3]);
    aretes[3] = new Arete(s[1], 1, s[3]);
    /* Creation du Graph */
    Graph *graph = new Graph(s, n_sommet, aretes, m_arretes);
    //graph->afficherSommets();
    //printf("%d", graph->getSommePoids()); /* Somme des poids du Graph G */
    cout << "Avant Kruskal";
    graph->afficherGraph();
    Graph *graphKruskal = graph->kruskal();
    cout << "\nApres Krusal";
    graphKruskal->afficherGraph();
    
    return 0;
}