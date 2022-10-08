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

char s[2][4100];

void solve() {
  scanf("%s%s", s[0], s[1]);
  int n = strlen(s[0]);
  int cnt[2][4];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < n; j += 2) {
      cnt[i][s[i][j] - '0' + (s[i][j + 1] - '0') * 2]++;
    }
  }
  if (cnt[0][0] != cnt[1][0] || cnt[0][3] != cnt[1][3]) {
    printf("-1\n");
    return;
  }
  vector<int> ans;
  auto rev = [&](int x) {
    assert(x % 2 == 0);
    ans.push_back(x);
    reverse(s[0], s[0] + x);
  };

  for (int i = 0; i < n; i += 2) {
    int ch =
  }
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
