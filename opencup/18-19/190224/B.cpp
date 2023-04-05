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

const int INF = 1e9;

struct segtree {
#ifndef LOCAL
#endif

  int n;
  int N;
  vector<int> a;
  vector<int> sum, mn;

  void pull(int i) {
    sum[i] = sum[i * 2] + sum[i * 2 + 1];
    mn[i] = min(mn[i * 2], mn[i * 2 + 1] + sum[i * 2]);
  }

  segtree() {}
  segtree(vector<int> bal) {
    a = bal;
    n = a.size();

    N = 1;
    while (N < n) N <<= 1;

    sum.resize(N * 2);
    mn.resize(N * 2);

    for (int i = 0; i < n; i++) {
      sum[N + i] = a[i];
      mn[N + i] = min(0, a[i]);
    }
    for (int i = N - 1; i >= 1; i--) {
      pull(i);
    }
  }

  void upd(int x, int y) {
    a[x] = y;
    x += N;
    sum[x] = y;
    mn[x] = min(y, 0);
    while (x > 1) {
      x >>= 1;
      pull(x);
    }
  }

  int globmin() {
    /*int res = 0;
    int cur = 0;
    for (int i = 0; i < n; i++) {
      cur += a[i];
      res = min(res, cur);
    }
    return res;*/
    return mn[1];
  }
};

int charBalance(char c) {
  if (c == '(') return 1;
  if (c == ')') return -1;
  assert(0);
}

int fast(string s, vector<int> c) {
  int n = s.length();

  // 0 -- open
  // 1 -- close
  vector<vector<vector<int>>> pos(3, vector<vector<int>>(2));
  for (int i = 0; i < n; i++) {
    pos[c[i]][s[i] == ')'].push_back(i);
  }
  for (int i = 0; i < 3; i++) {
    reverse(pos[i][0].begin(), pos[i][0].end());
  }

  auto fix = [&](int tp, int nbal) {
    int cbal = 0;
    cbal += pos[tp][0].size();
    cbal -= pos[tp][1].size();
    if (abs(cbal % 2) != abs(nbal % 2)) return 0;

    // new - old
    int delta = (nbal - cbal) / 2;

    if (delta < 0) {
      // ( to )
      if ((int)pos[tp][0].size() < -delta) return 0;
      for (int i = 0; i < -delta; i++) s[pos[tp][0][i]] ^= '(' ^ ')';
    } else {
      // ) to (
      if ((int)pos[tp][1].size() < delta) return 0;
      for (int i = 0; i < delta; i++) s[pos[tp][1][i]] ^= '(' ^ ')';
    }
    return 1;
  };

  int ans = INF;
  auto olds = s;
  for (int bal2 = -n; bal2 <= n; bal2++) {
    s = olds;

    int bal0 = -bal2;
    int bal1 = -bal2;

    if (!fix(0, bal0) || !fix(1, bal1) || !fix(2, bal2)) {
      continue;
    }

    int curCost = 0;
    for (int i = 0; i < n; i++) curCost += s[i] != olds[i];

    vector<vector<vector<int>>> npos(3, vector<vector<int>>(2));
    for (int i = 0; i < n; i++) {
      npos[c[i]][s[i] == ')'].push_back(i);
    }
    for (int i = 0; i < 3; i++) {
      reverse(npos[i][0].begin(), npos[i][0].end());
      int k = min(npos[i][0].size(), npos[i][1].size());
      npos[i][0].resize(k);
      npos[i][1].resize(k);
      while (!npos[i][0].empty() && npos[i][0].back() <= npos[i][1].back()) {
        npos[i][0].pop_back();
        npos[i][1].pop_back();
      }
    }


    vector<vector<int>> bal(2);
    for (int i = 0; i < 2; i++) {
      bal[i].resize(n);
      for (int j = 0; j < n; j++) {
        int was = 0;
        int delta = c[j] == i ? 0 : charBalance(s[j]);
        bal[i][j] = was + delta;
      }
    }
    vector<segtree> tr(2);
    for (int i = 0; i < 2; i++) tr[i] = segtree(bal[i]);

    auto change = [&](int i) {
      curCost -= s[i] != olds[i];
      s[i] ^= '(' ^ ')';
      curCost += s[i] != olds[i];

      tr[0].upd(i, charBalance(s[i]) * (int)(c[i] != 0));
      tr[1].upd(i, charBalance(s[i]) * (int)(c[i] != 1));
    };
    vector<int> ptr(2);
    auto changePair = [&](int i, int j) {
      change(i);
      change(j);
    };

    for (int i = 0; i < 2; i++) {
      while (ptr[i] < (int)npos[i][0].size()) {
        changePair(npos[i][0][ptr[i]], npos[i][1][ptr[i]]);
        ptr[i]++;
      }
    }

    bool wasOk = 0;
    for (int taken2 = 0; taken2 <= (int)npos[2][0].size(); taken2++) {
      wasOk |= tr[0].globmin() >= 0 && tr[1].globmin() >= 0;

      for (int i = 0; i < 2; i++) {
        while (wasOk && ptr[i] > 0 && tr[i ^ 1].globmin() >= 0) {
          ptr[i]--;
          changePair(npos[i][0][ptr[i]], npos[i][1][ptr[i]]);
        }
      }

      int realCost = curCost;
      for (int i = 0; i < 2; i++) {
        if (tr[i].globmin() < 0) {
          realCost += 2;
        }
      }
      if (wasOk) ans = min(ans, realCost);

      if (taken2 < (int)npos[2][0].size()) {
        changePair(npos[2][0][taken2], npos[2][1][taken2]);
      }
    }
  }

  if (ans == INF) ans = -1;
  return ans;
}

bool correct(string s) {
  int cur = 0;
  for (char c : s) {
    if (c == '(') cur++;
    if (c == ')') cur--;
    if (cur < 0) return 0;
  }
  return cur == 0;
}

int slow(string s, vector<int> c) {
  int n = s.length();

  int ans = INF;
  for (int mask = 0; mask < (1 << n); mask++) {
    string t = s;
    for (int i = 0; i < n; i++) {
      if (mask & (1 << i)) {
        t[i] ^= '(' ^ ')';
      }
    }
    vector<string> b(2);
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < n; j++) {
        if (c[j] != i) {
          b[i] += t[j];
        }
      }
    }
    if (correct(b[0]) && correct(b[1])) {
      ans = min(ans, __builtin_popcount(mask));
    }
  }
  if (ans == INF) ans = -1;
  return ans;
}

void stress() {
  for (int it = 3361;; it++) {
    if (it % (int)1e3 == 0) cout << it << endl;
    srand(it);

    int n = rand() % 10 + 1;
    string s = "";
    for (int i = 0; i < n; i++) s += "()"[rand() % 2];
    vector<int> c(n);
    for (int i = 0; i < n; i++) c[i] = rand() % 3;

    auto ans1 = fast(s, c);
    auto ans2 = slow(s, c);
    if (ans1 != ans2) {
      cout << ans1 << " instead of " << ans2 << endl;
      cout << s << endl;
      for (int x : c) cout << x << " ";
      exit(0);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  //freopen("b.out", "w", stdout);
#endif
//  stress();

  int n;
  while (scanf("%d", &n) == 1) {
    static char buf[111111];
    scanf("%s", buf);
    string s = buf;
    vector<int> c(n);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    printf("%d\n", fast(s, c));
  }

  return 0;
}
