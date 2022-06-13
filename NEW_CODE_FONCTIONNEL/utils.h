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

// +--------+
// | GETTER |
// +--------+
int getNbCase();
int getNbViolation();
string getAlgo();
vector<Color> getTab();
int getnCouleurDifferente();
string getFileName();

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
