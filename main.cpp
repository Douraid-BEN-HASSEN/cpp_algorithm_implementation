#include <fstream>
#include <iostream>

#include <stdlib.h>
#include <stdio.h>

using namespace std;

int tile;
int contraints;

int equipe = 5;
string input_path = "Graphes/";
string input_file_name = "queen5_5.col";
string output_file_name = "output.txt";

int tab_output[5][5];

int Violation();
void FileRead(string input_file);
void FileWrite(string output_file);
void CompleteTabInput();
void CompleteTabOutput();

int main()
{
    FileRead(operator+(input_path, input_file_name));
    // CompleteTabInput();
    CompleteTabOutput();
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
            if (ligne[0] == 'c')
            {
                cout << ligne << endl;
            }
            else if (ligne[0] == 'p')
            {

            }
            else if (ligne[0] == 'e')
            {

            }
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
        output_file << "f " << input_file_name << endl;
        output_file << "r 5 " << Violation() << endl;
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

int Violation()
{
    int violation = 0;
    return violation;
}

void CompleteTabInput()

void CompleteTabOutput()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            tab_output[i][j] = rand()%5;
        }
    }
}