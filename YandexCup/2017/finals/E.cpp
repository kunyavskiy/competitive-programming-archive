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

int ans[10100];
int n;
char correct[10100];
int ops;

int cache[10100];

int get(int pos) {
  if (cache[pos] != -1) return cache[pos];
  ++ops;
  printf("? %d\n", pos + 1);
  fflush(stdout);
#ifdef LOCAL
  for (int j = 0;; j++) {
    if (pos - j >= 0 && correct[pos - j] == '1') return cache[pos] = j;
    if (pos + j < n && correct[pos + j] == '1') return cache[pos] = j;
  }
#else
  int ans;
  scanf("%d", &ans);
  cache[pos] = ans;
  return ans;
#endif
}

void solve(int a, int b) {
  if (b - a <= 1) {
    return;
  }
  int m = (a + b) / 2;
  int x = get(m);
  vector<int> v;
  v.push_back(a);
  v.push_back(b);
  assert(m - x >= a);
  if (m - x != a) {
    int t = get(m - x);
    if (t == 0) {
      ans[m - x] = 1;
      v.push_back(m - x);
    }
  }
  assert(m + x <= b);
  if (m + x != b && x != 0) {
    int t = get(m + x);
    if (t == 0) {
      ans[m + x] = 1;
      v.push_back(m + x);
    }
  }

  sort(v.begin(), v.end());

  if (v.size() == 2) return;

  for (int i = 0; i < (int)v.size() - 1; i++) {
    solve(v[i], v[i+1]);
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  memset(cache, -1, sizeof(cache));

  scanf("%d", &n);

#ifdef LOCAL
  scanf("%s", correct);
#endif


  int a1 = get(0);
  int a2 = get(n - 1);
  ans[a1] = 1;
  ans[n - 1 - a2] = 1;
  solve(a1, n - 1 - a2);

  int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (ans[i] == 1) {
      cnt++;
    }
  }
  assert(ops <= 4 * cnt);

  printf("! %d", cnt);
  for (int i = 0; i < n; i++) {
    if (ans[i]) {
      printf(" %d", i + 1);
    }
  }
  printf("\n");
  fflush(stdout);


  return 0;
}
