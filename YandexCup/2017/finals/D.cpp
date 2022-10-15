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


vector<int> vand(const vector<int> &a, const vector<int> &b) {
  vector<int> c(a.size());
  c.erase(set_intersection(a.begin(), a.end(), b.begin(), b.end(), c.begin()), c.end());
  return c;
}

vector<int> getAll(const vector<int> &v) {
  vector<int> res;
  int n = v.size();
  for (int i = 0; i < (1 << n); i++) {
    int a = 0;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        a ^= v[j];
      }
    }
    res.push_back(a);
  }
  sort(res.begin(), res.end());
  res.erase(unique(res.begin(), res.end()), res.end());
  return res;
}

int n;
vector<int> v;

map<int, vector<int>> cache;

vector<int> solve(int a, int b) {
  int cc = (a << 16) | b;
  if (cache.find(cc) != cache.end()) {
    return cache[cc];
  }
  vector<int> &res = cache[cc];

  if (!a) {
    vector<int> nv;
    for (int i = 0; i < n; i++) {
      if (b & (1 << i)) {
        nv.push_back(v[i]);
      }
    }
    return res = getAll(nv);
  };

  if (__builtin_popcount(a) % 2 == n % 2) {
    int t = a;
    while (t) {
      int bit = t & ~(t - 1);
      if (a == t) {
        res = solve(a ^ bit, b);
      } else {
        res = vand(res, solve(a ^ bit, b));
      }

      t ^= bit;
    }
    return res;
  }

  int t = a;
  while (t) {
    int bit = t & ~(t - 1);
    vector<int> cur = solve(a ^ bit, b ^ bit);
    for (int x : cur) {
      res.push_back(x);
    }

    t ^= bit;
  }
  sort(res.begin(), res.end());
  res.erase(unique(res.begin(), res.end()), res.end());
  return res;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  scanf("%d", &n);
  v.resize(n);

  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
  }

  vector<int> res = solve((1 << n) - 1, 0);
  assert(res[0] == 0);

  printf("%d\n", (int)res.size() - 1);
  for (int x : res) {
    if (x) {
      printf("%d ", x);
    }
  }
  printf("\n");

  return 0;
}
