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
#include <random>

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
typedef unsigned long long ull;
typedef long double ld;

int n;

ll calc(int d) {
  return (ll)d * (n - d);
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int m;
  scanf("%d%d", &n, &m);
  vector<int> l(m), r(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d", &l[i], &r[i]);
    l[i]--;
    r[i]--;
    if (l[i] > r[i]) swap(l[i], r[i]);
  }
  vector<int> a(n);
  for (int i = 0; i < m; i++) {
    a[l[i]]++;
    a[r[i]]--;
  }
  for (int i = 0; i < n; i++) {
    a[i + 1] += a[i];
  }
  ll res = 0;
  vector<ll> q = {0, 0};
  for (int i = 0; i < n - 1; i++) {
    if (a[i] == 0) {
      q.push_back(calc(i + 1));
    } else if (a[i] == 1) {
      res = max(res, calc(i + 1));
    }
  }
  sort(q.rbegin(), q.rend());
  res = max(res, q[0] + q[1]);

  mt19937_64 rnd(1234325);
  vector<ull> aa(n);
  for (int i = 0; i < (int)l.size(); i++) {
      ull x = rnd();
      aa[l[i]] ^= x;
      aa[r[i]] ^= x;
  }
  for (int i = 0; i < n - 1; i++) {
    aa[i + 1] ^= aa[i];
  }

  map<ull, vector<int>> s;
  for (int i = 0; i < n - 1; i++) {
    s[aa[i]].push_back(i);
  }

  for (auto p : s) {
    auto q = p.second;
    int m = q.size();
    if (m < 2) continue;
    int j = 0;
    for (int i = 1; i < m; i++) {
      while (q[j] < q[i] - n / 2) {
        j++;
      }
      res = max(res, calc(q[i] - q[j]));
      if (j - 1 >= 0) {
        res = max(res, calc(q[i] - q[j - 1]));
      }
    }
  }

  cout << res * 2 << "\n";

  return 0;
}
