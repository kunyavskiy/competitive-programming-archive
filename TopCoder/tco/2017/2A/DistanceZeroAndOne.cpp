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


class DistanceZeroAndOne {
  vector<string> g;

  vector<int> dist(int v) {
    queue<int> q;
    vector<int> res(g.size(), -1);
    q.push(v);
    res[v] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = 0; i < (int)g.size(); i++) {
        if (g[u][i] == 'Y' && res[i] == -1) {
          res[i] = res[u] + 1;
          q.push(i);
        }
      }
    }
    return res;
  }

public:
  vector<string> construct(vector<int> a, vector<int> b) {
    int n = (int) a.size();
    g.resize(n, string(n, 'Y'));
    for (int i = 0; i < n; i++) {
      g[i][i] = 'N';
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (abs(a[i] - a[j]) > 1 || abs(b[i] - b[j]) > 1) {
          g[i][j] = 'N';
        }
      }
    }
    if (dist(0) != a || dist(1) != b) {
      return vector<string>();
    }
    return g;
  }
};










