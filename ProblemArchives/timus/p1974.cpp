#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <sstream>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#ifndef LOCAL
#undef assert
void assert(bool x) {
  if (!x) printf("%d\n", 5 / 0);
}
void assert2(bool x) {
  if (!x) {
    int *tmp = new int[1];
    tmp[int(1e5)] = 100 / 23;
  }
}
#else
#define assert2 assert
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef linux
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

const int inf = 1e9;
const double eps = 1e-9;
const double INF = inf;
const double EPS = eps;

int getNote(char *buf) {
  assert(buf[0] >= '1' && buf[0] <= '8');
  int base = (buf[0] - '1') * 12;
  const char *LS = "CDEFGAB";
  const int offs[] = { 0, 2, 4, 5, 7, 9, 11 };
  int x = strchr(LS, buf[1]) - LS;
  assert(0 <= x && x < 7);
  base += offs[x];
  if (buf[2] == '+') base++;
  else if (buf[2] == '-') base--;
  return base;
}

const int MAXL = 1010;
int n, m;
int a[MAXL + 1];
int b[MAXL + 1];

int d[MAXL + 1][MAXL + 1];

int main(){     
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  while (scanf("%d", &n) == 1) {
    vi base(n);
    for (int i = 0; i < n; i++) {
      char buf[5];
      scanf("%s", buf);
      a[i] = getNote(buf);
    }

    int k;
    scanf("%d", &k);
    while (k --> 0) {
      scanf("%d", &m);
      for (int i = 0; i < m; i++) {
        char buf[5];
        scanf("%s", buf);
        b[i] = getNote(buf);
      }

      int ans = 0;
      for (int p1 = n; p1 >= 0; p1--)
      for (int p2 = m; p2 >= 0; p2--) {
        if (p1 >= n || p2 >= m) {
          d[p1][p2] = 0;
          continue;
        }
        d[p1][p2] = d[p1 + 1][p2 + 1] + (a[p1] == b[p2]);
        ans = max(ans, d[p1][p2]);
      }
      printf("%.8lf\n", double(ans) / m);
    }
  }

  TIMESTAMP(end);
  return 0;
}
