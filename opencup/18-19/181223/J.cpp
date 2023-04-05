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

namespace SA {
  const int MAXN = 1 << 19;
  const int SIGMA = 27;

  int sz, last;
  int nxt[MAXN][SIGMA];
  int link[MAXN], len[MAXN], pos[MAXN];
  int e[MAXN][SIGMA];

  void init(int z) {
    for (int i = 0; i < min(MAXN, 2 * z + 10); i++) {
      memset(e[i], -1, sizeof(e[i]));
      memset(nxt[i], -1, sizeof(nxt[i]));
      link[i] = -1;
      len[i] = 0;
    }
    /*memset(nxt, -1, sizeof(nxt));
    memset(link, -1, sizeof(link));
    memset(len, 0, sizeof(len));*/
    last = 0;
    sz = 1;
  }

  void add(int c) {
    int cur = sz++;
    len[cur] = len[last] + 1;
    pos[cur] = len[cur];
    int p = last;
    last = cur;
    for (; p != -1 && nxt[p][c] == -1; p = link[p]) nxt[p][c] = cur;
    if (p == -1) {
      link[cur] = 0;
      return;
    }
    int q = nxt[p][c];
    if (len[p] + 1 == len[q]) {
      link[cur] = q;
      return;
    }
    int clone = sz++;
    memcpy(nxt[clone], nxt[q], sizeof(nxt[q]));
    len[clone] = len[p] + 1;
    pos[clone] = pos[q];
    link[clone] = link[q];
    link[q] = link[cur] = clone;
    for (; p != -1 && nxt[p][c] == q; p = link[p]) nxt[p][c] = clone;
  }

  int n;
  string s;
  int l[MAXN], r[MAXN];

  void getSufTree(string _s) {
    //memset(e, -1, sizeof(e));
    s = _s;
    n = s.length();
    reverse(s.begin(), s.end());
    init(s.length());
    for (int i = 0; i < n; i++) add(s[i] - 'a');
    reverse(s.begin(), s.end());
    for (int i = 1; i < sz; i++) {
      int j = link[i];
      l[i] = n - pos[i] + len[j];
      r[i] = n - pos[i] + len[i];
      e[j][s[l[i]] - 'a'] = i;
    }
  }

  double dfs(int v, int len) {
    len += r[v] - l[v];

    vector<double> vct;

    bool any = 0;
    for (int c = 0; c < SIGMA; c++) {
      int to = e[v][c];
      if (to == -1) continue;
      double res = dfs(to, len);
      any = 1;
      if (res < -0.5) continue;
      vct.push_back(res);
    }
    bool zero = 0;
    for (double x : vct) if (x < 1e-10) zero = 1;

    double res = 0;
    if (!zero) {
      double sum = 0;
      for (double x : vct) sum += 1 / x;
      vector<double> pr;
      for (double x : vct) pr.push_back((1 / x) / sum);

      for (int i = 0; i < (int)vct.size(); i++) {
        res = max(res, pr[i] * vct[i]);
      }
    }
    res += r[v] - l[v];
    if (!any) res -= 1;

    //cout << v << " " << res << endl;
    if (len == 1 && !any) res = -1;
    return res;
  }
}


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  //freopen("j.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    char buf[1111111];
    scanf("%s", buf);
    string s = buf;
    s += (char)('z' + 1);

    SA::getSufTree(s);

    printf("%.17f\n", SA::dfs(0, 0));
  }

  return 0;
}

