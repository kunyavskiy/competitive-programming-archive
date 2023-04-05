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

int ds(int a) {
  int res = 0;
  while (a) {
    res += a % 10;
    a /= 10;
  }
  return res;
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

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  if (0) {
    int x;
    scanf("%d", &x);
    int ans = 0;
    for (int i = 1; i < x; i++) {
      ans += abs(ds(i) - ds(i + 1));
    }
    printf("%d\n", ans);
    return 0;
  }

  string s;
  cin >> s;
  int n = s.size();
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = s[i] - '0';
  }
  reverse(v.begin(), v.end());

  v[0] -= 1;
  for (int i = 1; i < n; i++) {
    v[0] -= v[i];
  }
  for (int i = 0; i < n - 1; i++) {
    v[i] += v[i + 1] * 8;
  }

  for (int i : v) {
    eprintf("%d ", i);
  }
  eprintf("\n");


  for (int i = 0; i < (int)v.size(); i++) {
//    for (int i : v) {
//      eprintf("%d ", i);
//    }
    eprintf("\n");
    int to_next = -v[i] / 10;
    if (to_next * 10 + v[i] < 0) {
      to_next++;
    }
    eprintf("v[i] = %d, to_next = %d\n", v[i], to_next);
    assert(to_next * 10 + v[i] >= 0);
    assert(to_next * 10 + v[i] < 10);
    v[i] += to_next * 10;
    if (to_next && i + 1 == (int)v.size()) {
      v.push_back(0);
    }
    v[i + 1] -= to_next;
  }

  while (v.size() > 1 && v.back() == 0) v.pop_back();

  reverse(v.begin(), v.end());

  int ans = 0;
  for (int i : v) {
    ans = mul(ans, 10);
    add(ans, i);
  }
  printf("%d\n", ans);

  return 0;
}
