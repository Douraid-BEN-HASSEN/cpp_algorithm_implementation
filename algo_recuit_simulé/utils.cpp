#include "utils.h"

vector<vector<int>> positionInterdite;
vector<Color> tab;

int nbCase;
int nbViolation = 0;

void init() {
    positionInterdite = readCol("queen5_5.col");
    std::fill_n(std::back_inserter(tab), getNbCase(), Color::EMPTY);

}

// +-------+
// | UTILS |
// +-------+
std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }

    return result;
}

vector<vector<int>> readCol(const char* pFile) {
    vector<vector<int>> result;
    std::ifstream f;
    std::string line;
    std::string content = "";

    f.open(pFile);
    if (f.is_open())
    {
        int indexActuel = -1;
        while (getline(f, line))
        {
            if (line[0] == 'p') {
                nbCase = stoi(split(line, ' ')[2]);
            }
            else if (line[0] == 'e') {
                if ((indexActuel + 1) != stoi(split(line, ' ')[1])) {
                    indexActuel = stoi(split(line, ' ')[1]) - 1;
                    result.push_back({ stoi(split(line, ' ')[2]) - 1 });
                }
                else result[indexActuel].push_back(stoi(split(line, ' ')[2]) - 1);
            }
        }
        f.close();
    }

    return result;
}

int countNbViolation(int pCase, Color pColor) {
    int nViolation = 0;
    for (int iCase = 0; iCase < positionInterdite[pCase].size(); iCase++) {
        if (tab[positionInterdite[pCase][iCase]] == pColor) {
            nViolation++;
        }
    }

    return nViolation;
}

int countNbViolation(vector<Color> pTab, int pCase, Color pColor) {
    int nViolation = 0;
    for (int iCase = 0; iCase < positionInterdite[pCase].size(); iCase++) {
        if (pTab[positionInterdite[pCase][iCase]] == pColor) {
            nViolation++;
        }
    }

    return nViolation/2;
}

int getRandomNumber(int max)
{
    return rand() % max;
}

// +--------+
// | GETTER |
// +--------+
int getNbCase() {
    return nbCase;
}

int getNbViolation()
{
    return nbViolation;
}

vector<Color> getTab() {
    return tab;
}

// +------+
// | ALGO |
// +------+
void algo_violation() {
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
        nbViolation += countNbViolation(iCase, tab[iCase]);
    }

    nbViolation /= 2;
}

void algo_violation(vector<Color> pTab) {
    // remplir la grille
    int nbReinePlacee;
    int nViolation = 0;

    // compte nViolation
    for (int iCase = 0; iCase < getNbCase(); iCase++) {
        nViolation += countNbViolation(pTab, iCase, pTab[iCase]);
    }

    nViolation /= 2;
}

void algo_recuit()
{
    // etape 1 : init => remplir tab
    int nRouge = 0;
    int nJaune = 0;
    int nVert = 0;
    int nBleu = 0;
    int nViolet = 0;
    int nMax = 5;

    srand(time(NULL));
    while (!(nRouge == 5 && nJaune == 5 && nVert == 5 && nBleu == 5 && nViolet == 5))
    {
        if (nRouge < 5) {
            Color color = Color::ROUGE;
            int randomCase = getRandomNumber(getNbCase());
            if (tab[randomCase] == Color::EMPTY) {
                tab[randomCase] = color;
                nRouge++;
            }
        }
        else if (nJaune < 5) {
            Color color = Color::JAUNE;
            int randomCase = getRandomNumber(getNbCase());
            if (tab[randomCase] == Color::EMPTY) {
                tab[randomCase] = color;
                nJaune++;
            }
        }
        else if (nVert < 5) {
            Color color = Color::VERT;
            int randomCase = getRandomNumber(getNbCase());
            if (tab[randomCase] == Color::EMPTY) {
                tab[randomCase] = color;
                nVert++;
            }
        }
        else if (nBleu < 5) {
            Color color = Color::BLEU;
            int randomCase = getRandomNumber(getNbCase());
            if (tab[randomCase] == Color::EMPTY) {
                tab[randomCase] = color;
                nBleu++;
            }
        }
        else if (nViolet < 5) {
            Color color = Color::VIOLET;
            int randomCase = getRandomNumber(getNbCase());
            if (tab[randomCase] == Color::EMPTY) {
                tab[randomCase] = color;
                nViolet++;
            }
        }
    }

    // etape 2
    int xc = 999;
    int x1;
    int x2;
    double temperature = 100.0;

    int random_value_1;
    int random_value_2;

    int nbIteration = 0;
    
    while (nbIteration < 10000 && xc > 0)
    {
        xc = 0;
        x1 = 0;
        x2 = 0;

        vector<Color> tab_voisin1 = tab;
        vector<Color> tab_voisin2 = tab;
        Color color_tmp;

        // compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            xc += countNbViolation(tab, iCase, tab[iCase]);
        }

        // nb violation x1
        random_value_1 = getRandomNumber(24);
        random_value_2 = getRandomNumber(24);
        color_tmp = tab_voisin1[random_value_1];
        tab_voisin1[random_value_1] = tab_voisin1[random_value_2];
        tab_voisin1[random_value_2] = color_tmp;
        //  compte nb violation sur tab_voisin1
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x1 += countNbViolation(tab_voisin1, iCase, tab_voisin1[iCase]);
        }

        // nb violation x2
        random_value_1 = getRandomNumber(24);
        random_value_2 = getRandomNumber(24);
        color_tmp = tab_voisin2[random_value_1];
        tab_voisin2[random_value_1] = tab_voisin2[random_value_2];
        tab_voisin2[random_value_2] = color_tmp;
        //  compte nb violation sur tab_voisin2
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x2 += countNbViolation(tab_voisin2, iCase, tab_voisin2[iCase]);
        }
        
        if (x1 < xc)
        {
            tab = tab_voisin1;
        }
        else if (x2 > xc && ((double)(x2 - xc) / temperature) < ((double)rand() / RAND_MAX))
        {
            tab = tab_voisin2;
            temperature -= 0.1;
        }
        nbIteration++;
    }

    nbViolation = xc;
    cout << "nbIteration => " << nbIteration << endl;
    cout << "XC => " << xc << endl;
    cout << "TP => " << temperature << endl;
}
