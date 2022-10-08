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

char s[1'100'000];

int solve(const string& s) {
  vector<int> v(s.size());
  for (int i = 0; i < (int)s.size(); i++) {
    v[i] = s[i] - '0';
  }

  while (v.size() > 1) {
    int last = v.back();
    v.pop_back();
    for (int i = (int)v.size() - 1; i >= 0; i--) {
      int next = abs(v[i] - last);
      last = v[i];
      v[i] = next;
    }
  }
  return v[0];
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    scanf("%s", s);
#ifdef LOCAL
    string init = s;
    int correct = solve(init);
#endif
    for (int i = 0; i < n; i++) {
      s[i]--;
    }
    int mul = 1;
    if (find(s, s + n, '1') == s + n) {
      mul = 2;
      for (int i = 0; i < n; i++) {
        if (s[i] == '2') {
          s[i] = '1';
        }
      }
    }

    int ans = 0;

    for (int i = 0; i < n; i++) {
      if (((~(n - 1)) & i) == 0) {
        if (s[i] == '1') {
          ans ^= 1;
        }
      }
    }
#ifdef LOCAL
    if (ans * mul != correct) {
      eprintf("%s %d %d\n", init.c_str(), ans * mul,correct);
      assert(0);
    }
#endif

    printf("%d\n", ans * mul);
  }


  return 0;
}
