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

void solve(int k, int n, int m) {
  vector<int> a(k);
  int last = 1;
  for (int i = 0; i < k; i++) {
    scanf("%d", &a[i]);
    if (a[i] == -1) {
      a[i] = last;
    }
    last = a[i];
  }

  if (k > n) {
    printf("-1\n");
    return;
  }
  for (int i = 1; i < k; i++) {
    if (a[i] < a[i - 1]) {
      printf("-1\n");
      return;
    }
  }

  vector<int> ans;

  for (int i = 0; i < k; i++) {
    for (int j = m; j > a[i]; j--) {
      if (k - i + (int)ans.size() == n) break;
      ans.push_back(j);
    }
    ans.push_back(a[i]);
  }
  if ((int)ans.size() < n) {
    printf("-1\n");
  } else {
    for (int x : ans) {
      printf("%d ", x);
    }
    printf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int k, n, m;
  while (scanf("%d%d%d", &k, &n, &m) == 3) {
    solve(k, n, m);
#ifndef LOCAL
    break;
#endif
  }

  return 0;
}
