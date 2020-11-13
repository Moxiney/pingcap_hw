#include <iostream>
#include <vector>

using namespace std;

int main() {
  cout << "Hello World" << endl;

  vector<int> a = {1, 2, 3};

  for (auto i : a) {
    cout << i << endl;
  }
}