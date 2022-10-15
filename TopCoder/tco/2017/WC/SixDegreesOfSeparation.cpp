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


class SixDegreesOfSeparation {
  vector<vector<int>> g;
  vector<int> h;

  void dfs(int v, int curh) {
    if (h[v] != -1) return;
    h[v] = curh;
    for (int u : g[v]) {
      dfs(u, curh + 1);
    }
  }
public:
  vector<int> getAdditionalEdges(int n, vector<int> a, vector<int> b) {
    g = vector<vector<int>>(n);
    h = vector<int>(n, -1);
    set<pair<int, int>> s;
    for (int i = 0; i < (int)a.size(); i++) {
      if (a[i] > b[i]) swap(a[i], b[i]);
      g[a[i]].push_back(b[i]);
      g[b[i]].push_back(a[i]);
      s.insert({a[i], b[i]});
    }
    dfs(0, 0);
    vector<int> cnt(3);
    for (int i = 0; i < n; i++) {
      cnt[h[i] % 3]++;
    }
    vector<int> ans;
    int t = min_element(cnt.begin(), cnt.end()) - cnt.begin();
    for (int i = 1; i < n; i++) {
      if (h[i] % 3 == t) {
        if (s.find({0, i}) == s.end()) {
          ans.push_back(0);
          ans.push_back(i);
        }
      }
    }
    return ans;
  }
};










