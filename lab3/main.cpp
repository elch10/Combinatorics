#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

int main()
{
  string filename = "input.txt";
  ifstream fin(filename);
  if (!fin) {
    cout << "Bad parameters - Cannot find file - " << filename << endl;
    return 0;
  }

  OrientedMultiGraph gr;
  fin >> gr;
  cout << gr;
  return 0;
}