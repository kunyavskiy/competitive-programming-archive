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


class SquareCutout {
public:
  int verify(vector<string> v) {
    int minx = v.size(), maxx = -1;
    int miny = v.size(), maxy = -1;
    for (int i = 0; i < (int)v.size(); i++) {
      for (int j = 0; j < (int)v[i].size(); j++){
        if (v[i][j] == '#') {
          minx = min(minx, i);
          maxx = max(maxx, i);
          miny = min(miny, j);
          maxy = max(maxy, j);
        }
      }
    }

    if (minx > maxx) {
      return 1;
    }

    for (int i = minx; i <= maxx; i++) {
      for (int j = miny; j < maxy; j++) {
        if (v[i][j] == '.') {
          return 0;
        }
      }
    }

    int fromx, tox, fromy, toy;
    fromx = tox = maxx - minx + 1;
    fromy = toy = maxy - miny + 1;

    if (minx == 0 || maxx == (int)v.size() - 1) {
      tox = 1e9;
    }
    if (miny == 0 || maxy == (int)v[0].size() - 1) {
      toy = 1e9;
    }

    if (max(fromx, fromy) <= min(tox, toy)) {
      return max(fromx, fromy);
    }

    return 0;
  }
};










