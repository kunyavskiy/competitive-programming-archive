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

// (altering lowest row, non-altering)
pair<int, int> solve(vector<int> v) {
  if (v.size() == 0) {
    return {1, 0};
  }
  if (v.size() == 1) {
    return {mpow(2, v[0]), 0};
  }
  int m = *min_element(v.begin(), v.end());

  int res1 = 1;
  int res2 = 1;
  vector<int> st;
  for (int i = 0; i <= (int)v.size(); i++) {
    if (i != (int)v.size() && v[i] > m) {
      st.push_back(v[i] - m + 1);
    } else {
      auto r = solve(st);
      res1 = mul(res1, mul(r.first, minv(st.empty() ? 1 : 2)));
      res2 = mul(res2, r.first + r.second);
      if (i != (int)v.size()) {
        res2 = mul(res2, 2);
      }
      st.clear();
    }
  }

  sub(res2, mul(res1, 2));
  res1 = mul(res1, mpow(2, m));

  return {res1, res2};
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> v(n);
    for (int &x : v) {
      scanf("%d", &x);
    }
    auto res = solve(v);
    printf("%d\n", (res.first + res.second) % MOD);
//    break;
  }

  return 0;
}
