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

const int MOD = 998244353;

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

vector<int> l;
vector<int> r;

map<pair<int, ll>, int> states;

ll H(const vector<int>& v) {
  ll cur = 321321321321;
  for (int x : v) {
    cur = cur * 1717239239 + x;
  }
  return cur;
}

int calc(int pos, vector<int> v) {
  auto res = states.insert({{pos, H(v)}, 0});
  if (!res.second) {
    return res.first->second;
  }
  int &ans = res.first->second;
  ans = 0;

  if (pos == (int)l.size()) {
    ans = 1;
    for (int i = 0; i < (int)v.size(); i++) {
      if (v[i] == i) {
        ans = mul(ans, 35);
      }
    }
    return ans;
  }
  add(ans, calc(pos + 1, v));
  auto join = [&](int a, int b) {
    if (v[a] == v[b]) return;
    int from_id = max(v[a], v[b]);
    int to_id = min(v[a], v[b]);
    for (int &x : v) {
      if (x == from_id) {
        x = to_id;
      }
    }
  };

  int len = r[pos] - l[pos];
  len /= 2;
  for (int j = 0; j < len; j++) {
    join(l[pos] + j, l[pos] + len + j);
  }
  sub(ans, calc(pos + 1, v));
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

//  int n, k;
//  cin >> n >> k;
//  cerr << n << " " << k << endl;
  for (int n = 1; n <= 100; n++) {
    for (int k = 0; k <= 16; k++) {
      l.clear();
      r.clear();
      states.clear();
      eprintf("%d %d\n", n, k);
      for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
          int len = j - i;
          if (len % 2 == 0 && len >= n - k) {
            l.push_back(i);
            r.push_back(j);
          }
        }
      }

      vector<int> cur(n);
      for (int i = 0; i < n; i++) {
        cur[i] = i;
      }

      printf("a[%d][%d] = %d;\n", n, k, calc(0, cur));
      eprintf("a[%d][%d] = %d;\n", n, k, calc(0, cur));
    }
  }
  eprintf("%d\n", (int)states.size());
  return 0;
}
