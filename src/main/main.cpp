#include <iostream>
#include <vector>

#include "common/def.h"

using namespace std;

int main() {
  cout << "Hello World" << endl;

  vector<int> a = {1, 2, 3};

  for (auto i : a) {
    cout << i << endl;
  }

  common::Elem elem;

  elem.size = 2;

  cout << elem.size << endl;
}