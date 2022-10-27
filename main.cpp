#include "./Graph.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

Sommet **createSommets(int n_sommet)
{
    Sommet **s = new Sommet *[n_sommet];
    for (int i = 0; i < n_sommet; i++)
    {
        s[i] = new Sommet((char *)"0", 0, 0);
    }
    return s;
}

Graph *createGraph()
{
    int n_sommet = 5; /* Nombre de sommets */
    Sommet **s = new Sommet *[n_sommet];
    s[0] = new Sommet((char *)"0", 0, 0); /*Creation du sommet */
    s[1] = new Sommet((char *)"1", 0, 0);
    s[2] = new Sommet((char *)"2", 0, 0);
    s[3] = new Sommet((char *)"3", 0, 0); /*Creation du sommet */
    s[4] = new Sommet((char *)"4", 0, 0);

    int m_arretes = 7; /* Nombre d'arrete */
    Arete **aretes = new Arete *[m_arretes];
    aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
    aretes[1] = new Arete(s[0], 75, s[2]); /* Creation d'une arrete avec des sommets qui n'existe pas */
    aretes[2] = new Arete(s[1], 95, s[2]);
    aretes[6] = new Arete(s[1], 19, s[3]);
    aretes[3] = new Arete(s[2], 51, s[3]);
    aretes[5] = new Arete(s[1], 42, s[4]);
    aretes[4] = new Arete(s[4], 31, s[3]);
    return new Graph(s, n_sommet, aretes, m_arretes);
}

void intro()
{
    cout << "0 : Sortir." << endl;
    cout << "1 : Choix 1.Lister les grahes existants" << endl;
    cout << "2 : Choix 2.Créer un nouveau Graph" << endl;
    cout << "3 : Choix 3.Ajouter somme à un graph existant" << endl;
    cout << "4 : Choix 4.Ajouter un arete au graph" << endl;
    cout << "5 : Choix 5.Savoir le poids des arrets du Graph" << endl;
    cout << "6 : Choix 6.Appliquer algorithme Kruskal au graph" << endl;
}

void outtro()
{
    cout << "Au revoir." << endl;
}

void Choix1(int nbGraph, Graph **g)
{
    cout << "Vous avez fait le choix 1.\n"
         << endl;
    cout << "La liste des graphes existants avec leurs sommets" << endl;
    for (int i = 0; i < nbGraph; i++)
    {
        cout << "Graph " << i << ": Sommets :";
        g[i]->afficherSommets();
    }
}

Graph *Choix2()
{
    cout << "Vous avez fait le choix 2." << endl;
    cout << "Création du graph..." << endl;
    Graph *graph = createGraph();
    sleep(1);
    cout << "Le graph est créer avec succées.\n"
         << endl;
    return graph;
}

void Choix3()
{
    cout << "Vous avez fait le choix 3." << endl;
}
void Choix4()
{
    cout << "Vous avez fait le choix 4." << endl;
}
void Choix5()
{
    cout << "Vous avez fait le choix 5." << endl;
}

void Choix6()
{
    cout << "Vous avez fait le choix 6." << endl;
}

int main()
{
    /*EXAMPLE*/
    Graph **graph = new Graph *[4];
    Sommet **s;
    char choix = '?';
    int nbGraph_ = 0;
    cout << "Bonjour." << endl;
    do
    {
        intro();
        cin >> choix;
        switch (choix)
        {
        case '1':
            Choix1(nbGraph_, graph);
            cout << "1 : Choix 1. Plus de détail sur un graph ? Entrer le numéro du graphe" << endl;
            cout << "2 : Revenir au menu." << endl;
            cin >> choix;
            switch (choix)
            {
            case '1':
                cout << "1 : Choix 1. " << endl;
                break;
            case '2':
                break;
            }
            break;
        case '2':
            graph[nbGraph_] = Choix2();
            nbGraph_++;
            cout << "1 : Choix 1. Ajouter sommet au graph" << endl;
            cout << "2 : Choix 2. Ajouter des arretes" << endl;
            cout << "3 : Revenir au menu." << endl;
            cin >> choix;
            switch (choix)
            {
            case '1':
                cout << "1. Ceer les sommets automatiquement " << endl;
                cout << "2. Creer les sommets manuel " << endl;
                cin >> choix;
                if (choix == '1')
                {
                    cout << "Attention!! les sommets vont être numérotés automatiquemen"
                         << "vous ne pouvez pas spécifier l'étiquette du sommet ! "
                         << "Voulez-vous continuer la création [y/n] ?" << endl;
                    cin >> choix;
                    if (choix == 'y')
                    {
                        int nbS = 0;
                        cout << " Entrer le nombre de sommet que vous voulez créer : ";
                        cin >> nbS;
                    }
                    }
                    break;
                case '2':
                    cout << "2\n\n";
                    break;
                case '3':
                    break;
                }
                break;

            case '3':
                Choix3();
                break;

            case '4':
                Choix4();
                break;

            case '5':
                Choix5();
                break;

            case '6':
                Choix6();
                break;

            case '0':
                break;

            default:
                cerr << "Quoi ?" << endl;
                break;
            }
        }
        while (choix != '0')
            ;
        outtro();
        // cout << "Avant Kruskal";
        // graph->afficherGraph();
        // Graph *graphKruskal = graph->kruskal();
        // cout << "\nApres Krusal";
        // graphKruskal->afficherGraph();

        return 0;
    }