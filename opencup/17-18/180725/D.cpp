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

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> ends(n + 1);
  vector<int> starts(n);
  for (int i = 0; i < m; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    ends[r].push_back(l - 1);
    starts[l - 1]++;
  }
  set<int> valid;
  vector<int> cnt(n + 1);
  for (int i = 1; i <= n; i++) {
    valid.insert(i);
  }

  multiset<int> segs;

  vector<int> ans(n);
  int ptr = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < starts[i]; j++) {
      segs.insert(i);
    }
    for (int x : ends[i]) {
      segs.erase(segs.find(x));
    }
    while (ptr < i && (segs.empty() || ptr < *segs.begin())) {
      cnt[ans[ptr]]--;
      if (cnt[ans[ptr]] == 0) {
        valid.insert(ans[ptr]);
      }
      ptr++;
    }
    ans[i] = *valid.begin();
    cnt[ans[i]]++;
    valid.erase(valid.begin());
  }

  for (int i = 0; i < n; i++) {
    printf("%d ", ans[i]);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();

  return 0;
}
