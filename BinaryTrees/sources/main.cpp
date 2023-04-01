#include "../includes/Tree.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
  string line;
  getline(cin, line);
  Tree bt(line);
  cout << bt.height() << " " << bt.size() << endl;
  return 0;
}