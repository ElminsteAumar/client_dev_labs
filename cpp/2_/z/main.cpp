#include <iostream>
#include <sstream>
#include <stdexcept>
#include "set.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cout << "Usage: [app name] \"[sequence of ints]\" \"[sequence of ints]\"" << endl;
    return 0;
  }

  Set<int> set1, set2;
  istringstream iss1(argv[1]), iss2(argv[2]);
  cout << boolalpha;

  cout << "Insertion:" << endl;
  while (!iss1.eof() || !iss2.eof()) {
    if (!iss1.eof()) {
      int a;
      if (!(iss1 >> a)) goto failure;
      set1.insert(a);
      cout << "a: " << a << endl;
      cout << "Contains  (Set 1): " << set1.contains(a) << endl;
    }

    if (!iss2.eof()) {
      int b;
      if (!(iss2 >> b)) goto failure;
      set2.insert(b);
      cout << "b: " << b << endl;
      cout << "Contains  (Set 2): " << set2.contains(b) << endl;
    }

    cout << "Set 1:                  " << set1        << endl;
    cout << "Set 2:                  " << set2        << endl;
    cout << "Intersection:           " << set1 * set2 << endl;
    cout << "Union:                  " << set1 + set2 << endl;
    cout << "Difference (1st - 2nd): " << set1 - set2 << endl;
    cout << "Difference (2nd - 1st): " << set2 - set1 << endl;
    cout << endl;
  }

  iss1.seekg(0);
  iss2.seekg(0);

  cout << "Removal:" << endl;
  while (!iss1.eof() || !iss2.eof()) {
    if (!iss1.eof()) {
      int a;
      if (!(iss1 >> a)) goto failure;
      set1.remove(a);
      cout << "a: " << a << endl;
      cout << "Contains  (Set 1): " << set1.contains(a) << endl;
    }

    if (!iss2.eof()) {
      int b;
      if (!(iss2 >> b)) goto failure;
      set2.remove(b);
      cout << "b: " << b << endl;
      cout << "Contains  (Set 2): " << set2.contains(b) << endl;
    }

    cout << "Set 1: " << set1 << endl;
    cout << "Set 2: " << set2 << endl;
    cout << endl;
  }

  return 0;

failure:
  throw invalid_argument("Either one or both of CLI arguments are invalid");
}
