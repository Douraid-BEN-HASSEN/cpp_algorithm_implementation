#include "utils.h"

vector<vector<int>> positionInterdite;
vector<Color> tab;

string algo;

int nCouleurDifferente = 44;
string folder = "./DSJC/";
string fileName = "DSJC125.9.col";
int nbCase;
int nbViolation = 0;

string readFromOutput = "";

void init() {
    positionInterdite = readCol((folder + fileName).c_str());
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
            indexActuel++;
            if (line[0] == 'p') {
                nbCase = stoi(split(line, ' ')[2]);
                vector<int> lVide;
                std::fill_n(std::back_inserter(result), getNbCase(), lVide);
            }
            else if (line[0] == 'e') {
                result[stoi(split(line, ' ')[1]) - 1].push_back({ stoi(split(line, ' ')[2]) - 1 });
            }
        }
        f.close();
    }
    else {
        std::cout << "File not opened !" << std::endl;
    }

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result.size(); j++) {
            for (int a = 0; a < result[j].size(); a++) {
                if (result[j][a] == i && std::count(result[i].begin(), result[i].end(), j) == 0) {
                    result[i].push_back(j);
                }
            }
        }
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
            if (line[0] == 'r') {
                nbViolation = stoi(split(line, ' ')[2]);
            }
            else if (line[0] != 'c' && line[0] != 'f' && line[0] != 'r') {
                result.push_back((Color)std::stoi(line));
            }
        }
        f.close();
    }

    return result;
}

bool compareGrille(vector<Color> pGrille_A, vector<Color> pGrille_B) {
    return (countNbViolation(pGrille_A) < countNbViolation(pGrille_B));
}

void FileWrite(string output_file_name)
{
    int equipe = 5;
    vector<Color> tab = getTab();
    ofstream output_file(output_file_name, ios::out | ios::trunc);
    if (output_file)
    {
        output_file << "c Algo utilisé : " << getAlgo() << endl;
        output_file << "c Equipe : " << equipe << endl;
        output_file << "f " << getFileName() << endl;
        output_file << "r " << getnCouleurDifferente() << " " << getNbViolation() << endl;
        for (int i = 0; i < getNbCase(); i++)
        {
            output_file << tab[i] << endl;
        }
        output_file.close();
    }
    else
    {
        cerr << "Impossible to write in the file !" << endl;
    }
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
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

// +--------+
// | SETTER |
// +--------+
void setnCouleurDifferente(int pnCouleurDifferente) {
    nCouleurDifferente = pnCouleurDifferente;
}

void setFolder(string pFolder) {
    folder = pFolder;
}

void setFilename(string pFilename) {
    fileName = pFilename;
}

void setreadFromOutput(string pReadFromOutput) {
    readFromOutput = pReadFromOutput;
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
    
    // ------

    // etape 2
    int xc = 999999;
    int x1;
    int x2;
    double temperature = 2500;

    int random_value_1;
    int random_value_2;

    int maxIteration = 70000;
    int nbIteration = 0;

    int bestSolution = 999999;
    vector<Color> bestTab;

    std::cout << "+---------------------+" << std::endl;
    std::cout << "|     ALGO RECUIT     |" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << " TP => " << temperature << std::endl;
    std::cout << " maxIteration => " << maxIteration << std::endl;
    std::cout << "+---------------------+" << std::endl;

    while (nbIteration < maxIteration && xc > 0)
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
            if (x1 < bestSolution) {
                bestSolution = x1;
                bestTab = tab_voisin1;
            }
        }
        else if (x2 > xc && ((double)(x2 - xc) / temperature) < ((double)rand() / RAND_MAX))
        {
            tab = tab_voisin2;
            temperature = temperature * 0.99;
        }
        nbIteration++;
        
        if (nbIteration % 1000 == 0) {
            std::cout << "nbIteration => " << nbIteration << std::endl;
            std::cout << "temperature => " << temperature << std::endl;
            std::cout << "xc => " << xc << std::endl;
            std::cout << "best => " << bestSolution << std::endl;
        }
    }

    if (bestSolution < xc) {
        nbViolation = bestSolution;
        tab = bestTab;
    } else nbViolation = xc;

    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "XC => " << xc << endl;
    std::cout << "TP => " << temperature << endl;
}

vector<Color> algo_recuit(vector<Color> pTab, int &pViolation, int &pnbIteration) {

    int xc = pViolation;
    int x1;
    int x2;
    double temperature = 2500;

    int random_value_1;
    int random_value_2;

    int maxIteration = 70000; // 70000
    int nFlip = 2;

    int bestSolution = pViolation;
    vector<Color> bestTab;

    std::cout << "+---------------------+" << std::endl;
    std::cout << "|     ALGO RECUIT     |" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << " temperature => " << temperature << std::endl;
    std::cout << " nFlip => " << nFlip << std::endl;
    std::cout << " maxIteration => " << maxIteration << std::endl;
    std::cout << "+---------------------+" << std::endl;

    while (pnbIteration < maxIteration && xc > 0)
    {
        xc = 0;
        x1 = 0;
        x2 = 0;

        vector<Color> tab_voisin1 = pTab;
        vector<Color> tab_voisin2 = pTab;
        Color color_tmp;

        // compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            xc += countNbViolation(pTab, iCase, pTab[iCase]);
        }
        xc /= 2;

        // nb violation x1
        for (int iFlip = 0; iFlip < nFlip; iFlip++) {
            random_value_1 = getRandomNumber(getNbCase() - 1);
            random_value_2 = getRandomNumber(getNbCase() - 1);
            color_tmp = tab_voisin1[random_value_1];
            tab_voisin1[random_value_1] = tab_voisin1[random_value_2];
            tab_voisin1[random_value_2] = color_tmp;
        }

        //  compte nb violation sur tab_voisin1
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x1 += countNbViolation(tab_voisin1, iCase, tab_voisin1[iCase]);
        }
        x1 /= 2;

        // nb violation x2
        for (int iFlip = 0; iFlip < nFlip; iFlip++) {
            random_value_1 = getRandomNumber(getNbCase() - 1);
            random_value_2 = getRandomNumber(getNbCase() - 1);
            color_tmp = tab_voisin2[random_value_1];
            tab_voisin2[random_value_1] = tab_voisin2[random_value_2];
            tab_voisin2[random_value_2] = color_tmp;
        }
        
        //  compte nb violation sur tab_voisin2
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x2 += countNbViolation(tab_voisin2, iCase, tab_voisin2[iCase]);
        }
        x2 /= 2;

        if (x1 < xc)
        {
            pTab = tab_voisin1;
            if (x1 < bestSolution) {
                bestSolution = x1;
                bestTab = tab_voisin1;
            }
        }
        else if (x2 > xc && ((double)(x2 - xc) / temperature) < ((double)rand() / RAND_MAX))
        {
            pTab = tab_voisin2;
            temperature = temperature * 0.99;
        }
        pnbIteration++;

        if (pnbIteration % 100 == 0) {
            std::cout << "nbIteration => " << pnbIteration << std::endl;
            std::cout << "temperature => " << temperature << std::endl;
            std::cout << "xc => " << xc << std::endl;
            std::cout << "best => " << bestSolution << std::endl;
        }
    }

    if (bestSolution < xc) {
        pTab = bestTab;
        pViolation = bestSolution;
    }
    return pTab;
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
    int meilleur_sol = 99999;
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

vector<Color> algo_random_walk(vector<Color> pTab, int& pViolation, int& pnbIteration, int pMaxViolation)
{
    
    int maxIteration = 200000; //500000
    int nFlip = 1;
    int meilleur_sol = pViolation;
    int meilleur_sol_courant = 99999;
    int x_courant;

    int random_value_1;
    int random_value_2;

    vector<Color> bestVoisinCourant = pTab;
    vector<Color> voisin;

    std::cout << "+--------------------------+" << std::endl;
    std::cout << "|     ALGO RANDOM WALK     |" << std::endl;
    std::cout << "+--------------------------+" << std::endl;
    std::cout << " maxIteration => " << maxIteration << std::endl;
    std::cout << " nFlip => " << nFlip << std::endl;
    std::cout << "+--------------------------+" << std::endl;

    while (pnbIteration < maxIteration && meilleur_sol > 0)
    {
        x_courant = 0;
        voisin = bestVoisinCourant;

        Color color_tmp;
        for (int iFlip = 0; iFlip < nFlip; iFlip++) {
            random_value_1 = getRandomNumber(getNbCase() - 1);
            random_value_2 = getRandomNumber(getNbCase() - 1);
            color_tmp = voisin[random_value_1];
            voisin[random_value_1] = voisin[random_value_2];
            voisin[random_value_2] = color_tmp;
        }
        
        //  compte violation courante
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            x_courant += countNbViolation(voisin, iCase, voisin[iCase]);
        }
        x_courant /= 2;

        if (x_courant < meilleur_sol) {
            meilleur_sol = x_courant;
            pTab = voisin;

            nbViolation = meilleur_sol;
            tab = pTab;
            FileWrite("output_random_it_" + to_string(pnbIteration) + string("_") + ReplaceAll(ReplaceAll(fileName, ".col", ""), ".", "_") + ".txt");
        }

        if (x_courant < meilleur_sol_courant) {
            meilleur_sol_courant = x_courant;
            bestVoisinCourant = voisin;
        }

        if (pnbIteration % 1000 == 0) {
            if (nFlip > 1) nFlip--;
            std::cout << "nbIteration => " << pnbIteration << std::endl;
            std::cout << "SOLUTION => " << meilleur_sol << std::endl;
            std::cout << "SOLUTION COURANT => " << meilleur_sol_courant << std::endl;
        }

        pnbIteration++;
    }

    pViolation = meilleur_sol;

    return pTab;
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

    int nViolation = 999999;    
    int bestViol = 999999;
    int nbIteration = 0;

    while (nbIteration < 500 && nViolation > 0) {
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
        
        if (nbIteration % 10 == 0) {
            std::cout << "nbIteration => " << nbIteration << std::endl;
            std::cout << "SOLUTION => " << nViolation << std::endl;
        }

        nbIteration++;
    }
    
    nbViolation = nViolation;
    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "SOLUTION_COURANTE => " << nViolation << endl;
}

vector<Color> algo_recherche_tabou(vector<Color> pTab, int& pViolation, int& pnbIteration)
{  
    vector<Color> voisin;
    vector<vector<vector<Color>>> grilleTabou;
    vector<vector<Color>> lVide1;
    vector<Color> lVide2;
    std::fill_n(std::back_inserter(lVide2), getNbCase(), Color::EMPTY);
    for (int i = 0; i < getNbCase(); i++) {
        grilleTabou.push_back(lVide1);
    }

    int nViolation = pViolation;
    int maxIteration = 1000;

    std::cout << "+------------------------------+" << std::endl;
    std::cout << "|     ALGO RECHERCHE TABOU     |" << std::endl;
    std::cout << "+------------------------------+" << std::endl;
    std::cout << " maxIteration => " << maxIteration << std::endl;
    std::cout << "+--------------------------+" << std::endl;

    while (pnbIteration < maxIteration && nViolation > 0) {
        int iBestCase = -1;
        int iBestGrille = -1;
        int bestVal = -1;

        // etape 1
        // trouver la case avec le meilleur score en changeant les couleurs       
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            voisin = pTab;

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

                if (tmpNbViol < pViolation) {
                    grilleTabou[iCase].push_back(voisin);
                    pViolation = tmpNbViol;
                    bestVal = pViolation;
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

                if (tmpNbViol < pViolation) {
                    pViolation = tmpNbViol;
                    bestVal = pViolation;
                    iBestCase = iCase;
                    iBestGrille = grilleTabou[iCase].size() - 1; // le meilleur est forcément la dernière case
                }
            }

        }

        // etape 2
        // get best case
        if (iBestCase > -1 && iBestGrille > -1) {
            voisin = pTab;
            voisin = grilleTabou[iBestCase][iBestGrille];
            int nbViolationTmp = 0;
            for (int iCase = 0; iCase < getNbCase(); iCase++) {
                nbViolationTmp += countNbViolation(voisin, iCase, voisin[iCase]);
            }
            nbViolationTmp /= 2;

            if (nbViolationTmp < nViolation) {
                pTab = voisin;
                nViolation = nbViolationTmp;

                nbViolation = nViolation;
                tab = pTab;
                //FileWrite("./result/running/" + ReplaceAll(fileName, ".col", "") + "/output_it_" + to_string(pnbIteration) + string("_") + ReplaceAll(ReplaceAll(fileName, ".col", ""), ".", "_") + ".txt");
                FileWrite("output_it_" + to_string(pnbIteration) + string("_") + ReplaceAll(ReplaceAll(fileName, ".col", ""), ".", "_") + ".txt");
            }
        }

        if (pnbIteration % 10 == 0) {
            std::cout << "nbIteration => " << pnbIteration << std::endl;
            std::cout << "SOLUTION => " << nViolation << std::endl;
        }

        pnbIteration++;
    }

    return pTab;
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

    int nbParticule = 20;
    int seuil = 120;
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
        std::cout << "iteration => " << nbIteration << " | sol => " << bestSolution << std::endl;
    }

    tab = bestTab;
    nbViolation = bestSolution;
    std::cout << "seuil => " << seuil << endl;
    std::cout << "SOLUTION => " << bestSolution << endl;
}

vector<Color> algo_gww(vector<Color> pTab, int& pViolation, int& pnbIteration) {
    int nbParticule = 20;
    int seuil = pViolation*5;
    int nbRandomWalk = 10;

    // remplissage particule
    vector<vector<Color>> grilleParticule;
    vector<Color> particule = pTab;

    for (int i = 0; i < nbParticule; i++) {
        int random_value_1 = getRandomNumber(getNbCase() - 1);
        int random_value_2 = getRandomNumber(getNbCase() - 1);
        Color color_tmp = particule[random_value_1];
        particule[random_value_1] = particule[random_value_2];
        particule[random_value_2] = color_tmp;
        grilleParticule.push_back(particule);
    }

    int maxIteration = 10000;
    int bestSolution = pViolation;
    vector<Color> bestTab;

    std::cout << "+------------------+" << std::endl;
    std::cout << "|     ALGO GWW     |" << std::endl;
    std::cout << "+------------------+" << std::endl;
    std::cout << " maxIteration => " << maxIteration << std::endl;
    std::cout << " nbParticule => " << nbParticule << std::endl;
    std::cout << " nbRandomWalk => " << nbRandomWalk << std::endl;
    std::cout << " seuil => " << seuil << std::endl;
    std::cout << "+------------------+" << std::endl;

    while (bestSolution > 0 && pnbIteration < maxIteration)
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
                particulesInvalide[iParticulesInvalide] = particulesValide[getRandomNumber(particulesValide.size())];
                grilleParticule.push_back(particulesInvalide[iParticulesInvalide]);
            }
            seuil -= 1;
        }
        else {
            grilleParticule = particulesInvalide;
        }

        //
        pnbIteration++;

        if (pnbIteration % 100 == 0) {
            std::cout << "nbIteration => " << pnbIteration << std::endl;
            std::cout << "SOLUTION => " << bestSolution << std::endl;
        }
    }

    pTab = bestTab;
    pViolation = bestSolution;
    
    return pTab;
}

// ----

vector<vector<Color>> algo_genetique_generate_population(int nPopulation) {
    vector<vector<Color>> result;
    vector<Color> grille;
    while (result.size() < nPopulation)
    {
        grille = tab;
        // genere une grille aleatoire
        int nChange = getRandomNumber(getNbCase() - 1);
        for (int iChange = 0; iChange < nChange; iChange++) {
            grille[getRandomNumber(getNbCase() - 1)] = (Color)(1+getRandomNumber(nCouleurDifferente));
        }
        result.push_back(grille);
    }
    return result;
}

vector<vector<Color>> algo_genetique_selection_uniforme(vector<vector<Color>> pPopulation) {
    int nPopulation = pPopulation.size() / 2;
    
    int nDeleted = 0;
    while (nDeleted < nPopulation)
    {
        pPopulation.erase(pPopulation.begin() + getRandomNumber(pPopulation.size()-1));
        nDeleted++;
    }
    return pPopulation;
}

vector<vector<Color>> algo_genetique_selection_rank(vector<vector<Color>> pPopulation) {
    vector<vector<Color>> result;

    // TRI
    for (int i = 0; i < pPopulation.size(); i++) {
        bool tableau_trie = true;
        for (int j = 0; j < i - 1; j++) {
            if (countNbViolation(pPopulation[j+1]) < countNbViolation(pPopulation[j])) {
                vector<Color> temp = pPopulation[j + 1];
                pPopulation[j + 1] = pPopulation[j];
                pPopulation[j] = temp;
                tableau_trie = false;
            }
        }
        if (tableau_trie) break;
    }

    int nPopulation = pPopulation.size() / 2;
    for (int iSelected = 0; iSelected < nPopulation; iSelected++) {
        result.push_back(pPopulation[iSelected]);
    }

    return result;
}

vector<vector<Color>> algo_genetique_croissement(vector<vector<Color>> pPopulation, int pPivotX, int pPivotY) {
    vector<vector<Color>> populationEnfant;
    
    int nEnfant = pPopulation.size();
    pPivotX = (pPivotX * getNbCase()) / 100;
    pPivotY = (getNbCase()) - pPivotX;

    while (nEnfant > 0) {
        // selectionner 2 parents
        int mere = getRandomNumber(pPopulation.size() - 1);
        int pere = getRandomNumber(pPopulation.size() - 1);
        vector<Color> enfant;

        // GEN MERE
        for (int iGen = 0; iGen < pPivotX; iGen++) {
            enfant.push_back(pPopulation[mere][iGen]);
        }
        for (int iGen = pPivotX; iGen < (pPivotX + pPivotY); iGen++) {
            enfant.push_back(pPopulation[pere][iGen]);
        }
        populationEnfant.push_back(enfant);
        nEnfant--;
        enfant.clear();

        // GEN PERE
        if (nEnfant > 0) {
            for (int iGen = 0; iGen < pPivotX; iGen++) {
                enfant.push_back(pPopulation[pere][iGen]);
            }
            for (int iGen = pPivotX; iGen < (pPivotX + pPivotY); iGen++) {
                enfant.push_back(pPopulation[mere][iGen]);
            }
            populationEnfant.push_back(enfant);
            nEnfant--;
        }
    }

    for (int iEnfant = 0; iEnfant < populationEnfant.size(); iEnfant++) {
        pPopulation.push_back(populationEnfant[iEnfant]);
    }

    return pPopulation;
}

vector<Color> algo_genetique_get_best(vector<vector<Color>> pPopulation) {
    int iBest = -1;
    int bestSolution = 999;
    for (int iElement = 0; iElement < pPopulation.size(); iElement++) {
        int bestSolutionTmp = countNbViolation(pPopulation[iElement]);
        if (bestSolutionTmp < bestSolution) {
            iBest = iElement;
            bestSolution = bestSolutionTmp;
        }
    }
    return pPopulation[iBest];
}

vector<vector<Color>> algo_genetique_mutation(vector<vector<Color>> pPopulation) {
    int nMutants = getRandomNumber(pPopulation.size()/2);
    
    while (nMutants > 0)
    {
        pPopulation[getRandomNumber(pPopulation.size()-1)][getRandomNumber(getNbCase()-1)] = (Color)(1+getRandomNumber(nCouleurDifferente));
        nMutants--;
    }
    return pPopulation;
}

void algo_genetique() {
    // INIT
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

    int nPopulation = 1000;
    int pivotX = 50;
    int pivotY = 100 - pivotX;
    vector<vector<Color>> population = algo_genetique_generate_population(nPopulation);
    
    int nbIteration = 0;
    int maxIteration = 250;
    vector<Color> bestElement;
    int bestSolution = 999999;

    while (bestSolution > 0 && nbIteration < maxIteration)
    {
        // SELECTION
        population = algo_genetique_selection_rank(population);

        // CROISEMENT
        population = algo_genetique_croissement(population, pivotX, pivotY);

        vector<Color> voisin;

        // get best avant mutation
        voisin = algo_genetique_get_best(population);
        int nViolation = countNbViolation(voisin);
        if (nViolation < bestSolution) {
            bestSolution = nViolation;
            bestElement = voisin;
        }

        // MUTATION
        population = algo_genetique_mutation(population);

        // get best apres mutation
        voisin = algo_genetique_get_best(population);
        nViolation = countNbViolation(voisin);
        if (nViolation < bestSolution) {
            bestSolution = nViolation;
            bestElement = voisin;
        }

        nbIteration++;
        if (nbIteration % 50 == 0) {
            std::cout << "nbIteration => " << nbIteration << endl;
            std::cout << "SOLUTION => " << bestSolution << endl;
        }
    }

    nbViolation = bestSolution;
    tab = bestElement;

    std::cout << "nbIteration => " << nbIteration << endl;
    std::cout << "SOLUTION => " << nbViolation << endl;
    
}

vector<Color> algo_genetique(vector<Color> pTab, int& pViolation, int& pnbIteration)
{
    int nPopulation = 1000;
    int pivotX = 50;
    int pivotY = 100 - pivotX;
    vector<vector<Color>> population = algo_genetique_generate_population(nPopulation);

    int maxIteration = 500;
    vector<Color> bestElement;
    int bestSolution = pViolation;

    std::cout << "+------------------------+" << std::endl;
    std::cout << "|     ALGO GENETIQUE     |" << std::endl;
    std::cout << "+------------------------+" << std::endl;
    std::cout << " maxIteration => " << maxIteration << std::endl;
    std::cout << " nPopulation => " << nPopulation << std::endl;
    std::cout << " pivotX => " << pivotX << std::endl;
    std::cout << " pivotY => " << pivotY << std::endl;
    std::cout << "+------------------------+" << std::endl;

    while (bestSolution > 0 && pnbIteration < maxIteration)
    {
        // SELECTION
        population = algo_genetique_selection_rank(population);

        // CROISEMENT
        population = algo_genetique_croissement(population, pivotX, pivotY);

        vector<Color> voisin;

        // get best avant mutation
        voisin = algo_genetique_get_best(population);
        int nViolation = countNbViolation(voisin);
        if (nViolation < bestSolution) {
            bestSolution = nViolation;
            bestElement = voisin;
        }

        // MUTATION
        population = algo_genetique_mutation(population);

        // get best apres mutation
        voisin = algo_genetique_get_best(population);
        nViolation = countNbViolation(voisin);
        if (nViolation < bestSolution) {
            bestSolution = nViolation;
            bestElement = voisin;
        }

        pnbIteration++;
        if (pnbIteration % 10 == 0) {
            std::cout << "nbIteration => " << pnbIteration << endl;
            std::cout << "SOLUTION COURANTE => " << nViolation << endl;
            std::cout << "BEST SOLUTION => " << bestSolution << endl;
        }
    }

    if (bestSolution < pViolation) {
        pViolation = bestSolution;
        pTab = bestElement;
    }

    return pTab;
}

// algo_hybride
void algo_hybride() {
    algo = "algo_hybride";

    int solution;

    if (readFromOutput != "") {
        tab = readOutput(readFromOutput.c_str());
        solution = nbViolation;
    }
    else {
        solution = 9999999;
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

        int iSwap;
        for (int iCase = 0; iCase < getNbCase(); iCase++) {
            iSwap = getRandomNumber(getNbCase() - 1);
            Color tempColor = tab[iCase];
            tab[iCase] = tab[iSwap];
            tab[iSwap] = tempColor;
        }
    }

    int nbIterationGlobal = 0;
    int nbIteration = 0;

 
    tab = algo_random_walk(tab, solution, nbIteration, -1);
    nbIterationGlobal += nbIteration;
    nbIteration = 0;

    // fin avec tabou
    tab = algo_recherche_tabou(tab, solution, nbIteration);
    nbIterationGlobal += nbIteration;
    nbIteration = 0;

    std::cout << "nbIterationGlobal => " << nbIterationGlobal << endl;
    std::cout << "SOLUTION => " << solution << endl;

    nbViolation = solution;

    FileWrite("output_" + ReplaceAll(ReplaceAll(fileName, ".col", ""), ".", "_") + ".txt");
    
}

void algo_hybride_partie_2() {
    // int from output
    tab = readOutput("output.txt");    

    int solution = 99999;
    int nbIterationGlobal = 0;
    int nbIteration = 0;

    // algo_recuit
    tab = algo_recuit(tab, solution, nbIteration);
    nbIterationGlobal += nbIteration;
    nbIteration = 0;

    // fin avec tabou
    tab = algo_recherche_tabou(tab, solution, nbIteration);
    nbIterationGlobal += nbIteration;
    nbIteration = 0;

    std::cout << "nbIterationGlobal => " << nbIterationGlobal << endl;
    std::cout << "SOLUTION => " << solution << endl;

    nbViolation = solution;

    FileWrite("output.txt");
}
