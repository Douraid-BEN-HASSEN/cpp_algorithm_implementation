#include <iostream>
#include "utils.h"

using namespace std;

vector<vector<int>> positionInterdite;
vector<Color> tab;

void init();
void algo_Violation();
int getNbViolation(int, Color);

int nbViolation = 0;

int main()
{
    init();

    algo_Violation();

}

void init() {
    positionInterdite = readCol("queen5_5.col");
    std::fill_n(std::back_inserter(tab), getNbCase(), Color::EMPTY);
}

void algo_Violation() {
    // remplir la grille
    int nbReinePlacee;

    for (int iColor = 1; iColor < 6; iColor++) {
        nbReinePlacee = 0;
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            if (nbReinePlacee < 5) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    nbReinePlacee++;
                }
            }
            else break;
            
        }
    }

    // compte nbViolation
    for (int iCase = 0; iCase < getNbCase(); iCase++) {
        nbViolation += getNbViolation(iCase, tab[iCase]);
    }

    nbViolation /= 2;
}

int getNbViolation(int pCase, Color pColor) {
    int nViolation = 0;
    for (int iCase = 0; iCase < positionInterdite[pCase].size(); iCase++) {
        if (tab[positionInterdite[pCase][iCase]] == pColor) {
            nViolation++;
        }
    }

    return nViolation;
}
