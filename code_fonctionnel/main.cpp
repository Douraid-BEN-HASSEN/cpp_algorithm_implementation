// +------+
// | MAIN |
// +------+
#include "utils.h"

int equipe = 5;
string input_path = "Graphes/";
string input_file_name = "queen5_5.col";
string output_file_name = "output.txt";

void FileWrite(string output_file);

int main()
{
    init();

    algo_violation();

    FileWrite(output_file_name);

}

void FileWrite(string output_file_name)
{
    vector<Color> tab = getTab();

    ofstream output_file(output_file_name, ios::out | ios::trunc);
    if (output_file)
    {
        output_file << "c Algo utilisé : " << endl;
        output_file << "c Equipe : " << equipe << endl;
        output_file << "f " << input_file_name << endl;
        output_file << "r 5 " << getNbViolation() << endl;
        for (int i = 0; i < 25; i++)
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
