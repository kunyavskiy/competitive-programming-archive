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

const int MAXN = 310;
const int MOD = 1000000007;

int cnk[MAXN][MAXN];

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

int mul(int a, int b) {
  return (a * 1LL * b) % MOD;
}

int c[MAXN][MAXN];

const int C = 300;

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }


  for (int i = 0; i < MAXN; i++) {
    for (int j = 1; j < MAXN; j++) {
      add(cnk[i][j], cnk[i][j - 1]);
    }
  }


  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &c[i][j]);
      --c[i][j];
    }
  }

  vector<int> order;
  vector<int> color;
  vector<bool> used(n);
  vector<int> cnt(C);

  for (int i = 0; i < n; i++) {
    int id = -1;
    int col = -1;
    for (int j = 0; j < n; j++) {
      if (used[j]) continue;
      col = -1;
      for (int k = 0; k < n; k++) {
        if (used[k] || j == k) continue;
        if (col == -1) col = c[j][k];
        if (col != c[j][k]) {
          col = -2;
          break;
        }
      }
      if (col != -2) {
        id = j;
        if (col == -1) col = 0;
        break;
      }
    }
    assert(id != -1);
    used[id] = true;
    order.push_back(id);
    color.push_back(col);
    cnt[col]++;
  }

  reverse(order.begin(), order.end());
  reverse(color.begin(), color.end());

  vector<int> at_most(n + 1);

  for (int i = 1; i <= n; i++) {
    vector<int> ccnt = cnt;
    for (int j = 0; j < n; j++) {
      ccnt[color[j]]--;
      int cur = 1;
      for (int k = 0; k < C; k++) {
        cur = mul(cur, cnk[ccnt[k]][i - 1]);
      }
      add(at_most[i], cur);
    }
  }

  int ans = 0;

  for (int i = 1; i <= n; i++) {
    int cur = at_most[i];
    add(cur, MOD - at_most[i - 1]);
    add(ans, mul(cur, i));
  }

  printf("%d\n", ans);

  return 0;
}
