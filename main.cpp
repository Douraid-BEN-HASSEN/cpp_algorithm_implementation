#include <fstream>
#include <iostream>

using namespace std;

int equipe = 5;
string input_path = "Graphes/";
string input_file_name = "queen5_5.col";
string output_file_name = "output.txt";

void FileRead(string input_file);
void FileWrite(string output_file);

int main()
{
    FileRead(operator+(input_path, input_file_name));
    FileWrite(output_file_name);
}

void FileRead(string input_file_name)
{
    ifstream input_file(input_file_name, ios::in);
    if (input_file)
    {
        string ligne;
        while (getline(input_file, ligne))
        {
            cout << ligne << endl;
        }
        input_file.close();
    }
    else
    {
        cerr << "Impossible to open the file !" << endl;
    }
}

void FileWrite(string output_file_name)
{
    ofstream output_file(output_file_name, ios::out | ios::trunc);
    if (output_file)
    {
        output_file << "c Algo utilisé : " << endl;
        output_file << "c Equipe : " << equipe << endl;
        output_file << "f Fichier : " << input_file_name << endl;
        output_file << "r 5 0" << endl;
        for (int i = 0; i < 25; i++)
        {
            output_file << rand()%5 << endl;
        }
        output_file.close();
    }
    else
    {
        cerr << "Impossible to write in the file !" << endl;
    }
}