#include <iostream>
#include "utils.h"

using namespace std;

vector<vector<int>> positionInterdite;
vector<Color> tab;

int nbViolation = 0;

void init();
void algo_Violation();
int getNbViolation(int, Color);
int getNbViolation();