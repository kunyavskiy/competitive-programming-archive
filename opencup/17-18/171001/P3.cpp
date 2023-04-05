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

const int MAXN = 100010;
const int MAXM = 300;

double dp1[MAXN];
int dp1p[MAXN];
double dp2[MAXM][MAXN];
int dp2p[MAXM][MAXN];

int M[MAXM], T[MAXM], I[MAXM];
int m0;
vector<pair<int, int>> res;

void relax(double &v, double nv, int& p, int pval) {
  if (v < nv) {
    v = nv;
    p = pval;
  }
}

void restore(int m);

void restore2(int m, int j) {
  if (dp2p[j][m] == -1) {
    restore2(m - M[j], j);
    assert(res.back().first == j);
    res.back().second++;
    return;
  }
  restore(m - M[j] * dp2p[j][m]);
  res.push_back({j, dp2p[j][m]});
}

void restore(int m) {
  if (m == m0) {
    return;
  }
  restore2(m, dp1p[m]);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  eprintf("%d\n", (int)((sizeof(dp2) + sizeof(dp2p))/ 1024 / 1024));

  int t, mmax;
  scanf("%d%d", &t, &mmax);

  int vneed;
  scanf("%d%d", &m0, &vneed);

  for (int i = 0; i < t; i++) {
    scanf("%d%d%d", &M[i], &T[i], &I[i]);
  }

  for (int i = 0; i <= mmax; i++) {
    dp1[i] = -1e100;
    for (int j = 0; j < t; j++) {
      dp2[j][i] = -1e100;
    }
  }
  dp1[m0] = 0;

  for (int i = m0; i <= mmax; i++) {
    for (int j = 0; j < t; j++) {
      relax(dp1[i], dp2[j][i] + I[j] * log(i), dp1p[i], j);
      if (i + M[j] <= mmax) {
        relax(dp2[j][i + M[j]], dp2[j][i], dp2p[j][i + M[j]], -1);
      }
    }
    for (int j = 0; j < t; j++) {
      int den = 5 * T[j] - 8 * M[j];
      if (den <= 0) continue;
      int k = (8 * i + den - 1) / den;
      if (i + k * 1LL * M[j] <= mmax) {
        relax(dp2[j][i + k * M[j]], dp1[i] - I[j] * log(i), dp2p[j][i + k * M[j]], k);
      }
    }
  }

  int ms = -1;
  for (int i = 0; i <= mmax; i++) {
    if (dp1[i] >= vneed) {
      ms = i;
      break;
    }
  }
  printf("%d", ms);
  if (ms == -1) {
    printf("\n");
    return 0;
  }

  restore(ms);
  reverse(res.begin(), res.end());
  printf(" %d\n", (int)res.size());
  for (auto x : res) {
    printf("%d %d\n", x.first + 1, x.second);
  }

  return 0;
}
