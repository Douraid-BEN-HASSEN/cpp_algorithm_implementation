// +------+
// | MAIN |
// +------+
#include "utils.h"

bool checkFile();

int main()
{
    init();

    // algo_recuit(); // OK
    // algo_descente(); // OK
    // algo_gsat();
    // algo_random_walk(); OK

    // algo_recherche_tabou(); // OK
    // algo_gww(); // OK
    // algo_genetique();

    algo_hybride();
    //algo_hybride_partie_2();

    

    // checkFile();
}

bool checkFile() {
    int nbViolationTmp = 0;
    vector<Color> tab = readOutput("output.txt");
    for (int iCase = 0; iCase < getNbCase(); iCase++) {
        nbViolationTmp += countNbViolation(tab, iCase, tab[iCase]);
    }
    nbViolationTmp /= 2;
    return nbViolationTmp == nbViolationTmp;
}
