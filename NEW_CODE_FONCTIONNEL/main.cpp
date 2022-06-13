// +------+
// | MAIN |
// +------+
#include "utils.h"

int equipe = 5;
string input_path = "Graphes/";
string output_file_name = "output.txt";

void FileWrite(string output_file);
bool checkFile();

int main()
{
    init();

    // algo_recuit();

    // algo_descente();
    // algo_gsat();
    // algo_random_walk();

    // algo_recherche_tabou();    

    FileWrite(output_file_name);
}

void FileWrite(string output_file_name)
{
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

bool checkFile() {
    int nbViolationTmp = 0;
    vector<Color> tab = readOutput("output.txt");
    for (int iCase = 0; iCase < getNbCase(); iCase++) {
        nbViolationTmp += countNbViolation(tab, iCase, tab[iCase]);
    }
    nbViolationTmp /= 2;
    return nbViolationTmp == nbViolationTmp;
}
