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


const int Z = 10;
const int LEN = 101;
const int N = 73;
const int MOD = 1e9 + 7;

struct Mask {
  bitset<N> b;

  Mask() {
    b.reset();
  }

  bool operator< (const Mask &m) const {
    int id = (b ^ m.b)._Find_first();
    if (id == N) return 0;
    return !b[id];
//    for (int i = 0; i < N; i++) if (b[i] != m.b[i]) return b[i] < m.b[i];
    return 0;
  }

  Mask add(int x) {
    auto nb = (b << x) | (b >> x);
    for (int i = 0; i < x; i++) {
      if (b[i]) {
        int j = -(i - x);
        nb[j] = 1;
      }
    }
    Mask res;
    res.b = nb;
    return res;
  }

  int min() {
    int res = N;
    for (int i = 0; i < N; i++) {
      if (b[i]) {
        res = i;
        break;
      }
    }
    assert(res < Z);
    return res;
  }
};

int sz;
vector<Mask> q;
map<Mask, int> mp;
vector<vector<int>> nxt;

vector<vector<vector<int>>> dp;
vector<vector<vector<int>>> sum;

void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}

int mul(int x, int y) {
  return 1LL * x * y % MOD;
}

void init() {
  cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  Mask start;
  start.b[0] = 1;
  mp[start] = q.size();
  q.push_back(start);

  for (int i = 0; i < (int)q.size(); i++) {
    Mask cur = q[i];
    for (int c = 0; c < 10; c++) {
      Mask nw = cur.add(c);
      if (!mp.count(nw)) {
        mp[nw] = q.size();
        q.push_back(nw);
      }
    }
  }
  cerr << clock() / (double)CLOCKS_PER_SEC << endl;

  sz = q.size();
  nxt.assign(sz, vector<int>(Z));
  for (int i = 0; i < sz; i++) {
    for (int c = 0; c < Z; c++) {
      nxt[i][c] = mp[q[i].add(c)];
    }
  }

  dp.assign(LEN, vector<vector<int>>(sz, vector<int>(Z)));
  sum.assign(LEN, vector<vector<int>>(sz, vector<int>(Z)));
  for (int v = 0; v < sz; v++) {
    dp[0][v][q[v].min()] = 1;
    sum[0][v][q[v].min()] = 0;
  }
  for (int i = 1; i < LEN; i++) {
    for (int v = 0; v < sz; v++) {
//      vector<unsigned long long> tmpsum(Z);

      for (int j = 0; j < Z; j++) {
        unsigned long long tmpsum = 0;
        for (int c = 0; c < Z; c++) {
          int nv = nxt[v][c];
          add(dp[i][v][j], dp[i - 1][nv][j]);
          tmpsum += 1LL * dp[i - 1][nv][j] * c;
          tmpsum += 1LL * sum[i - 1][nv][j] * Z;
        }
        sum[i][v][j] = tmpsum % MOD;
      }
    }
  }
}

vector<int> solve(string s) {
  vector<int> res(Z);

  vector<unsigned long long> pw10(s.length() + 2);
  pw10[0] = 1;
  for (int i = 1; i < (int)pw10.size(); i++) pw10[i] = pw10[i - 1] * 10LL % MOD;

  vector<vector<int>> pwc(s.length() + 2, vector<int>(Z));
  for (int i = 0; i < (int)pwc.size(); i++) {
    for (int j = 0; j < Z; j++) {
      if (i == 0) {
        pwc[i][j] = j;
      } else {
        pwc[i][j] = 1LL * pwc[i - 1][j] * 10 % MOD;
      }
    }
  }

  int pref = 0;
  int v = 0;
  for (int i = 0; i < (int)s.length(); i++) {
    int cadd = s.length() - 1 - i;
    int tprev = 1LL * pref * pw10[cadd + 1] % MOD;
    for (int j = 0; j < Z; j++) {
      unsigned long long tmpsum = 0;
      for (int c = 0; '0' + c < s[i]; c++) {
        int nv = nxt[v][c];
        tmpsum += sum[cadd][nv][j];
        tmpsum += 1LL * (tprev + pwc[cadd][c]) * dp[cadd][nv][j];
      }
      res[j] = ((unsigned long long)res[j] + tmpsum) % MOD;
    }
    v = nxt[v][s[i] - '0'];

    pref = (10LL * pref + (s[i] - '0')) % MOD;
  }
  add(res[q[v].min()], pref);
  return res;
}

vector<int> solve(string l, string r) {
  for (int i = (int)l.length() - 1; i >= 0; i--) {
    if (l[i] == '0') {
      l[i] = '9';
      continue;
    }
    l[i]--;
    break;
  }

  auto v1 = solve(l);
  auto v2 = solve(r);
  for (int i = 0; i < Z; i++) {
    v2[i] = (v2[i] - v1[i] + MOD) % MOD;
  }
  return v2;
}

void print(vector<int> v) {
  for (int i = 0; i < (int)v.size(); i++) printf("%d%c", v[i], " \n"[i + 1 == (int)v.size()]);
}

void test() {
  cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  for (int i = 0; i < 1e4; i++) {
    int n = 100;
    string t(n, '9');

    solve(t, t);
  }
  cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
//  freopen("e.out", "w", stdout);
#endif
  init();
//  test();


  int T;
  scanf("%d", &T);
  while (T--) {
    static char b1[LEN], b2[LEN];
    scanf("%s%s", b1, b2);

    print(solve(b1, b2));
  }

  return 0;
}
