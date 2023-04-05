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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  static char s[int(1e6) + 10];
  while (scanf("%s", s) == 1) {
    const int n = strlen(s);
    vector<vector<int>> ne(n + 1, vector<int>(26, n));
    {
      vector<int> las(26, n);
      for (int i = n - 1; i >= 0; i--) {
        las[s[i] - 'a'] = i;
        ne[i] = las;
      }
    }

    int ans = 0;
    for (int i = 0; i < n;) {
      ans++;
      const int st = i;
      int ptr = 0;
      while (i < n && ptr < st && ne[ptr][s[i] - 'a'] < st) {
        ptr = ne[ptr][s[i] - 'a'] + 1;
        i++;
      }
      if (st == i) {
        i++;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
