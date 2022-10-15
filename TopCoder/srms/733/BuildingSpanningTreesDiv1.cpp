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

const int MOD = 987654323;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}


class BuildingSpanningTreesDiv1 {

  vector<int> p;
  vector<int> sz;

  int get(int a) {
    if (p[a] == a) return a;
    return p[a] = get(p[a]);
  }

public:
  int getNumberOfSpanningTrees(int n, vector<int> x, vector<int> y) {
    p = vector<int>(n);
    sz = vector<int>(n);
    for (int i = 0; i < n; i++) {
      p[i] = i;
      sz[i] = 1;
    }
    
    for (int i = 0; i < (int)x.size(); i++) {
      x[i] = get(x[i]);
      y[i] = get(y[i]);
      if (x[i] == y[i]) {
        return 0;
      }
      p[x[i]] = y[i];
      sz[y[i]] += sz[x[i]];
    }
    
    int ans = 1;

    int c = 0;

    for (int i = 0; i < n; i++) {
      if (p[i] == i) {
        ans = mul(ans, sz[i]);
        c++;
      }
    }

    if (c == 1) return 1;
    for (int i = 0; i < c - 2; i++) {
      ans = mul(ans, n);
    }
    return ans;
  }
};










