using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

int ROUGE = 0;
int BLEU = 1;
int JAUNE = 2;
int VERT = 3;
int VILOET = 4;

const int tailleMatrice = 5;
int matrice[tailleMatrice][tailleMatrice];
int chaine[5] = {0,1,2,3,4};

// Fonction "SwapChaine".
void SwapChaine()
{
    int stock1;
    int stock2;

    stock1 = chaine[3];
    stock2 = chaine[4];

    chaine[4] = chaine[2];
    chaine[3] = chaine[1];
    chaine[2] = chaine[0];
    chaine[1] = stock2;
    chaine[0] = stock1;
}

// Fonction "LectureFichier".
// Permet de lire le fichier en question.
int LectureFichier()
{
    string filename("Graphe/queen5_5.col");
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open())
    {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return EXIT_FAILURE;
    }

    while (getline(input_file, line))
    {
        lines.push_back(line);
    }

    for (const auto &i : lines)
    {
        cout << i << endl;
    }
    input_file.close();
    return EXIT_SUCCESS;
}

// Fonction "RemplissageAleatoire".
// Permet de remplir une matrice avec des couleurs aleatoire.
void RemplissageAleatoire()
{
    for (int i = 0 ; i < tailleMatrice ; i++)
    {
        for (int j = 0 ; j < tailleMatrice ; j++)
        {
            matrice[i][j] = rand()%5;
            cout << matrice[i][j] << " ";
        }

        cout << endl;
    }
}

// Fonction "RemplissageAlgo".
// Fonction qui permet de remplir une matrice avec les couleurs suivant l'algo.
void RemplissageAlgo()
{
    for (int i = 0 ; i < tailleMatrice ; i++)
    {
        for (int j = 0 ; j < tailleMatrice ; j++)
        {
            matrice[i][j] = chaine[j];
            cout << matrice[i][j] << " ";
        }
        SwapChaine();
        cout << endl;
    }
}



int main ()
{
    // RemplissageAleatoire();
    RemplissageAlgo();
    // LectureFichier();

    
}