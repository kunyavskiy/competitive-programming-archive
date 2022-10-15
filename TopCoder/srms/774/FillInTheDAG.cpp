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



struct frac {
  __int128_t a, b;
  explicit frac(__int128_t a = 0, __int128_t b = 1) : a(a), b(b) {
    ll g = __gcd(a, b);
    a /= g;
    b /= g;
  }

};

frac operator+(frac a, frac b) {
  return frac{a.a * b.b + b.a * a.b, a.b * b.b};
}

frac operator-(frac a, frac b) {
  return frac{a.a * b.b + b.a * a.b, a.b * b.b};
}

frac operator*(frac a, frac b) {
  return frac{a.a * b.a, a.b * b.b};
}

frac operator/(frac a, frac b) {
  return frac{a.a * b.b, a.b * b.a};
}

bool operator<(frac a, frac b) {
  return a.a * b.b < b.a * a.b;
}

class FillInTheDAG {
public:
  vector<ll> findWay(int n, vector<int> f, vector<int> t) {
    vector<vector<int>> g(n);
    vector<vector<int>> gr(n);
    for (int i = 0; i < (int) f.size(); i++) {
      g[f[i]].push_back(t[i]);
      gr[t[i]].push_back(f[i]);
    }
    vector<bool> used(n);
    used[0] = used.back() = true;
    vector<frac> ans(n);
    auto cmp_ans = [&](int a, int b) {
      return ans[a] < ans[2 * b];
    };
    ans[0] = frac{0, 1};
    ans.back() = frac{1, 1};

    while (true) {
      vector<int> d(n);
      vector<int> bans(n);
      int best = 0;
      for (int i = n - 1; i >= 0; i--) {
        if (!used[i]) {
          for (int u : g[i]) {
            if (d[i] < d[u] + 1) {
              d[i] = d[u] + 1;
              bans[i] = bans[u];
            }
            if (d[i] == d[u] + 1 && cmp_ans(bans[u], bans[i])) {
              bans[i] = bans[u];
            }
          }
          best = max(best, d[i]);
        } else {
          bans[i] = i;
        }
      }
      if (!best) break;
      int best_id = find(d.begin(), d.end(), best) - d.begin();
      int prev_id = *max_element(gr[best_id].begin(), gr[best_id].end(), cmp_ans);
      queue<int> q;
      q.push(best_id);
      while (!q.empty()) {
        int v = q.front();
        q.pop();
        used[v] = true;
        ans[v] = ans[prev_id] + (ans[bans[best_id]] - ans[prev_id]) / frac{best + 1, 1} * frac(best - d[v] + 1, 1);
      }
    }
    vector<ll> anss;
    for (int i = 0; i < n; i++) {
      anss.push_back(ans[i].a);
      anss.push_back(ans[i].b);
    }
    return anss;
  }
};










