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

#define TEST

#ifdef TEST
vector<int> real;
vector<int> ireal;
#endif

int ops;

int query(int a, int b, int c) {
  printf("? %d %d %d\n", a, b, c);
  ops++;
  assert(ops < 12512);
#ifdef TEST
  int n = (int)real.size();
  int v = (real[a] * real[b] + real[c]) % n;
  return ireal[v];
#else
  fflush(stdout);
  int res;
  scanf("%d", &res);
  return res;
#endif
}

int find_zero(int n) {
  vector<int> v;
  for (int i = 0; i < n; i++) {
    if (query(i, i, i) == i) {
      v.push_back(i);
    }
  }
  assert(v.size());
  while (v.size() != 1) {
    vector<int> nv;
    for (int c : v) {
      if (query(c, rand() % n, 0) == 0) {
        nv.push_back(c);
      }
    }
    v = nv;
  }
  return v[0];
}

int totient(int n) {
  int phi = 1;
  for (int i = 2; i <= n; i++) {
    if (n % i == 0) {
      phi *= i - 1;
      n /= i;
      while (n % i == 0) {
        phi *= i;
        n /= i;
      }
    }
  }
  return phi;
}

int find_one(int n, int zero) {
  int phi = totient(n);

  while (true) {
    int x = rand() % n;

    int t = phi - 1;
    int res = x;
    while (t) {
      if (t & 1) res = query(res, x, zero);
      x = query(x, x, zero);
      t /= 2;
    }

    bool bad = false;
    while (ops + n < 12500 && !bad) {
      int zz = rand() % n;
      if (query(res, zz, zero) != zz) {
        bad = true;
      }
    }
    if (!bad) return res;
  }
}


vector<int> solve(int n) {
  if (n == 1) {
    return vector<int>(1);
  }
  int zero = find_zero(n);
#ifdef TEST
  assert(real[zero] == 0);
#endif
  int one = find_one(n, zero);
#ifdef TEST
  assert(real[one] == 1);
#endif
  vector<int> ans(n);
  ans[zero] = 0;
  ans[one] = 1;
  int cur = one;
  for (int i = 2; i < n; i++) {
    cur = query(one, cur, one);
    ans[cur] = i;
  }
  return ans;
}

int main() {
#ifdef TEST
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
#ifdef TEST
  real.resize(n);
  ireal.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &real[i]);
    ireal[real[i]] = i;
  }
#endif

  vector<int> ans = solve(n);
#ifdef TEST
  assert(ans == real);
#endif
  printf("!");
  for (int x : ans) {
    printf(" %d", x);
  }
  printf("\n");
  return 0;
}
