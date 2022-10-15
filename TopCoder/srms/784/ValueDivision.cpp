#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class ValueDivision {
public:
  vector<int> getArray(vector<int> a) {
    set<int> b(a.begin(), a.end());

    reverse(a.begin(), a.end());

    while (!b.empty()) {
      int x = *b.rbegin();
      b.erase(x);
      if (x == 1) continue;
      bool found = false;
      for (int &y : a) {
        if (y == x) {
          if (!found) {
            found = true;
          } else {
            y--;
            b.insert(y);
          }
        }
      }
    }

    reverse(a.begin(), a.end());

    return a;
  }
};










