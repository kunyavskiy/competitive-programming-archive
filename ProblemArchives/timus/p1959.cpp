#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const long long linf = 1e18;
const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

const int MAXV = 1e5 + 10;

class Counter {
  vi cnts;
  set<pii> bs;

  public:
  Counter() : cnts(MAXV + 1, 0) {}
  void add(int x) {
    if (cnts[x]) bs.erase(mp(-cnts[x], x));
    cnts[x]++;
    bs.insert(mp(-cnts[x], x));
  }
  void del(int x) {
    bs.erase(mp(-cnts[x], x));
    if (--cnts[x])
      bs.insert(mp(-cnts[x], x));
  }
  int getMaxFreq() {
    assert(!bs.empty());
    return bs.begin()->second;
  }
};

int main() {
/*  #ifdef DEBUG
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
  #else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif    */

  int n;
  while (scanf("%d", &n) >= 1) {
    vi s(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &s[i]);

    int m;
    scanf("%d", &m);
    vi p(m);
    for (int i = 0; i < m; i++)
      scanf("%d", &p[i]);

    {
      Counter c;
      int cl = 0, cr = 0;

      for (int i = 0; i < m; i++) {
        int l = i, r = n - m + i + 1;
        while (cr < r)
          c.add(s[cr++]);
        while (cl < l)
          c.del(s[cl++]);

        if (p[i] == 0)
          p[i] = c.getMaxFreq();
      }
    }
    {
      Counter c;
      int cl = 0, cr = 0;

      for (int i = 0; i < n; i++) {
        int l = max(0, i - n + m);
        int r = min(m - 1, i) + 1;

        while (cr < r)
          c.add(p[cr++]);
        while (cl < l)
          c.del(p[cl++]);

        if (s[i] == 0)
          s[i] = c.getMaxFreq();
      }
    }

    for (int i = 0; i < n; i++)
      printf("%d%c", s[i], "\n "[i + 1 < n]);
    for (int i = 0; i < m; i++)
      printf("%d%c", p[i], "\n "[i + 1 < m]);
  }
  timestamp("end");
  return 0;
}
