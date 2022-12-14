#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>
#include <ctime>
#include <math.h>

using namespace std;

enum Color {
	EMPTY = 0,
	ROUGE = 1,
	JAUNE = 2,
	VERT = 3,
	BLEU = 4,
	VIOLET = 5,
	ORANGE = 6,
	NOIR = 7,
	BLANC = 8,
	ROSE = 9
};

void init();

// +-------+
// | UTILS |
// +-------+
vector<vector<int>> readCol(const char*);
vector<string> split(const string&, char);
int countNbViolation(int, Color);
int countNbViolation(vector<Color>, int, Color);
int countNbViolation(vector<Color>);
int getRandomNumber(int);
vector<Color> readOutput(const char*);
bool compareGrille(vector<Color>, vector<Color>);
void FileWrite(string);
std::string ReplaceAll(std::string, const std::string&, const std::string&);

// +--------+
// | GETTER |
// +--------+
int getNbCase();
int getNbViolation();
string getAlgo();
vector<Color> getTab();
int getnCouleurDifferente();
string getFileName();

// +--------+
// | SETTER |
// +--------+
void setnCouleurDifferente(int);
void setFolder(string);
void setFilename(string);
void setreadFromOutput(string);

// +------+
// | ALGO |
// +------+
void algo_violation();
void algo_violation(vector<Color>);

void algo_recuit();

void algo_descente();
void algo_gsat();
void algo_random_walk();

void algo_recherche_tabou();

vector<Color> algo_gww_random_walk(vector<Color>);
void algo_gww();

vector<vector<Color>> algo_genetique_generate_population(int);
vector<vector<Color>> algo_genetique_selection_uniforme(vector<vector<Color>>);
vector<vector<Color>> algo_genetique_selection_rank(vector<vector<Color>>);
vector<vector<Color>> algo_genetique_croissement(vector<vector<Color>>, int, int);
vector<Color> algo_genetique_get_best(vector<vector<Color>>);
vector<vector<Color>> algo_genetique_mutation(vector<vector<Color>>);

void algo_genetique();

vector<Color> algo_recuit(vector<Color>, int&, int&);
vector<Color> algo_random_walk(vector<Color>, int&, int&, int);
vector<Color> algo_recherche_tabou(vector<Color>, int&, int&);
vector<Color> algo_gww(vector<Color> pTab, int& pViolation, int& pnbIteration);
vector<Color> algo_genetique(vector<Color>, int&, int&);

void algo_hybride();
void algo_hybride_partie_2();
