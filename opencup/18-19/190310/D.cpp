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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

int MOD;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

const int MAXN = 3010;

int cnk[MAXN][MAXN];
int f[MAXN];
int c2[MAXN];

int cnt[MAXN];
int ans[MAXN];

int cnt2[MAXN];
int ans2[MAXN];


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d%d", &t, &MOD);

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }
  f[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
  }
  c2[0] = c2[1] = c2[2] = 1;
  for (int i = 3; i < MAXN; i++) {
    c2[i] = mul(c2[i - 1], i);
  }


  for (int i = 1; i < MAXN; i++) {
    if (i <= 2) {
      cnt[i] = 1;
    } else {
      cnt[i] = mpow(i, i - 2);
    }
    for (int k = i; k >= 3; k--) {
      int cur = cnk[i][k];
      cur = mul(cur, c2[k - 1]);
      if (k != i) {
        cur = mul(cur, k);
        cur = mul(cur, mpow(i, i - k - 1));
      }
      add(cnt[i], cur);
      cur = mul(cur, k);
      add(ans[i], cur);
    }
  }

  for (int i = 1; i < MAXN; i++) {
    cnt2[i] = cnt[i];
    ans2[i] = ans[i];
    for (int j = 1; j < i; j++) {
      int c = cnk[i - 1][j - 1];
      int ncnt = mul(cnt[j], cnt2[i - j]);
      add(cnt2[i], mul(ncnt, c));
      int ansl = mul(ans[j], cnt2[i - j]);
      add(ans2[i], mul(ansl, c));
      int ansr = mul(cnt[j], ans2[i - j]);
      add(ans2[i], mul(ansr, c));
    }
  }

  while (t-->0) {
    int x;
    scanf("%d", &x);
    printf("%d\n", ans2[x]);
  }



  return 0;
}
