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

#define next next_111

map<pair<vector<int>, vector<int>>, int> id;
vector<pair<vector<int>, vector<int>>> byid;

struct item {
  int a, b;
};

vector<vector<item>> next;

int get_id(const pair<vector<int>, vector<int>> &x) {
  auto it = id.find(x);
  if (it != id.end()) {
    return it->second;
  }
  int res = id[x] = (int)byid.size();
  byid.push_back(x);
  next.push_back(vector<item>());
  return res;
}


void gen_all(pair<vector<int>, vector<int>> v) {
  assert(v.first.size() == v.second.size());
  int id = get_id(v);
  if (v.first.size() == 1) {
    return;
  }

  for (int i = 1; i < (int)v.first.size(); i++) {
    vector<int> a(v.first.begin(), v.first.begin() + i);
    vector<int> b(v.first.begin() + i, v.first.end());
    vector<int> c(v.second.begin(), v.second.begin() + i);
    vector<int> d(v.second.begin() + i, v.second.end());

    swap(c.back(), d[0]);

    int aid = get_id({a, c});
    int bid = get_id({b, d});
    next[id].push_back({aid, bid});
  }
}

vector<int> read(int n) {
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
    v[i] += i;
  }
  return v;
}

const int MOD = 1000000007;

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

int minv(int x) {
  return mpow(x, MOD - 2);
}

const int MAXN = 55;

int dp1[MAXN][MAXN];
vector<int> dp2[MAXN][MAXN];
vector<int> dp3[MAXN][MAXN];
vector<vector<int>> points;
int n, m;

const int MAXF = 2e6;

int F[MAXF];
int IF[MAXF];
int invv[MAXF];

int cnk(int n, int k) {
  return mul(F[n], mul(IF[k], IF[n - k]));
}

vector<int> sumf[MAXN];
vector<int> sums[MAXN];

int calc3(int from, int to, int id) {
  int& ans = dp3[from][to][id];
  if (ans != -1) return ans;

  ans = F[sums[to][id] - sumf[from][id]];
  for (int i = 0; i < (int)byid[id].first.size(); i++) {
    if (points[to][byid[id].second[i]] < points[from][byid[id].first[i]]) return ans = 0;
    ans = mul(ans, IF[points[to][byid[id].second[i]] - points[from][byid[id].first[i]]]);
  }

  return ans;
}

int calc2(int from, int to, int id) {
  int& ans = dp2[from][to][id];
  if (ans != -1) return ans;

  ans = calc3(from, to, id);
  for (int i = 0; i < (int)byid[id].first.size(); i++) {
    if (points[to][byid[id].second[i]] < points[from][byid[id].first[i]]) return ans = 0;
  }

  for (auto t : next[id]) {
    int r1 = calc2(from, to, t.a);
    int r2 = calc3(from, to, t.b);
    int r = mul(r1, r2);
    int moves1 = sums[to][t.a] - sumf[from][t.a];
    int moves2 = sums[to][t.b] - sumf[from][t.b];
    r = mul(r, cnk(moves1 + moves2, moves1));
    sub(ans, r);
  }

  if (id == 0) {
    eprintf("(");
    for (int i = 0; i < (int) byid[id].first.size(); i++) {
      eprintf("%d ", points[from][byid[id].first[i]]);
    }
    eprintf("),(");
    eprintf("(");
    for (int i = 0; i < (int) byid[id].first.size(); i++) {
      eprintf("%d ", points[to][byid[id].second[i]]);
    }
    eprintf(")");
    eprintf(" = %d\n", ans);
  }
  return ans;
}

int calc1(int from, int to) {
  int& ans = dp1[from][to];
  if (ans != -1) return dp1[from][to];
  for (int i = 0; i < n; i++) {
    if (points[to][i] < points[from][i]) return ans = 0;
  }

  ans = calc2(from, to, 0);
  for (int i = 0; i < m; i++) {
    if (i != from && i != to) {
      int a = calc1(from, i);
      int b = calc2(i, to, 0);
      sub(ans, mul(a, b));
      if (from == 0 && to == 1) {
        eprintf("-= %d * %d = %d\n", a, b, mul(a, b));
      }
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  invv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    invv[i] = mul(MOD - invv[MOD % i], MOD / i);
    assert(mul(i, invv[i]) == 1);
  }

  F[0] = IF[0] = 1;
  for (int i = 1; i < MAXF; i++) {
    F[i] = mul(F[i - 1], i);
    IF[i] = mul(IF[i - 1], invv[i]);
  }

  scanf("%d%d", &n, &m);

  vector<int> all(n);
  for (int i = 0; i < n; i++) all[i] = i;
  //get_id({all, all});

  //for (int i = 0; i < (int)byid.size(); i++)
    //gen_all(byid[i]);

  m += 2;
  points = vector<vector<int>> (m);
  points[0] = all;
  for (int i = 1; i < m; i++) {
    points[i] = read(n);
  }
  swap(points[1], points[m - 1]);

  int ans = 0;
  function<void(vector<int>)> rec = [&](vector<int> cur) {
    if (cur == points[m - 1]) {
      ans++;
      return;
    }
    for (int i = 1; i < m; i++) if (cur == points[i]) return;
    for (int i = 0; i < n; i++) {
      if (cur[i] > points[m - 1][i]) return;
      if (i > 0 && cur[i - 1] >= cur[i]) return;
    }
    for (int i = 0; i < n; i++) {
      auto ncur = cur;
      ncur[i]++;
      rec(ncur);
    }
  };
  rec(points[0]);
  printf("%d\n", ans);


  return 0;
}
