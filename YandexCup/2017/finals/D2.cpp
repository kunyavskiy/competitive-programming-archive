#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


int n;

map<pair<vector<int>, int>, bool> cache;

bool check(vector<int> v, int a) {
  for (int i = 0; i < (int) v.size(); i++) {
    if (!v[i]) continue;
    int bit = v[i] & ~(v[i] - 1);
    if (a & bit) a ^= v[i];
    for (int j = i + 1; j < (int) v.size(); j++) {
      if (v[j] & bit) v[j] ^= v[i];
    }
  }
  return !a;
}

bool solve(vector<int> v, int a, int move) {
  if (!a) return true;
  if (!check(v, a)) return false;


  auto it = cache.find({v, 2 * a + move});
  if (it != cache.end()) {
    return it->second;
  }

  bool &res = cache[{v, 2 * a + move}];

  if (move == 0) {
    vector<int> nv(v.begin() + 1, v.end());
    res = solve(nv, a, 1);
    for (int i = 1; res && i < (int) v.size(); i++) {
      nv[i - 1] = v[i - 1];
      res &= solve(nv, a, 1);
    }
    return res;
  }

  res = false;

  for (int i = 0; !res && i < (int) v.size(); i++) {
    if (v[i] == v[i - 1]) continue;
    int bit = v[i] & ~(v[i] - 1);
    vector<int> nv;
    for (int x : v) {
      if (x & bit) {
        if (x ^ v[i]) {
          nv.push_back(x ^ v[i]);
        }
      } else {
        nv.push_back(x);
      }
    }
    sort(nv.begin(), nv.end());
    res |= solve(nv, ((a & bit) ? (a ^ v[i]) : a), 0);
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  scanf("%d", &n);

  vector<int> v(n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  vector<int> p;
  for (int i = 0; i < (1 << n); i++) {
    int a = 0;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        a ^= v[j];
      }
    }
    if (a) {
      p.push_back(a);
    }
  }

  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  vector<int> ans;

  sort(v.begin(), v.end());

  for (int x : p) {
    if (solve(v, x, 0)) {
      ans.push_back(x);
    }
  }

  printf("%d\n", (int) ans.size());
  for (int x : ans) {
    printf("%d ", x);
  }
  printf("\n");

  return 0;
}
