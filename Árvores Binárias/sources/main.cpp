#include "../includes/Tree.h"
#include <iostream>
#include <string>
int main() {
  std::string line;
  getline(std::cin, line);
  Tree bt(line);
  bt.bshow();
  // std::cout << bt.height() << " " << bt.size() << "\n";
  return 0;
}