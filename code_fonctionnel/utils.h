#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <array>

using namespace std;

enum Color {
	EMPTY = 0,
	RED = 1,
	JAUNE = 2,
	VERT = 3,
	BLEU = 4,
	VIOLET = 5
};

void init();

// +-------+
// | UTILS |
// +-------+
vector<vector<int>> readCol(const char*);
vector<string> split(const string&, char);
int countNbViolation(int, Color);
int countNbViolation(vector<Color>, int, Color);
int getRandomNumber(int);

// +--------+
// | GETTER |
// +--------+
int getNbCase();
int getNbViolation();
vector<Color> getTab();

// +------+
// | ALGO |
// +------+
void algo_violation();
void algo_violation(vector<Color>);
void algo_recuit();


