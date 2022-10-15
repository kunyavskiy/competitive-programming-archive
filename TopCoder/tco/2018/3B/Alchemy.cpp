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

#define YES "Possible"
#define NO "Impossible"

class Alchemy {
  vector<int> get_sums(int k, vector<int> c, int shift) {
    vector<int> vals;
    vals.push_back(shift);
    int m = *max_element(c.begin(), c.end());
    for (int i = 0; i < k; i++) {
      vector<bool> bnvals((i + 1) * m + 1 + shift);
      vector<int> nvals;
      for (int j : vals) {
        for (int v : c) {
          if (!bnvals[j + v]) {
            bnvals[j + v] = true;
            nvals.push_back(j + v);
          }
        }
      }
      vals = nvals;
    }
    return vals;
  }
public:
  string leadToGold(vector<int> a, vector<int> b, ll c) {
    vector<int> v;
    for (int i = 0; i < (int)a.size(); i++) {
      if (a[i] == 0) {
        v.push_back(b[i]);
      }
    }
    if (v.empty()) {
      return NO;
    }

    vector<int> changes;
    for (int i = 0; i < (int)a.size(); i++) {
      if (a[i] != 0) {
        vector<int> x = get_sums(a[i] - 1, v, b[i]);
        changes.insert(changes.end(), x.begin(), x.end());
      }
    }
    sort(changes.begin(), changes.end());
    changes.erase(unique(changes.begin(), changes.end()), changes.end());

    int g = 0;
    for (int i : changes) {
      g = __gcd(g, i);
    }

    for (int &i : changes) {
      i /= g;
    }

    vector<bool> p = get_prefix(changes);

    for (int x : v) {
      ll t = (c - x);
      if (t % g != 0 || t < 0) continue;
      t /= g;
      if (t > (int)p.size() || p[t]) return YES;
    }
    return NO;
  }

  vector<bool> get_prefix(vector<int> vals) {
    int m = vals[0];
    vector<bool> ok;
    ok.push_back(true);
    int last = 1;
    for (int i = 1;last < m; i++) {
      int done = false;
      for (int x : vals) {
        if (x <= i && ok[i - x]) {
          done = true;
          break;
        }
      }
      if (done) {
        ok.push_back(true);
        last++;
      } else {
        ok.push_back(false);
        last = 0;
      }
    }
    return ok;
  }
};










