#include "utils.h"

vector<vector<int>> positionInterdite;
vector<Color> tab;

string algo;

int nCouleurDifferente = 5;
string fileName = "queen5_5.col";
int nbCase;
int nbViolation = 0;

void init() {
    positionInterdite = readCol(fileName.c_str());
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

    return nViolation;
}

int countNbViolation(vector<Color> pTab) {
    int nViolation = 0;
    for (int iCase = 0; iCase < pTab.size(); iCase++) {
        for (int iCaseInterdite = 0; iCaseInterdite < positionInterdite[iCase].size(); iCaseInterdite++) {
            if (pTab[positionInterdite[iCase][iCaseInterdite]] == pTab[iCase]) {
                nViolation++;
            }
        }
    }

    return nViolation/2;
}

int getRandomNumber(int max)
{
    return rand() % max;
}

std::vector<Color>readOutput(const char* pFile) {
    vector<Color> result;
    std::ifstream f;
    std::string line;
    std::string content = "";

    f.open(pFile);
    if (f.is_open())
    {
        int indexActuel = -1;
        while (getline(f, line))
        {
            if (line[0] != 'c' && line[0] != 'f' && line[0] != 'r') {
                result.push_back((Color)std::stoi(line));
            }
        }
        f.close();
    }

    return result;
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

string getAlgo() {
    return algo;
}

vector<Color> getTab() {
    return tab;
}

int getnCouleurDifferente() {
    return nCouleurDifferente;
}

string getFileName() {
    return fileName;
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

    nbViolation = nViolation / 2;
}

void algo_recuit()
{
    algo = "algo recuit";

    // etape 1 : init => remplir tab
    // INIT
    srand(time(NULL));

    bool remplie = false;
    while (!remplie) {
        remplie = true;

        for (int iColor = 1; iColor < nCouleurDifferente+1; iColor++) {
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    break;
                }
            }
        }

        for (int cpt = 0; cpt < tab.size(); cpt++) {
            if (tab[cpt] == Color::EMPTY) {
                remplie = false;
                break;
            }
        }
    }
    
    // melanger les cases
    for (int iCase = 0; iCase < getNbCase(); iCase++) {

    }
    // ------

    // etape 2
    int xc = 999;
    int x1;
    int x2;
    double temperature = 2500;

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
        xc /= 2;

        // nb violation x1
        random_value_1 = getRandomNumber(getNbCase()-1);
        random_value_2 = getRandomNumber(getNbCase()-1);
        color_tmp = tab_voisin1[random_value_1];
        tab_voisin1[random_value_1] = tab_voisin1[random_value_2];
        tab_voisin1[random_value_2] = color_tmp;
        //  compte nb violation sur tab_voisin1
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x1 += countNbViolation(tab_voisin1, iCase, tab_voisin1[iCase]);
        }
        x1 /= 2;

        // nb violation x2
        random_value_1 = getRandomNumber(getNbCase() - 1);
        random_value_2 = getRandomNumber(getNbCase() - 1);
        color_tmp = tab_voisin2[random_value_1];
        tab_voisin2[random_value_1] = tab_voisin2[random_value_2];
        tab_voisin2[random_value_2] = color_tmp;
        //  compte nb violation sur tab_voisin2
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x2 += countNbViolation(tab_voisin2, iCase, tab_voisin2[iCase]);
        }
        x2 /= 2;

        if (x1 < xc)
        {
            tab = tab_voisin1;
            //xc += x1;
        }
        else if (x2 > xc && ((double)(x2 - xc) / temperature) < ((double)rand() / RAND_MAX))
        {
            tab = tab_voisin2;
            temperature = temperature * 0.99;
            //xc += x2;
        }
        nbIteration++;
    }

    nbViolation = xc;

    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "XC => " << xc << endl;
    std::cout << "TP => " << temperature << endl;
}

// ok
void algo_descente() {
    algo = "algo decente";

    // etape 1 : init => remplir tab

    srand(time(NULL));
    bool remplie = false;
    while (!remplie) {
        remplie = true;

        for (int iColor = 1; iColor < nCouleurDifferente + 1; iColor++) {
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    break;
                }
            }
        }

        for (int cpt = 0; cpt < tab.size(); cpt++) {
            if (tab[cpt] == Color::EMPTY) {
                remplie = false;
                break;
            }
        }
    }

    // etape 2
    int x_courant = 999;
    int x_voisin;

    int random_value_1;
    int random_value_2;

    int nbIteration = 0;

    vector<Color> tab_voisin;

    while (nbIteration < 10000 && x_courant > 0)
    {
        x_courant = 0;
        x_voisin = 0;

        //  compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x_courant += countNbViolation(tab, iCase, tab[iCase]);
        }
        x_courant /= 2;

        Color color_tmp;
        // nb violation courante
        random_value_1 = getRandomNumber(getNbCase() - 1);
        random_value_2 = getRandomNumber(getNbCase() - 1);
        tab_voisin = tab;
        color_tmp = tab_voisin[random_value_1];
        tab_voisin[random_value_1] = tab_voisin[random_value_2];
        tab_voisin[random_value_2] = color_tmp;
        //  compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x_voisin += countNbViolation(tab_voisin, iCase, tab_voisin[iCase]);
        }
        x_voisin /= 2;

        if (x_voisin < x_courant)
        {
            tab = tab_voisin;
            x_courant = x_voisin;
        }
        else if ((double)rand() / RAND_MAX > 0.5)
        {
            tab = tab_voisin;
            x_courant = x_voisin;
        }
        nbIteration++;
    }
 
    nbViolation = x_courant;
    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "SOLUTION_COURANTE => " << x_courant << endl;
}

// ok (a revoir)
void algo_gsat() {
    algo = "gsat";

    // prend le meilleur de algo_descente
    // etape 1 : init => remplir tab    

    srand(time(NULL));
    bool remplie = false;

    while (!remplie) {
        remplie = true;

        for (int iColor = 1; iColor < nCouleurDifferente + 1; iColor++) {
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    break;
                }
            }
        }

        for (int cpt = 0; cpt < tab.size(); cpt++) {
            if (tab[cpt] == Color::EMPTY) {
                remplie = false;
                break;
            }
        }
    }

    // etape 2
    int x_courant = 999;
    int x_voisin;

    int random_value_1;
    int random_value_2;

    int nbIteration = 0;

    vector<Color> meilleur_solution;
    vector<Color> tab_voisin;

    int meilleur_solution_val = -1;

    while (nbIteration < 100000 && x_courant > 0)
    {
        x_courant = 0;
        x_voisin = 0;

        //  compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x_courant += countNbViolation(tab, iCase, tab[iCase]);
        }
        x_courant /= 2;

        Color color_tmp;
        // nb violation courante
        random_value_1 = getRandomNumber(getNbCase()-1);
        random_value_2 = getRandomNumber(getNbCase()-1);
        tab_voisin = tab;
        color_tmp = tab_voisin[random_value_1];
        tab_voisin[random_value_1] = tab_voisin[random_value_2];
        tab_voisin[random_value_2] = color_tmp;
        //  compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x_voisin += countNbViolation(tab_voisin, iCase, tab_voisin[iCase]);
        }
        x_voisin /= 2;

        if (x_voisin < x_courant)
        {
            meilleur_solution = tab_voisin;
            meilleur_solution_val = x_voisin;
            x_courant = x_voisin;
            tab = tab_voisin;
        }
        else if ((double)rand() / RAND_MAX > 0.5)
        {
            tab = tab_voisin;
        }
        nbIteration++;
    }

    nbViolation = x_courant;

    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "SOLUTION_COURANTE => " << x_courant << endl;
    std::cout << "MEILLEUR_SOL => " << meilleur_solution_val << endl;
}

// ok
void algo_random_walk() {
    algo = "algo random walk";

    // tire au hasard jusqu'à nErreur = 0 ou nbIteration > NMAX
    // etape 1 : init => remplir tab

    srand(time(NULL));
    bool remplie = false;
    while (!remplie) {
        remplie = true;

        for (int iColor = 1; iColor < nCouleurDifferente + 1; iColor++) {
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    break;
                }
            }
        }

        for (int cpt = 0; cpt < tab.size(); cpt++) {
            if (tab[cpt] == Color::EMPTY) {
                remplie = false;
                break;
            }
        }
    }

    // etape 2
    int meilleur_sol = 999;
    int x_courant;

    int random_value_1;
    int random_value_2;

    int nbIteration = 0;
    vector<Color> voisin;

    while (nbIteration < 10000 && meilleur_sol > 0)
    {
        x_courant = 0;
        voisin = tab;

        Color color_tmp;
        // nb violation courante
        random_value_1 = getRandomNumber(getNbCase()-1);
        random_value_2 = getRandomNumber(getNbCase()-1);
        color_tmp = voisin[random_value_1];
        voisin[random_value_1] = voisin[random_value_2];
        voisin[random_value_2] = color_tmp;
        //  compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x_courant += countNbViolation(voisin, iCase, voisin[iCase]);
        }
        x_courant /= 2;

        if (x_courant < meilleur_sol) {
            meilleur_sol = x_courant;
            tab = voisin;
        }

        nbIteration++;
    }

    nbViolation = meilleur_sol;

    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "SOLUTION_COURANTE => " << meilleur_sol << endl;
}

// ok
void algo_recherche_tabou() {
    algo = "algo recherche tabou";

    // etape 1 : init => remplir tab
    srand(time(NULL));
    bool remplie = false;
    while (!remplie) {
        remplie = true;

        for (int iColor = 1; iColor < nCouleurDifferente + 1; iColor++) {
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    break;
                }
            }
        }

        for (int cpt = 0; cpt < tab.size(); cpt++) {
            if (tab[cpt] == Color::EMPTY) {
                remplie = false;
                break;
            }
        }
    }

    // etape 2 : traitement
    vector<Color> voisin;
    vector<vector<vector<Color>>> grilleTabou;
    vector<vector<Color>> lVide1;
    vector<Color> lVide2;
    std::fill_n(std::back_inserter(lVide2), getNbCase(), Color::EMPTY);
    for (int i = 0; i < getNbCase(); i++) {
        grilleTabou.push_back(lVide1);
    }

    int nViolation = 999;    
    int bestViol = 999;
    int nbIteration = 0;

    while (nbIteration < 10000 && nViolation > 0) {
        int iBestCase = -1;
        int iBestGrille = -1;
        int bestVal = -1;

        // etape 1
        // trouver la case avec le meilleur score en changeant les couleurs       
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
                voisin = tab;

                Color originalColor = voisin[iCase];
                Color bestColor = Color::EMPTY;                

                while (bestColor == Color::EMPTY)
                {
                    bestColor = (Color)(1 + getRandomNumber(nCouleurDifferente));
                    if (bestColor == originalColor) bestColor = Color::EMPTY;
                }

                // check chaque grille pour la case
                voisin[iCase] = bestColor; // change la couleur pour la comparer avec la liste tabou
                bool isTabou = false;
                for (int iCheckTabou = 0; iCheckTabou < grilleTabou[iCase].size(); iCheckTabou++) {
                    isTabou = true;
                    for (int i = 0; i < grilleTabou[iCase][iCheckTabou].size(); i++) {
                        if (grilleTabou[iCase][iCheckTabou][i] != voisin[i]) {
                            isTabou = false;
                            break;
                        }
                    }
                }

                if (!isTabou) {
                    int tmpNbViol = 0;
                    voisin[iCase] = bestColor;

                    for (int iCaseTest = 0; iCaseTest < getNbCase(); iCaseTest++) {
                        tmpNbViol += countNbViolation(voisin, iCaseTest, voisin[iCaseTest]);
                    }
                    tmpNbViol /= 2;

                    if (tmpNbViol < bestViol) {
                        grilleTabou[iCase].push_back(voisin);
                        bestViol = tmpNbViol;
                        bestVal = bestViol;
                        iBestCase = iCase;
                        iBestGrille = grilleTabou[iCase].size() - 1; // le meilleur est forcément la dernière case
                    }
                }
                // critère d'aspiration
                else {
                    int tmpNbViol = 0;
                    voisin[iCase] = bestColor;

                    for (int iCaseTest = 0; iCaseTest < getNbCase(); iCaseTest++) {
                        tmpNbViol += countNbViolation(voisin, iCaseTest, voisin[iCaseTest]);
                    }
                    tmpNbViol /= 2;

                    if (tmpNbViol < bestViol) {
                        bestViol = tmpNbViol;
                        bestVal = bestViol;
                        iBestCase = iCase;
                        iBestGrille = grilleTabou[iCase].size() - 1; // le meilleur est forcément la dernière case
                    }
                }

            }
        
        // etape 2
        // get best case
        if (iBestCase > -1 && iBestGrille > -1) {
            voisin = tab;
            voisin = grilleTabou[iBestCase][iBestGrille];
            int nbViolationTmp = 0;
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                nbViolationTmp += countNbViolation(voisin, iCase, voisin[iCase]);
            }
            nbViolationTmp /= 2;

            if (nbViolationTmp < nViolation) {
                tab = voisin;
                nViolation = nbViolationTmp;
            }
        }
        std::cout << "iteration => " << nbIteration << std::endl;
        nbIteration++;
    }
    
    nbViolation = nViolation;
    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "SOLUTION_COURANTE => " << nViolation << endl;
}

// ok
vector<Color> algo_gww_random_walk(vector<Color> pTab) {
    int random_value_1 = getRandomNumber(getNbCase() - 1);
    int random_value_2 = getRandomNumber(getNbCase() - 1);
    Color color_tmp = pTab[random_value_1];
    pTab[random_value_1] = pTab[random_value_2];
    pTab[random_value_2] = color_tmp;
    return pTab;
}

void algo_gww() {
    algo = "algo gww";

    int nbParticule = 10;
    int seuil = 80;
    int nbRandomWalk = 10;

    // etape 1 : init => remplir tab
    srand(time(NULL));
    bool remplie = false;
    while (!remplie) {
        remplie = true;

        for (int iColor = 1; iColor < nCouleurDifferente + 1; iColor++) {
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                if (tab[iCase] == Color::EMPTY) {
                    tab[iCase] = (Color)iColor;
                    break;
                }
            }
        }

        for (int cpt = 0; cpt < tab.size(); cpt++) {
            if (tab[cpt] == Color::EMPTY) {
                remplie = false;
                break;
            }
        }
    }
    // remplissage particule
    vector<vector<Color>> grilleParticule;
    vector<Color> particule = tab;

    for (int i = 0; i < nbParticule; i++) {
        int random_value_1 = getRandomNumber(getNbCase() - 1);
        int random_value_2 = getRandomNumber(getNbCase() - 1);
        Color color_tmp = particule[random_value_1];
        particule[random_value_1] = particule[random_value_2];
        particule[random_value_2] = color_tmp;
        grilleParticule.push_back(particule);
    }

    int nbIteration = 0;
    int maxIteration = 10000;
    int bestSolution = 999;
    vector<Color> bestTab;

    while (bestSolution > 0 && nbIteration < maxIteration)
    {
        // faire un random walk sur chaque particule
        for (int iParticule = 0; iParticule < grilleParticule.size(); iParticule++) {
            for (int iRandomWalk = 0; iRandomWalk < nbRandomWalk; iRandomWalk++) {
                grilleParticule[iParticule] = algo_gww_random_walk(grilleParticule[iParticule]);
            }
        }

        // compter le nb de violation pour chaque particule
        vector<vector<Color>> particulesValide;
        vector<vector<Color>> particulesInvalide;

        for (int iParticule = 0; iParticule < grilleParticule.size(); iParticule++) {
            int nViolation = countNbViolation(grilleParticule[iParticule]);
            if (nViolation < seuil) particulesValide.push_back(grilleParticule[iParticule]);
            else particulesInvalide.push_back(grilleParticule[iParticule]);

            if (nViolation < bestSolution) {
                bestSolution = nViolation;
                bestTab = grilleParticule[iParticule];
            }
        }

        grilleParticule.clear();
        grilleParticule = particulesValide;
        if (grilleParticule.size()) {
            for (int iParticulesInvalide = 0; iParticulesInvalide < particulesInvalide.size(); iParticulesInvalide++) {
                particulesInvalide[iParticulesInvalide] =particulesValide[getRandomNumber(particulesValide.size())];
                grilleParticule.push_back(particulesInvalide[iParticulesInvalide]);
            }
            seuil -= 1;
        }
        else {
            grilleParticule = particulesInvalide;
        }

        //
        nbIteration++;
    }

    tab = bestTab;
    nbViolation = bestSolution;
    std::cout << "seuil => " << seuil << endl;
    std::cout << "SOLUTION => " << bestSolution << endl;
}
// ----
