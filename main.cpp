#include "./Graph.hpp"
#include <iostream>
#include <unistd.h>
using namespace std;

bool check(string numGraph, int nbGraph, vector<Graph*> graph)
{
    for (size_t i = 0; i < numGraph.length(); i++)
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
    return false;
}

bool checkDigit(string choix)
{
    for (size_t i = 0; i < choix.length(); i++)
    {
        if (isdigit(choix[i]) == true)
        {
            return true;
        }
    }
    return false;
}

void afficherSommets(vector<Sommet *>s, int n_sommet)
{
    for (int i = 0; i < n_sommet; i++)
    {
        cout << s[i]->getEtiquette() << ", ";
    }
    cout << endl;
}
vector<Sommet *> createSommets(int n_sommet)
{
    cout << "Création des sommets..." << endl;
    vector<Sommet *> s{};
    for (int i = 0; i < n_sommet; i++)
    {
        s.push_back(new Sommet(to_string(i), 0, 0));
    }
    sleep(1);
    cout << "Les sommets sont créer ave succcées." << endl;
    return s;
}

bool checkSommet(vector<Sommet *> s, string s_etiquette, int n_sommet)
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
    vector<Arete *> aretes{};
    vector<Sommet *>s{};
    int nbArrets = 0;
    char choix = '?';
    if (choix == '1')
    {
        cout << "1 : Choix 1. Ajouter sommet au graph" << endl;
        cout << "2 : Choix 2. Ajouter arret au graph" << endl;
    }
    else
    {
        cout << "1 : Choix 1. Créer sommet " << endl;
        cout << "2 : Choix 2. Créer arret " << endl;
    }
    cout << "3 : Choix 3. Créer un graph complet [Création automatique du graph]" << endl;
    cout << "4 : Choix 4. Revenir au menu." << endl;
    cin >> choix;
    switch (choix)
    {
    case '1':
    {
        cout << "1. Creer les sommets automatiquement " << endl;
        cout << "2. Creer les sommets manuel" << endl;
        cout << "3.Revenir au menu" << endl;
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
                        int i = 0;
                        while (i < nbArrets)
                        {
                            string s1;
                            string s2;
                            int poids;
                            cout << "\nLes sommets du graph : ";
                            afficherSommets(s, s.size());
                            cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                            cout << "Entrer le premier sommet de l'arret:  ";
                            cin >> s1;
                            while (checkSommet(s, s1, s.size()) == false)
                            {
                                cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s.push_back(new Sommet(s1, 0, 0));
                                    cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s1;
                                }
                            }
                            cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                            cin >> s2;
                            while (checkSommet(s, s2, s.size()) == false)
                            {
                                cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s.push_back(new Sommet(s2, 0, 0));
                                    cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s2;
                                }

                            }
                            while (s1 == s2)
                            {
                                cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                                        "Entre le deuxieme sommet  : ";
                                cin >> s2;
                                while (checkSommet(s, s2, s.size()) == false)
                                {
                                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                                  " :  ";
                                    cin >> s2;
                                }
                            }
                            cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                            cin >> poids;
                            aretes.push_back(new Arete(s1, poids, s2));
                            cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                                 << endl;
                            i++;
                        }
                    }
                    else if (nbArrets ==  0)
                    {
                        //aretes = new Arete *();
                        int i = 0;
                        char addArr = 'y';
                        while (addArr == 'y')
                        {
                            string s1;
                            string s2;
                            int poids;
                            cout << "\nLes sommets du graph : ";
                            afficherSommets(s, s.size());
                            cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                            cout << "Entrer le premier sommet de l'arret :  ";
                            cin >> s1;
                            while (checkSommet(s, s1, s.size()) == false)
                            {
                                cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s.push_back(new Sommet(s1, 0, 0));
                                    cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s1;
                                }
                            }
                            cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                            cin >> s2;
                            while (checkSommet(s, s2, s.size()) == false)
                            {
                                cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                cin >> choix;
                                if (choix == 'y')
                                {
                                    s.push_back(new Sommet(s1, 0, 0));
                                    cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                                    break;
                                }
                                else if (choix == 'n')
                                {
                                    cout << "Veuillez entrer un sommet valide : ";
                                    cin >> s2;
                                }
                            }
                            while (s1 == s2)
                            {
                                cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                                        "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                                cin >> s2;
                                while (checkSommet(s, s2, s.size()) == false)
                                {
                                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                                    cin >> choix;
                                    if (choix == 'y')
                                    {
                                        s.push_back(new Sommet(s2, 0, 0));
                                        nbS++;
                                        cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                                        break;
                                    }
                                    else if (choix == 'n')
                                    {
                                        cout << "Veuillez entrer un sommet valide : ";
                                        cin >> s2;
                                    }

                                }
                            }
                            cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                            cin >> poids;
                            aretes.push_back(new Arete(s1, poids, s2));
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
                break;
            }
            else
            {
                cout << choix << "N'est pas parmie les choix proposer veuillez choisir entre [y/n]" << endl;
                cout << "Les sommets vont être numérotés automatiquement"
                     << "vous ne pouvez pas spécifier l'étiquette du sommet !\n"
                     << "Voulez-vous continuer la création [y/n] ?" << endl;
                cout << "Pour sortir tapez q " << endl;
                cin >> choix;
                if (choix == 'q')
                {
                    break;
                }
            }
        }
        else if (choix == '2')
        {
            int nbrSommets = 0;
            cout << "Entrer le nombre de sommets que vous voulez ajouter [TAPEZ 0 SI VOUS NE SAVEZ PAS] : ";
            cin >> nbrSommets;
            int i = 0;
            string etiqu_sommet;
            if (nbrSommets > 0)
            {
                vector<Sommet *> so{};
                for (int i = 0; i < nbrSommets; i++)
                {
                    cout << "Entrer l'étiquette du sommet " << i << " : ";
                    cin >> etiqu_sommet;
                    so.push_back(new Sommet(etiqu_sommet, 0, 0));
                    cout << "Sommet " << etiqu_sommet << " est créer avec succées.\n"
                         << endl;
                }
                return new Graph(so, so.size(), aretes, aretes.size());
            }
            else if (nbrSommets == 0)
            {
                do
                {
                    cout << "Entrer l'étiquette du sommet " << i << " : ";
                    cin >> etiqu_sommet;
                    s.push_back(new Sommet(etiqu_sommet, 0, 0));
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
                return new Graph(s, s.size(), aretes, aretes.size());
            }
            else if (choix == '3')
            {
                break;
            }
            else
            {
                cout << "Veuillez entrer un nombre valide :  " << endl;
            }
        }
        return new Graph(s, s.size(), aretes, aretes.size());
    }
        
        break;

    case '2':
    {
        cout << "Entrer le nombre d'arrets que vous souhaitez-créer, Tapez 0 si vous ne savez pas le nombre"
                ":  ";
        cin >> nbArrets;
        if (nbArrets != 0)
        {
            //aretes = new Arete *[nbArrets];
            int i = 0;
            while (i < nbArrets)
            {
                string s1;
                string s2;
                int poids;
                cout << "\nLes sommets du graph : ";
                afficherSommets(s, s.size());
                cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                cout << "Entrer le premier sommet de l'arret  :  ";
                cin >> s1;
                while (checkSommet(s, s1, s.size()) == false)
                {
                    cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s.push_back(new Sommet(s1, 0, 0));
                        cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s1;
                    }

                }
                cout << "\nEntrer le deuxieme sommet de l'arret :  ";
                cin >> s2;
                while (checkSommet(s, s2, s.size()) == false)
                {
                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s.push_back(new Sommet(s2, 0, 0));
                        cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s2;
                    }
                }
                while (s1 == s2)
                {
                    cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                            "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                    cin >> s2;
                    while (checkSommet(s, s2, s.size()) == false)
                    {
                        cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                      "[Tapez -1 si vous voulez quitter] :  ";
                        cin >> s2;
                    }
                }
                cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                cin >> poids;
                aretes.push_back(new Arete(s1, poids, s2));
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
                afficherSommets(s, s.size());
                cout << "\nCreation de l'arret " << i << " : En cours ..." << endl;
                cout << "Entrer le premier sommet de l'arret :  ";
                cin >> s1;
                if (s1 == "-1")
                {
                    break;
                }
                while (checkSommet(s, s1, s.size()) == false)
                {
                    cout << "Le sommet " << s1 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s.push_back(new Sommet(s1, 0, 0));
                        cout << "Le sommet " << s1 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s1;
                    }
                }
                cout << "\nEntrer le deuxieme sommet de l'arret  :  ";
                cin >> s2;
                while (checkSommet(s, s2, s.size()) == false)
                {
                    cout << "Le sommet " << s2 << " n'éxiste pas en graph, voulez-vous l'ajouter au graph [y/n] ?  ";
                    cin >> choix;
                    if (choix == 'y')
                    {
                        s.push_back(new Sommet(s2, 0, 0));
                        cout << "Le sommet " << s2 << " a était créer avec succées " << endl;
                        break;
                    }
                    else if (choix == 'n')
                    {
                        cout << "Veuillez entrer un sommet valide : ";
                        cin >> s2;
                    }

                }
                while (s1 == s2)
                {
                    cout << "\nVous avez entrer le meme sommet!! Veuillez entrer un sommet different \n"
                            "Entre le deuxieme sommet [Tapez -1 pour sortir] : ";
                    cin >> s2;
                    while (checkSommet(s, s2, s.size()) == false)
                    {
                        cout << "Le sommet " << s2 << " n'éxiste pas en graph, veuillez entrer une sommet valide "
                                                      "[Tapez -1 si vous voulez quitter] :  ";
                        cin >> s2;
                    }
                }
                cout << "\nEntrer Poids de l'arret (Sommet1: " << s1 << ", Sommet2: " << s2 << " Poids: ";
                cin >> poids;
                aretes.push_back(new Arete(s1, poids, s2));
                // aretes[0] = new Arete(s[0], 9, s[1]);  /* Arete(Sommet_1, Poids, Sommet_2) */
                cout << "\nL'arret (" << s1 << "," << poids << ", " << s2 << ") est créer avec succés..\n"
                     << endl;
                i++;
                cout << "Voulez-vous ajouter un autre arrets [y/n] ? : ";
                cin >> addArr;
            }
        }
        else if (nbArrets == -1)
        {
            break;
        }
    }
        return new Graph(s, s.size(), aretes, aretes.size());
        break;
    case '3':
    {
        s = createSommets(5);
        vector<Arete *> arete{};
        cout << "Création des arrets..." << endl;
        sleep(1);
        arete.push_back(new Arete(s[0], 9, s[1]));  /* Arete(Sommet_1, Poids, Sommet_2) */
        arete.push_back(new Arete(s[0], 75, s[2])); /* Creation d'une arrete avec des sommets qui n'existe pas */
        arete.push_back(new Arete(s[1], 95, s[2]));
        arete.push_back(new Arete(s[1], 19, s[3]));
        arete.push_back(new Arete(s[2], 51, s[3]));
        arete.push_back(new Arete(s[1], 42, s[4]));
        arete.push_back(new Arete(s[4], 31, s[3]));
        cout << "Création du graph..." << endl;
        sleep(1);
        cout << "Le graph est créer.\n"
             << endl;
        return new Graph(s, s.size(), arete, arete.size());
    }
    break;
    case '4':
        break;
    }
    return new Graph();
}

void ajouterSommet(Graph *g, vector<Sommet*> s)
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
                                                          ": ";
                cin >> etiqu_sommet;
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
                                                          ": ";
                cin >> etiqu_sommet;
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
            cout << "Entrer le premier sommet de l'arret:  ";
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
            cout << "Entrer le premier sommet de l'arret :  ";
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
                    string x = "?";
                    while (x != "y" || x != "n" || x != "-1")
                    {
                        cout << x << " n'est pas parmie les choix, Entrer un choix valide [Tapez -1 pour sortir] :  ";
                        cin >> x;
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

void intro()
{
    cout << "\n0 : Sortir." << endl;
    cout << "1 : Choix 1.Lister les grahes existants" << endl;
    cout << "2 : Choix 2.Créer un nouveau Graph" << endl;
    cout << "3 : Choix 3.Modifier un graph existant." << endl;
    cout << "4 : Choix 4.Appliquer Kruskal a un graph." << endl;
    cout << "5 : Choix 5.Créer les sommets d'un graph à partir d'un autre graph." << endl;
    cout << "6 : Choix 6.Symetrise." << endl;
}

void outtro()
{
    cout << "Au revoir." << endl;
}

void Choix1(int nbGraph, vector<Graph*> g)
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

void Choix3(Graph *g, vector<Sommet *> s)
{
    char choix = '?';
    cout << "1. Choix1.Ajouter sommet au graph." << endl;
    cout << "2. Choix2.Ajouter arret au graph." << endl;
    cout << "3. Choix3.Revenir au menu." << endl;
    cin >> choix;
    if (choix == '1')
    {
        ajouterSommet(g, s);
    }
    else if (choix == '2')
    {
        ajouterArrete(g);
    }
}
void Choix4()
{
    cout << "\nVous avez fait le choix 4." << endl;
}
Graph *Choix5(Graph *graph)
{
    char choix = '?';
    cout << "\nVous avez fait le choix 5." << endl;
    cout << "Création des sommets..." << endl;
    sleep(1);
    Graph *G = graph->newGraph();
    G->afficherGraph();
    cout << "Voulez-vous créer des arrets pour le graph [y/n] ?: ";
    cin >> choix;
    while (choix != 'y' && choix != 'n')
    {
        cout << choix << " n'est pas parmie les choix proposer, veuillez entrer un choix valide.";
        cout << "Voulez-vous créer des arrets pour le graph [y/n] ?: ";
        cin >> choix;
    }
    if (choix == 'y')
    {
        ajouterArrete(G);
    }
    cout << "Création du graph..." << endl;
    sleep(1);
    cout << "Le graph est créer avec succées.";

    return G;
}

int main()
{
    /*EXAMPLE*/
    vector<Graph *> graph{};
    vector<Graph *> graphKruskal{};
    vector<Sommet* >s{};
    char choix = '?';
    cout << "Bonjour." << endl;
    do
    {
        intro();
        cin >> choix;
        switch (choix)
        {
        case '1':
            cout << "Vous avez fait le choix 1." << endl;
            if (graph.size() == 0)
            {
                cout << "Aucun graphe n'est créer" << endl;
                cout << "Voulez-vous créer un graphe ? [y/n]  ";
                cin >> choix;
                if (choix == 'y')
                {
                    graph.push_back(Choix2());
                    createSommetArrete();
                }
                break;
            }
            Choix1(graph.size(), graph);
            cout << "\n1 : Choix 1. Plus de détail sur un graph ?" << endl;
            cout << "2 : Revenir au menu." << endl;
            cin >> choix;
            if (choix == '1')
            {
                int numGraph = -1;
                cout << "Entrer le numéro du graph : ";
                cin >> numGraph;
                while (true)
                {
                    if (check(to_string(numGraph), graph.size(), graph) == false)
                    {
                        Choix1(graph.size(), graph);
                        cout << "Entrer le numéro du graph :";
                        cin >> numGraph;
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
                            graphKruskal.push_back(graph[numGraph]->kruskal());
                            cout << "\n***** APRES KRUSKAL *****\n";
                            graphKruskal[graphKruskal.size()-1]->afficherGraph();
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
            graph.push_back(Choix2());
            break;
        case '3':
            if (graph.size() == 0)
            {
                cout << "Vous avez fait le choix 3." << endl;
                cout << "Aucun graphe n'est créer, Veuillez créer un graph. [Tapez 2 pour le créer]\n\n"
                     << endl;
                break;
            }
            else if (graph.size() > 0)
            {
                cout << "Vous avez fait le choix 3." << endl;
                Choix1(graph.size(), graph);
                int numGraph;
                cout << "Entrer le numéro du graph au-quel vous souhaitez modifier : ";
                cin >> numGraph;
                Choix3(graph[numGraph], s);
            }
            break;

        case '4':
        {
            if (graph.size() == 0)
            {
                cout << "Aucun graphe n'est créer, Veuillez créer un graph. [Tapez 2 pour le créer]\n\n"
                     << endl;
                break;
            }
            cout << "vous avez fait le choix 4." << endl;
            Choix1(graph.size(), graph);
            int numGraph;
            cout << "Entrer le numéro du graph au-quel vous souhaitez appliquez algorithme Kruskal : ";
            cin >> numGraph;
            cout << "\n***** AVANT KRUSKAL *****\n";
            graph[numGraph]->afficherGraph();
            graphKruskal.push_back(graph[numGraph]->kruskal());
            cout << "\n***** APRES KRUSKAL *****\n";
            graphKruskal[graphKruskal.size()-1]->afficherGraph();
        }
        break;
        case '5':
        {
            if (graph.size() == 0)
            {
                cout << "Aucun graphe n'est créer, Veuillez créer un graph. [Tapez 2 pour le créer]\n\n"
                     << endl;
                break;
            }
            Choix1(graph.size(), graph);
            int numGraph;
            cout << "Entrer le numéro du graph au-quel vous souhaitez copier les memes sommets : ";
            cin >> numGraph;
            graph.push_back(Choix5(graph[numGraph]));
        }
        break;
        case '6':
            int numGraph;
            if(graph.size() <= 0){
                 cout << "Aucun graphe n'est créer" << endl;
                 cout << "Pour créer un tapez 2" << endl;
                 break;
            }
            Choix1(graph.size(), graph);
            cout << "Entrer le numéro du graph au-quel vous souhaitez appliquez symetrise : ";
            cin >> numGraph;
            cout << "\n***** AVANT SYMETRISE *****\n";
            graph[numGraph]->afficherGraph();
            cout << "\n***** APRES SYMETRISE *****\n";
            graph[numGraph]->symetrise();
            graph[numGraph]->afficherGraph();
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