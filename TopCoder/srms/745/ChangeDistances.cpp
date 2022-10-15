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


class ChangeDistances {
public:
  vector <string> findGraph(vector <string> v) {
    for (int i = 0; i < (int)v.size(); i++) {
      for (int j = 0; j < (int)v.size(); j++) {
        if (i != j) {
          v[i][j] ^= 1;
        }
      }
    }
    return v;
  }
};










