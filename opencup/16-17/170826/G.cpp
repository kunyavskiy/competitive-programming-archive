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

void solve(int n) {
  vector<int> next(n);
  for (int i = 0; i < n; i++) {
    if (i < n / 2) {
      next[i] = (2 * i + 1) % n;
    } else {
      next[i] = (2 * i) % n;
    }
  }
  while (true) {
    vector<int> col(n, -1);
    int c = 0;
    for (int i = 0; i < n; i++) {
      if (col[i] == -1) {
        c++;
        for (int j = i; col[j] == -1; j = next[j]) {
          col[j] = c;
        }
      }
    }
    if (c == 1) {
      break;
    }
    for (int i = 0; ; i++) {
      assert(i < n / 2);
      if (col[i] != col[i + n / 2]) {
        swap(next[i], next[i + n / 2]);
        break;
      }
    }
  }

  string res = "";
  int cur = 0;
  for (int i = 0; i < n; i++) {
    int to = next[cur];
    if ((cur * 2) % n == to) {
      res += "0";
    } else {
      assert((cur * 2 + 1) % n == to);
      res += "1";
    }
    cur = to;
  }
  assert(cur == 0);
  printf("%s\n", res.c_str());
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }

  return 0;
}
