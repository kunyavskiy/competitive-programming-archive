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

bool solve(vector<int> v) {
  int minv = *min_element(v.begin(), v.end());
  int maxv = *max_element(v.begin(), v.end());

  if (minv < maxv - 1) {
    return false;
  }

  int cnta, cntb;
  cnta = cntb = 0;
  for (int x : v) {
    if (x == maxv) {
      cntb++;
    } else {
      cnta++;
    }
  }

  if (cnta >= maxv) {
    return false;
  }

  if (cnta == 0 && cntb == maxv + 1) {
    return true;
  }

  int b_cols = maxv - cnta;
  int min_cntb = b_cols * 2;
  return cntb >= min_cntb;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> v(n);
    for (int &x : v) {
      scanf("%d", &x);
    }
    bool res = solve(v);
    printf("%s\n", res ? "Yes" : "No");
  }

  return 0;
}
