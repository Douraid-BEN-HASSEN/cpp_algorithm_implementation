void algo() {
    // pour chaque couleur
    for (int iColor = 1; iColor < 6; iColor++) {
        /*
        * placer la reine 1 sur une case vide
        */
        for (int iCaseMere = 0; iCaseMere < getNbCase(); iCaseMere++) {
            if (tab[iCaseMere] == Color::EMPTY) {
                tab[iCaseMere] = (Color)iColor;

                vector<Color> tabCP = tab;
                vector<int> localPositionInterdite;
                for (int iCaseInterdite = 0; iCaseInterdite < positionInterdite[iCaseMere].size(); iCaseInterdite++) {
                    localPositionInterdite.push_back(positionInterdite[iCaseMere][iCaseInterdite]);
                }

                // verifier pour toutes les autres case si nb placement possible >= X -1
                int meilleursScore = -1;
                int indexChoisi = -1;
                for (int iCaseFille = 0; iCaseFille < getNbCase(); iCaseFille++) {
                    int meilleurScoreTmp = nbPlacementPossible((Color)iColor, tab, localPositionInterdite);
                    if (tab[iCaseFille] == Color::EMPTY) {
                        if (meilleurScoreTmp > meilleursScore) {
                            meilleursScore = meilleurScoreTmp;
                            indexChoisi = iCaseFille;
                        }
                    }
                    
                    tab = tabCP; // reset tab
                }
                int a = 2; // pas de solution

            }
        }
    }
}

int nbPlacementPossible(Color pColor, vector<Color> &pTab, vector<int> pPositionInterdite) {
    for (int iCase = 0; iCase < pTab.size(); iCase++) {
        if (pTab[iCase] == Color::EMPTY) {
            if (!count(pPositionInterdite.begin(), pPositionInterdite.end(), iCase)) {
                pTab[iCase] = pColor;
                // ajout des nouvelles pos interdites
                for (int iCaseInterdite = 0; iCaseInterdite < positionInterdite[iCase].size(); iCaseInterdite++) {
                    if (!count(positionInterdite[iCase].begin(), positionInterdite[iCase].end(), iCase)) {
                        pPositionInterdite.push_back(iCase);
                    }
                }
                return 1 + nbPlacementPossible(pColor, pTab, pPositionInterdite);
            }
        }
    }
    return 0;
}
