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

const ll INF = (ll)5e18;
const int INT_INF = (int)2e9;

class AtLeastOnPrefix {
  map<int, ll> s;
  multiset<ll> vals;
public:

  AtLeastOnPrefix() {
    s[-1] = INT_INF + 1;
    s[0] = 0;
    vals.insert(0);
  }

  void addAtLeast(int y, int val) {
    auto it = s.upper_bound(y);
    --it;
    ll yval = it->second;
    if (yval > val) {
      return;
    }
    while (true) {
      vals.erase(vals.find(it->first + it->second));
      auto nit = it;
      --nit;
      if (nit->second > val) {
        it->second = val;
        vals.insert(it->first + it->second);
        break;
      }
      s.erase(it);
      it = nit;
    }
    it = s.find(y);
    if (it != s.end()) {
      vals.erase(vals.find(it->first + it->second));
    }
    s[y] = yval;
    vals.insert(y + yval);
  }

  ll get() {
    return *vals.begin();
  }
};

struct point {
  int x, y, c;
};


class ColorfulEnclosure {

  vector<int> used;
  int used_ptr = 0;

  ll solve2(const vector<point>& v, int l, int r) {
    used_ptr++;
    int have_cols = 0;
    for (int j = l; j < r; j++) {
      if (used[v[j].c] != used_ptr) {
        have_cols++;
        used[v[j].c] = used_ptr;
      }
    }
    if (have_cols < (int) used.size()) return INF;
    int m = (l + r) / 2;
    ll ans1 = solve2(v, l, m);
    ll ans2 = solve2(v, m, r);

    ll ans = min(ans1, ans2);

    AtLeastOnPrefix s;
    vector<multiset<int>> lf(used.size());
    vector<multiset<int>> rg(used.size());

    int midx = v[m].x;

    vector<point> all = vector<point>(v.begin() + l, v.begin() + r);
    sort(all.begin(), all.end(), [](const point& a, const point& b) { return a.y > b.y;});

    for (const point& p : all) {
      if (p.x < midx) {
        lf[p.c].insert(midx - p.x);
      } else {
        rg[p.c].insert(p.x - midx);
      }
    }

    for (int i = 0; i < (int)used.size(); i++) {
      int best_lf = lf[i].empty() ? INT_INF : *lf[i].begin();
      int best_rg = rg[i].empty() ? INT_INF : *rg[i].begin();
      s.addAtLeast(best_rg, best_lf);
    }


    for (const point& p : all) {
      ll val = s.get();
      if (val >= INT_INF) {
        return ans;
      }
      ans = min(ans, p.y * 1LL * val);
      if (p.x < midx) {
        lf[p.c].erase(lf[p.c].find(midx - p.x));
      } else {
        rg[p.c].erase(rg[p.c].find(p.x - midx));
      }
      int best_lf = lf[p.c].empty() ? INT_INF : *lf[p.c].begin();
      int best_rg = rg[p.c].empty() ? INT_INF : *rg[p.c].begin();
      s.addAtLeast(best_rg, best_lf);
    }


    return ans;
  }

  ll solve(vector<point> v) {
    sort(v.begin(), v.end(), [](const point& a, const point& b) { return a.x < b.x;});
    return solve2(v, 0, (int)v.size());
  }

public:
  ll minArea(int k, vector<int> x, vector<int> y, vector<int> c) {
    if (k == 1) {
      return 0;
    }
    used = vector<int>(k);
    vector<point> v;
    int n = (int)x.size();
    for (int i = 0; i < n; i++) {
      v.push_back({x[i], y[i], c[i]});
    }
    sort(v.begin(), v.end(), [](const point& a, const point& b) { return a.y < b.y;});
    ll ans = INF;
    for (int i = 0; i < n; i++) {
      for (int j = n - 1; j >= i; j--) {
        v[j].y -= v[i].y;
        assert(v[j].y >= 0);
      }
      ans = min(ans, solve(vector<point>(v.begin() + i, v.end())));
    }
    return ans;
  }
};










