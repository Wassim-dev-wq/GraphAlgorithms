#include "./Graph.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

bool check(string numGraph, int nbGraph, Graph **graph)
{
    for (int i = 0; i < numGraph.length(); i++)
    {
        if (isdigit(numGraph[i]) == true)
        {
            if (stoi(numGraph) <= nbGraph - 1 && stoi(numGraph) >= 0)
            {
                return true;
            }
            cout << "Le graph " << numGraph << " n'existe pas veuillez entrer numéro d'un graph existant\n"
                 << endl;
            return false;
        }
        else
        {
            cout << "Graph " << numGraph << " n'existe pas veuillez entrer un le nombre du graph\n"
                 << endl;
            return false;
        }
    }
}

void afficherSommets(Sommet **s, int n_sommet)
{
    for (int i = 0; i < n_sommet; i++)
    {
        cout << s[i]->getEtiquette() << ", ";
    }
    cout << endl;
}
Sommet **createSommets(int n_sommet)
{
    cout << "Création des sommets..." << endl;
    Sommet **s = new Sommet *[n_sommet];
    for (int i = 0; i < n_sommet; i++)
    {
        s[i] = new Sommet(to_string(i), 0, 0);
    }
    sleep(1);
    cout << "Les sommets sont créer avec succées" << endl;
    return s;
}

// Arete **createArret()
// {
//     cout << "Création de l'arret ..." << endl;
//     Arete **s = new Arete *[];
//     for (int i = 0; i < n_sommet; i++)
//     {
//         s[i] = new Sommet(to_string(i), 0, 0);
//     }
//     sleep(1);
//     cout << "Les sommets sont créer avec succées" << endl;
//     return s;
// }

Graph *createSommetArrete()
{
    int nbS = 0;
    Arete **aretes;
    Sommet **s;
    int nbArrets;
    char choix = '?';
    cout << "1 : Choix 1. Ajouter sommet au graph" << endl;
    cout << "2 : Choix 2. Ajouter des arretes" << endl;
    cout << "3 : Choix 3. Créer un graph complet [Création automatique du graph]" << endl;
    cout << "4 : Revenir au menu." << endl;
    cin >> choix;
    switch (choix)
    {
    case '1':
        cout << "1. Creer les sommets automatiquement " << endl;
        cout << "2. Creer les sommets manuel " << endl;
        cin >> choix;
        if (choix == '1')
        {
            cout << "Attention!! les sommets vont être numérotés automatiquement"
                 << "vous ne pouvez pas spécifier l'étiquette du sommet !\n"
                 << "Voulez-vous continuer la création [y/n] ?" << endl;
            cin >> choix;
            if (choix == 'y')
            {
                cout << " Entrer le nombre de sommet que vous voulez créer : ";
                cin >> nbS;
                s = new Sommet *[nbS];
                s = createSommets(nbS); /* s[1] = new Sommet((char *)"1", 0, 0); */
                cout << "Voulez-vous créer des arréts ? [y/n]";
                cin >> choix;
                if (choix == 'y')
                {
                    cout << "Entrer le nombre d'arrets que vous souhaitez-créer"
                            "[Entrer 0 si vous ne savez pas le nombre] :";
                    cin >> nbArrets;
                    if (nbArrets != 0)
                    {
                        aretes = new Arete *[nbArrets];
                        int i = 0;
                        while (i < nbArrets)
                        {
                            int s1;
                            int s2;
                            int poids;
                            cout << "Les sommets du graph :";
                            afficherSommets(s, nbS);
                            cout << "Creation de l'arret " << i << " :" << endl;
                            cout << "Entrer le premier sommet de l'arret :";
                            cin >> s1;
                            cout << "Entrer le deuxieme sommet de l'arret :";
                            cin >> s2;
                            if (s1 == s2)
                            {
                                cout << "Vous avez entrer le meme sommet!! Veuillez entrer un sommet different : ";
                                cin >> s2;
                            }
                            cout << "Entrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: " << endl;
                            cin >> poids;
                            aretes[i] = new Arete(s[s1], poids, s[s2]);
                            // aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
                            cout << "L'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés.. " << endl;
                            i++;
                        }
                    }
                }
            }
            else if (choix == 'n')
            {
            }
            else
            {
                cout << choix << "N'est pas parmie les choix proposer veuillez choisir entre [y/n]" << endl;
                cout << "Les sommets vont être numérotés automatiquement"
                     << "vous ne pouvez pas spécifier l'étiquette du sommet !\n"
                     << "Voulez-vous continuer la création [y/n] ?" << endl;
                cout << "Pour sortir tapez -1 " << endl;
                cin >> choix;
                if (choix == '-1')
                {
                    break;
                }
            }
        }
        return new Graph(s, nbS, aretes, nbArrets);
        break;
    case '3':
        s = createSommets(5);
        Arete **arete = new Arete *[7];
        arete[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
        arete[1] = new Arete(s[0], 75, s[2]); /* Creation d'une arrete avec des sommets qui n'existe pas */
        arete[2] = new Arete(s[1], 95, s[2]);
        arete[6] = new Arete(s[1], 19, s[3]);
        arete[3] = new Arete(s[2], 51, s[3]);
        arete[5] = new Arete(s[1], 42, s[4]);
        arete[4] = new Arete(s[4], 31, s[3]);
        return new Graph(s, 5, arete, 7);
        break;
    }
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
    Graph *graph = createSommetArrete();
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
            cout << "Vous avez fait le choix 1." << endl;
            if (nbGraph_ == 0)
            {
                cout << "Aucun graphe n'est créer" << endl;
                cout << "Voulez-vous créer un graphe ? [y/n] ";
                cin >> choix;
                if (choix == 'y')
                {
                    graph[nbGraph_] = Choix2();
                    nbGraph_++;
                    createSommetArrete();
                }
                break;
            }
            Choix1(nbGraph_, graph);
            cout << "1 : Choix 1. Plus de détail sur un graph ?" << endl;
            cout << "2 : Revenir au menu." << endl;
            cin >> choix;
            if (choix == '1')
            {
                string numGraph = "-1";
                cout << "Entrer le numéro du graph : ";
                cin >> numGraph;
                while (true)
                {
                    if (check(numGraph, nbGraph_, graph) == false)
                    {
                        Choix1(nbGraph_, graph);
                        cout << "Entrer le numéro du graph [Tapez -1 si vous voulez sortir]:";
                        cin >> numGraph;
                        if (numGraph == "-1")
                        {
                            break;
                        }
                    }
                    else
                    {
                        cout << "TRUE" << endl;
                        break;
                    }
                }
            }
            break;
        case '2':
            graph[nbGraph_] = Choix2();
            nbGraph_++;
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
    } while (choix != '0');
    outtro();
    // cout << "Avant Kruskal";
    // graph->afficherGraph();
    // Graph *graphKruskal = graph->kruskal();
    // cout << "\nApres Krusal";
    // graphKruskal->afficherGraph();

    return 0;
}