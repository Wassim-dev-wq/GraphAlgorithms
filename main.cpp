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

bool checkDigit(string choix)
{
    for (int i = 0; i < choix.length(); i++)
    {
        if (isdigit(choix[i]) == true)
        {
            return true;
        }
    }
    return false;
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
    return s;
}

bool checkSommet(Sommet **s, string s_etiquette, int n_sommet)
{
    for (int i = 0; i < n_sommet; i++)
    {
        if (s[i]->getEtiquette() == s_etiquette)
            return true;
    }
    return false;
}
Graph *createSommetArrete()
{
    int nbS = 0;
    Arete **aretes = new Arete *();
    Sommet **s = new Sommet *();
    int nbArrets;
    char choix = '?';
    cout << "1 : Choix 1. Ajouter sommet" << endl;
    cout << "2 : Choix 2. Ajouter arret " << endl;
    cout << "3 : Choix 3. Créer un graph complet [Création automatique du graph]" << endl;
    cout << "4 : Choix 4. Revenir au menu." << endl;
    cin >> choix;
    switch (choix)
    {
    case '1':
    {
        cout << "1. Creer les sommets automatiquement " << endl;
        cout << "2. Creer les sommets manuel[MARCHE PAS]" << endl; /* MANQUANT */
        cin >> choix;
        if (choix == '1')
        {
            cout << "Attention!! les sommets vont être numérotés automatiquement"
                 << "vous ne pouvez pas spécifier l'étiquette du sommet !\n"
                 << "Voulez-vous continuer la création [y/n] ?  ";
            cin >> choix;
            if (choix == 'y')
            {
                cout << "Entrer le nombre de sommet que vous voulez créer :  ";
                cin >> nbS;
                s = new Sommet *[nbS];
                s = createSommets(nbS); /* s[1] = new Sommet((char *)"1", 0, 0); */
                cout << "\nVoulez-vous créer des arréts [y/n] ?  ";
                cin >> choix;
                if (choix == 'y')
                {
                    cout << "\nEntrer le nombre d'arrets que vous souhaitez-créer"
                            "[Entrer 0 si vous ne savez pas le nombre] :  ";
                    cin >> nbArrets;
                    if (nbArrets != 0)
                    {
                        aretes = new Arete *[nbArrets];
                        int i = 0;
                        while (i < nbArrets)
                        {
                            string s1;
                            string s2;
                            int poids;
                            cout << "\nLes sommets du graph : ";
                            afficherSommets(s, nbS);
                            cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                            cout << "Entrer le premier sommet de l'arret [TAPEZ -1 POUR ANNULEZ]:  ";
                            cin >> s1;
                            if( s1 == "-1"){
                                break;
                            }
                            while (checkSommet(s, s1, nbS) == false)
                            {
                                cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s[nbS] = new Sommet(s1, 0, 0);
                                    nbS++;
                                    cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s1;
                                }
                                else
                                {
                                    while (choix != 'y' || choix != 'n' || choix != '-1')
                                    {
                                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                                        cin >> choix;
                                    }
                                }
                            }
                            cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                            cin >> s2;
                            while (checkSommet(s, s2, nbS) == false)
                            {
                                cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s[nbS] = new Sommet(s2, 0, 0);
                                    nbS++;
                                    cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s2;
                                }
                                else
                                {
                                    while (choix != 'y' || choix != 'n' || choix != '-1')
                                    {
                                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                                        cin >> choix;
                                    }
                                }
                            }
                            while (s1 == s2)
                            {
                                cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                                        "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                                cin >> s2;
                                while (checkSommet(s, s2, nbS) == false)
                                {
                                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                                  "[Tapez -1 si vous voulez quitter] :  ";
                                    cin >> s2;
                                }
                            }
                            cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                            cin >> poids;
                            aretes[i] = new Arete(s1, poids, s2);
                            // aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
                            cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                                 << endl;
                            i++;
                        }
                    }
                    else if (nbArrets == 0)
                    {
                        aretes = new Arete *();
                        int i = 0;
                        char addArr = 'y';
                        while (addArr == 'y')
                        {
                            string s1;
                            string s2;
                            int poids;
                            cout << "\nLes sommets du graph : ";
                            afficherSommets(s, nbS);
                            cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                            cout << "Entrer le premier sommet de l'arret [TAPEZ -1 POUR ANNULER] :  ";
                            cin >> s1;
                            if (s1 == "-1"){
                                break;
                            }
                            while (checkSommet(s, s1, nbS) == false)
                            {
                                cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s[nbS] = new Sommet(s1, 0, 0);
                                    nbS++;
                                    cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s1;
                                }
                                else
                                {
                                    while (choix != 'y' || choix != 'n' || choix != '-1')
                                    {
                                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                                        cin >> choix;
                                    }
                                }
                            }
                            cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                            cin >> s2;
                            while (checkSommet(s, s2, nbS) == false)
                            {
                                cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s[nbS] = new Sommet(s1, 0, 0);
                                    nbS++;
                                    cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s2;
                                }
                                else
                                {
                                    while (choix != 'y' || choix != 'n' || choix != '-1')
                                    {
                                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                                        cin >> choix;
                                    }
                                }
                            }
                            while (s1 == s2)
                            {
                                cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                                        "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                                cin >> s2;
                                while (checkSommet(s, s2, nbS) == false)
                                {
                                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                    cin >> choix;
                                    if (choix == 'y')
                                    {
                                        s[nbS] = new Sommet(s2, 0, 0);
                                        nbS++;
                                        cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                                        break;
                                    }
                                    else if (choix == 'n')
                                    {
                                        cout << "Veuillez entrer un sommet valide : ";
                                        cin >> s2;
                                    }
                                    else
                                    {
                                        while (choix != 'y' || choix != 'n' || choix != '-1')
                                        {
                                            cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                                            cin >> choix;
                                        }
                                    }
                                }
                            }
                            cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                            cin >> poids;
                            aretes[i] = new Arete(s1, poids, s2);
                            // aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
                            cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                                 << endl;
                            i++;
                            cout << "Voulez-vous ajouter un autre arrets [y/n] ? : ";
                            cin >> addArr;
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
        else if (choix == '2')
        {
            int numSommets;
            cout << "Entrer le nombre de sommets que vous voulez ajouter [TAPEZ 0 SI VOUS NE SAVEZ PAS] : ";
            cin >> numSommets;
            int i = 0;
            string etiqu_sommet;
            if (numSommets > 0)
            {
                while (i < numSommets)
                {
                    cout << "Entrer l'étiquette du sommet " << i << " : ";
                    cin >> etiqu_sommet;
                    s[nbS] = new Sommet(etiqu_sommet, 0, 0);
                    nbS++;
                    cout << "Sommet " << etiqu_sommet << " est créer avec succées.\n"
                         << endl;
                    i++;
                }
            }
            else if (numSommets == 0)
            {
                do
                {
                    cout << "Entrer l'étiquette du sommet " << i << " : ";
                    cin >> etiqu_sommet;
                    s[nbS] = new Sommet(etiqu_sommet, 0, 0);
                    nbS++;
                    cout << "Sommet " << etiqu_sommet << " est créer avec succées.\n"
                         << endl;
                    cout << "Voulez-vous ajouter un autre sommet [y/n] ?  :";
                    cin >> choix;
                    while (choix != 'y' && choix != 'n')
                    {
                        cout << choix << "N'est pas parmie les choix "
                                         "veuillez entrer y [YES] or n [NO] :  ";
                        cin >> choix;
                    }
                } while (choix == 'y');
            }
            else
            {
                cout << "Veuillez entrer un nombre valide :  " << endl;
            }
        }
        cout << "Les sommets du graph : ";
        afficherSommets(s, nbS);
        return new Graph(s, nbS, aretes, nbArrets);
    }
    break;

    case '2':
    {
        cout << "Entrer le nombre d'arrets que vous souhaitez-créer"
                "[Entrer 0 si vous ne savez pas le nombre] :  ";
        cin >> nbArrets;
        if (nbArrets != 0)
        {
            aretes = new Arete *[nbArrets];
            int i = 0;
            while (i < nbArrets)
            {
                string s1;
                string s2;
                int poids;
                cout << "\nLes sommets du graph : ";
                afficherSommets(s, nbS);
                cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                cout << "Entrer le premier sommet de l'arret [TAPEZ -1 POUR ANNULER] :  ";
                cin >> s1;
                if(s1 == "-1"){
                    break;
                }
                while (checkSommet(s, s1, nbS) == false)
                {
                    cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s[nbS] = new Sommet(s1, 0, 0);
                        nbS++;
                        cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s1;
                    }
                    else
                    {
                        while (choix != 'y' || choix != 'n' || choix != '-1')
                        {
                            cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                            cin >> choix;
                        }
                    }
                }
                cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                cin >> s2;
                while (checkSommet(s, s2, nbS) == false)
                {
                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s[nbS] = new Sommet(s2, 0, 0);
                        nbS++;
                        cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s2;
                    }
                    else
                    {
                        while (choix != 'y' || choix != 'n' || choix != '-1')
                        {
                            cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                            cin >> choix;
                        }
                    }
                }
                while (s1 == s2)
                {
                    cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                            "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                    cin >> s2;
                    while (checkSommet(s, s2, nbS) == false)
                    {
                        cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                      "[Tapez -1 si vous voulez quitter] :  ";
                        cin >> s2;
                    }
                }
                cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                cin >> poids;
                aretes[i] = new Arete(s1, poids, s2);
                cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                     << endl;
                i++;
            }
        }
        else if (nbArrets == 0)
        {
            int i = 0;
            char addArr = 'y';
            while (addArr == 'y')
            {
                string s1;
                string s2;
                int poids;
                cout << "\nLes sommets du graph : ";
                afficherSommets(s, nbS);
                cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                cout << "Entrer le premier sommet de l'arret [TAPEZ -1 POUR ANNULER] :  ";
                cin >> s1;
                if(s1 == "-1"){
                    break;
                }
                while (checkSommet(s, s1, nbS) == false)
                {
                    cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s[nbS] = new Sommet(s1, 0, 0);
                        nbS++;
                        cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s1;
                    }
                    else
                    {
                        while (choix != 'y' || choix != 'n' || choix != '-1')
                        {
                            cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                            cin >> choix;
                        }
                    }
                }
                cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                cin >> s2;
                while (checkSommet(s, s2, nbS) == false)
                {
                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s[nbS] = new Sommet(s2, 0, 0);
                        nbS++;
                        cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s2;
                    }
                    else
                    {
                        while (choix != 'y' || choix != 'n' || choix != '-1')
                        {
                            cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                            cin >> choix;
                        }
                    }
                }
                while (s1 == s2)
                {
                    cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                            "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                    cin >> s2;
                    while (checkSommet(s, s2, nbS) == false)
                    {
                        cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                      "[Tapez -1 si vous voulez quitter] :  ";
                        cin >> s2;
                    }
                }
                cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                cin >> poids;
                aretes[i] = new Arete(s1, poids, s2);
                // aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
                cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                     << endl;
                i++;
                cout << "Voulez-vous ajouter un autre arrets [y/n] ? : ";
                cin >> addArr;
            }
        }
    }
        return new Graph(s, nbS, aretes, nbArrets);
        break;
    case '3':
    {
        s = createSommets(5);
        Arete **arete = new Arete *[7];
        cout << "Création des arrets..." << endl;
        sleep(1);
        arete[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
        arete[1] = new Arete(s[0], 75, s[2]); /* Creation d'une arrete avec des sommets qui n'existe pas */
        arete[2] = new Arete(s[1], 95, s[2]);
        arete[6] = new Arete(s[1], 19, s[3]);
        arete[3] = new Arete(s[2], 51, s[3]);
        arete[5] = new Arete(s[1], 42, s[4]);
        arete[4] = new Arete(s[4], 31, s[3]);
        cout << "Crétion du graph..." << endl;
        sleep(1);
        cout << "Le graph est créer.\n"
             << endl;
        return new Graph(s, 5, arete, 7);
    }
    break;
    case '4':
        break;
    }
}
void intro()
{
    cout << "\n0 : Sortir." << endl;
    cout << "1 : Choix 1.Lister les grahes existants" << endl;
    cout << "2 : Choix 2.Créer un nouveau Graph" << endl;
    cout << "3 : Choix 3.Modifier un graph existant." << endl;
    cout << "4 : Choix 4.Appliquer Kruskal a un graph." << endl;
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
    cout << "\nVous avez fait le choix 2." << endl;
    cout << "Création du graph..." << endl;
    Graph *graph = createSommetArrete();
    sleep(1);
    return graph;
}

void Choix3()
{
    cout << "\nModifier un graph existant." << endl;
}
void Choix4()
{
    cout << "\nVous avez fait le choix 4." << endl;
}
void Choix5()
{
    cout << "Vous avez fait le choix 5." << endl;
}

void Choix6()
{
    cout << "Vous avez fait le choix 6." << endl;
}

void ajouterSommet(Graph *g, Sommet **s)
{
    int choix;
    int i = 0;
    string etiqu_sommet;
    cout << "Entrer le nombre de sommet que vous voulez ajouter [TAPEZ 0 SI VOUS SAVEZ PAS] : ";
    cin >> choix;
    if (choix != 0)
    {
        while (i < choix)
        {
            cout << "Entrer l'étiquette du sommet " << i << " : ";
            cin >> etiqu_sommet;
            while (g->checkSommet(etiqu_sommet))
            {
                cout << "L'étiquette " << etiqu_sommet << " est déja pris par un autre sommet, veuillez entrer une autre étiquette: "
                                                          "[TAPEZ -1 POUR ANNULER] : ";
                cin >> etiqu_sommet;
            }
            if (etiqu_sommet == "-1")
            {
                break;
            }
            g->ajoute_sommet(etiqu_sommet);
            cout << "Le sommet " << etiqu_sommet << " a était créer avec succées " << endl;
            i++;
        }
    }
    else if (choix == 0)
    {
        char choixSom = 'c';
        do
        {
            cout << "Entrer l'étiquette du sommet " << i << " : ";
            cin >> etiqu_sommet;
            while (g->checkSommet(etiqu_sommet))
            {
                cout << "L'étiquette " << etiqu_sommet << " est déja pris par un autre sommet, veuillez entrer une autre étiquette: "
                                                          "[TAPEZ -1 POUR ANNULER] : ";
                cin >> etiqu_sommet;
            }
            if (etiqu_sommet == "-1")
            {
                break;
            }
            g->ajoute_sommet(etiqu_sommet);
            cout << "Sommet " << etiqu_sommet << " est créer avec succées.\n"
                 << endl;
            cout << "Voulez-vous ajouter un autre sommet [y/n] ?  : ";
            cin >> choixSom;
            i++;
        } while (choixSom == 'y');
    }
    else
    {
        cout << choix << "n'est pas parmie les choix, veuillez entrer un choix valide : ";
        cin >> choix;
    }
}

void ajouterArrete(Graph *g)
{
    int nbArrets;
    char choix = '?';
    cout << "Entrer le nombre d'arrets que vous souhaitez-créer"
            "[Entrer 0 si vous ne savez pas le nombre] :  ";
    cin >> nbArrets;
    if (nbArrets != 0)
    {
        int i = 0;
        while (i < nbArrets)
        {
            string s1;
            string s2;
            int poids;
            cout << "\nLes sommets du graph : ";
            g->afficherSommets();
            cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
            cout << "Entrer le premier sommet de l'arret [TAPEZ -1 POUR ANNULER] :  ";
            cin >> s1;
            if(s1 == "-1"){
                break;
            }
            while (checkSommet(g->getSommets(), s1, g->getNbSommet()) == false)
            {
                cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                cin >> choix;
                if (choix == 'y')
                {
                    g->ajoute_sommet(s1);
                    cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                    break;
                }
                else if (choix == 'n')
                {
                    cout << "Veuillez entrer un sommet valide : ";
                    cin >> s1;
                }
                else
                {
                    while (choix != 'y' || choix != 'n' || choix != '-1')
                    {
                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                        cin >> choix;
                    }
                }
            }
            cout << "\nEntrer le deuxieme sommet de l'arret :  ";
            cin >> s2;
            while (checkSommet(g->getSommets(), s2, g->getNbSommet()) == false)
            {
                cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                cin >> choix;
                if (choix == 'y')
                {
                    g->ajoute_sommet(s2);
                    cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                    break;
                }
                else if (choix == 'n')
                {
                    cout << "Veuillez entrer un sommet valide : ";
                    cin >> s2;
                }
                else
                {
                    while (choix != 'y' || choix != 'n' || choix != '-1')
                    {
                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                        cin >> choix;
                    }
                }
            }
            while (s1 == s2)
            {
                cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                        "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                cin >> s2;
                while (checkSommet(g->getSommets(), s2, g->getNbSommet()) == false)
                {
                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                  "[Tapez -1 si vous voulez quitter] :  ";
                    cin >> s2;
                }
            }
            cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
            cin >> poids;
            g->ajoute_arete(s1, s2, poids);
            cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                 << endl;
            i++;
        }
    }
    else if (nbArrets == 0)
    {
        int i = 0;
        char addArr = 'y';
        cout << "NOMBRE ARRET " << g->getNbSommet();
        while (addArr == 'y')
        {
            string s1;
            string s2;
            int poids;
            cout << "\nLes sommets du graph : ";
            g->afficherSommets();
            cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
            cout << "Entrer le premier sommet de l'arret [TAPEZ -1 POUR ANNULER] :  ";
            if(s1 == "-1")
                break;
            cin >> s1;
            while (checkSommet(g->getSommets(), s1, g->getNbSommet()) == false)
            {
                cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                cin >> choix;
                if (choix == 'y')
                {
                    g->ajoute_sommet(s1);
                    cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                    break;
                }
                else if (choix == 'n')
                {
                    cout << "Veuillez entrer un sommet valide : ";
                    cin >> s1;
                }
                else
                {
                    while (choix != 'y' || choix != 'n' || choix != '-1')
                    {
                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                        cin >> choix;
                    }
                }
            }
            cout << "\nEntrer le deuxieme sommet de l'arret :  ";
            cin >> s2;
            while (checkSommet(g->getSommets(), s2, g->getNbSommet()) == false)
            {
                cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                cin >> choix;
                if (choix == 'y')
                {
                    g->ajoute_sommet(s2);
                    cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                    break;
                }
                else if (choix == 'n')
                {
                    cout << "Veuillez entrer un sommet valide : ";
                    cin >> s2;
                }
                else
                {
                    while (choix != 'y' || choix != 'n' || choix != '-1')
                    {
                        cout << choix << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                        cin >> choix;
                    }
                }
            }
            while (s1 == s2)
            {
                cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                        "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                cin >> s2;
                while (checkSommet(g->getSommets(), s2, g->getNbSommet()) == false)
                {
                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                  "[Tapez -1 si vous voulez quitter] :  ";
                    cin >> s2;
                }
            }
            cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
            cin >> poids;
            g->ajoute_arete(s1, s2, poids);
            // aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
            cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                 << endl;
            i++;
            cout << "Voulez-vous ajouter un autre arrets [y/n] ? : ";
            cin >> addArr;
        }
    }
}

int main()
{
    /*EXAMPLE*/
    Graph **graph = new Graph *();
    Graph **graphKruskal = new Graph *();
    Sommet **s = new Sommet *();
    char choix = '?';
    int nbGraph_ = 0;
    int nbGraph_Kruskal = 0;
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
                cout << "Voulez-vous créer un graphe ? [y/n]  ";
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
            cout << "\n1 : Choix 1. Plus de détail sur un graph ? [MARCHE PAS]" << endl;
            cout << "2 : Revenir au menu." << endl;
            cin >> choix;
            if (choix == '1')
            {
                int numGraph = -1;
                cout << "Entrer le numéro du graph : ";
                cin >> numGraph;
                while (true)
                {
                    if (check(to_string(numGraph), nbGraph_, graph) == false)
                    {
                        Choix1(nbGraph_, graph);
                        cout << "Entrer le numéro du graph [Tapez -1 si vous voulez sortir]:";
                        cin >> numGraph;
                        if (numGraph == -1)
                        {
                            break;
                        }
                    }
                    else
                    {
                        cout << "\n*******  DETAILS GRAPH " << numGraph << "  *******" << endl;
                        cout << "- Nombre des sommets : " << graph[numGraph]->getNbSommet();
                        graph[numGraph]->afficherGraph();
                        cout << "- La somme des poids des arretes : " << graph[numGraph]->getSommePoids() << endl;
                        cout << "\n1.Modifier sur le graph" << endl;
                        cout << "2.Appliquer kruskal au graph" << endl;
                        cout << "3.Revenir au menu" << endl;
                        cin >> choix;
                        if (choix == '1')
                        {
                                cout << "1.Ajouter sommet" << endl;
                                cout << "2.Ajouter arret" << endl;
                                cout << "3.Revenir au menu" << endl;
                                cin >> choix;

                                if (choix == '1')
                                {
                                    ajouterSommet(graph[numGraph], s);
                                }
                                else if (choix == '2')
                                {
                                    ajouterArrete(graph[numGraph]);
                                    break;
                                }
                                else if (choix == '3')
                                {
                                    break;
                                }
                                else
                                {
                                    cout << choix << " n'est pas parmie les choix, veuillez entrer un choix valide : ";
                                    cin >> choix;
                                }
                        }
                        else if (choix == '2')
                        {
                            cout << "\n***** AVANT KRUSKAL *****\n";
                            graph[numGraph]->afficherGraph();
                            graphKruskal[nbGraph_Kruskal] = graph[numGraph]->kruskal();
                            cout << "\n***** APRES KRUSKAL *****\n";
                            graphKruskal[nbGraph_Kruskal]->afficherGraph();
                            nbGraph_Kruskal++;
                        }
                        else if (choix == '3')
                        {
                            break;
                        }
                        else
                        {
                            cout << choix << "n'est pas parmie les choix, veuillez entrer un choix valide : ";
                        }
                        break;
                    }
                }
            }
            break;
        case '2':
            graph[nbGraph_] = Choix2();
            nbGraph_++;
            break;
        case '3':
            if (nbGraph_ == 0)
            {
                cout << "Aucun graphe n'est créer, Veuillez créer un graph. [Tapez 2 pour le créer]\n\n"
                     << endl;
                break;
            }
            else if (nbGraph_ > 0)
            {
                Choix1(nbGraph_, graph);
                cout << "LE RESTE PAS ENCORE IMPLEMENTER [ C'EST LE MEME MODIFIER DU LISTER LES GRAPHES ]" << endl;
            }
            break;

        case '4':
            if (nbGraph_ == 0)
            {
                cout << "Aucun graphe n'est créer, Veuillez créer un graph. [Tapez 2 pour le créer]\n\n"
                     << endl;
                break;
            }
            Choix1(nbGraph_, graph);
            int numGraph;
            cout << "Entrer le numéro du graph au-quel vous souhaitez appliquez algorithme Kruskal : ";
            cin >> numGraph;
            cout << "\n***** AVANT KRUSKAL *****\n";
            graph[numGraph]->afficherGraph();
            graphKruskal[nbGraph_Kruskal] = graph[numGraph]->kruskal();
            cout << "\n***** APRES KRUSKAL *****\n";
            graphKruskal[nbGraph_Kruskal]->afficherGraph();
            nbGraph_Kruskal++;

            break;

        case '0':
            break;

        default:
            cerr << "Quoi ?" << endl;
            break;
        }
    } while (choix != '0');
    outtro();

    return 0;
}