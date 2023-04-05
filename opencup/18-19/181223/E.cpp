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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const ll MOD = 998244353;
const int MAX = 10005;

void add(ll& a, ll b) {
  a += b;
  if (a >= MOD) a -= MOD;
}

vector<ll> calc(string s) {
  vector<ll> d(2 * MAX + 1);
  vector<ll> dd(2 * MAX + 1);
  d[MAX - 1] = 1;
  for (int i = (int) s.size() - 1; i >= 0; i--) {
    fill(dd.begin(), dd.end(), 0);
    for (int j = 0; j < (int) d.size(); j++) {
      if (d[j] != 0) {
        if (s[i] != 'P') {
          add(dd[j + 2], d[j]);
        }
        if (s[i] != 'V') {
          add(dd[min(j - 2, MAX - 2)], d[j]);
        }
      }
    }
    swap(d, dd);
  }
//  for (int i = 0; i < (int)d.size(); i++) {
//    if (d[i] > 0) {
//      cout << (i - MAX) << ": " << d[i] << "\n";
//    }
//  }
  return d;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  static char temp[5001];
  scanf("%s", temp);
  string a = temp;
  scanf("%s", temp);
  string b = temp;

  auto aa = calc(a);
  auto bb = calc(b);

  ll res = 0;
  for (int da = 0; da < (int)aa.size(); da++) {
    for (int db = 0; db < (int)bb. size(); db++) {
      int s = da + db - MAX - MAX;
      if (s > -3) {
        add(res, (aa[da] * bb[db]) % MOD);
      }
    }
  }
  cout << res << "\n";

  return 0;
}
