#include "Graph.hpp"
#include <iostream>
using namespace std;

int main()
{
    /*EXAMPLE*/
    int n_sommet = 2; /* Nombre de sommets */
    Sommet **s = new Sommet *[n_sommet];
    cout << s[0] << endl;
    s[0] = new Sommet((char *)"1", 0, 0); /*Creation du sommet */
    s[1] = new Sommet((char *)"3", 0, 0);
    int m_arretes = 2; /* Nombre d'arrete */
    Arete **aretes = new Arete *[m_arretes];
    aretes[0] = new Arete(s[0], 5, s[1]);               /* Arete(Sommet_1, Poids, Sommet_2) */
    aretes[1] = new Arete((char *)"1", 7, (char *)"3"); /* Creation d'une arrete avec des sommets qui n'existe pas */
    /* Creation du Graph */
    Graph *graph = new Graph(s, n_sommet, aretes, m_arretes);
    graph->afficherSommets();
    printf("%d", graph->getSommePoids()); /* Somme des poids du Graph G */
    return 0;
}