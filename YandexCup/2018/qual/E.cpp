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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<string> a(n);
  vector<string> b(m);
  for (string &x : a) {
    char buf[100];
    scanf("%s", buf);
    x = buf;
  }
  for (string &x : b) {
    char buf[100];
    scanf("%s", buf);
    x = buf;
  }

  set<string> have(b.begin(), b.end());
  map<string, int> cnt;

  ll ans = 0;
  int r = 0;

  for (int i = 0; i < n; i++) {
    while (r < n && (int)cnt.size() < m) {
      if (have.find(a[r]) != have.end()) {
        cnt[a[r]]++;
      }
      r++;
    }
    eprintf("%d %d %d\n", i, r, (int)cnt.size());
    if ((int)cnt.size() == m) {
      ans += n - r + 1;
    }
    cnt[a[i]]--;
    if (cnt[a[i]] <= 0) {
      cnt.erase(a[i]);
    }
  }

  printf("%lld\n", ans);

  return 0;
}
