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


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<string> s;
    vector<map<int, vector<int>>> cnts(26);
    for (int i = 0; i < n; i++) {
      static char buf[1'100'100];
      scanf("%s", buf);
      s.emplace_back(buf);
      reverse(s.back().begin(), s.back().end());
    }
    sort(s.begin(), s.end());

    for (char c = 'a'; c <= 'z'; c++) {
      for (int i = 0; i < n; i++) {
        int cnt = std::count(s[i].begin(), s[i].end(), c);
        cnts[c - 'a'][cnt].push_back(i);
      }
    }

    ll ans = 0;

    for (const auto &a : s) {
      string x = a.substr(0, a.size() - 1);
      int l = lower_bound(s.begin(), s.end(), x + 'a') - s.begin();
      int r = lower_bound(s.begin(), s.end(), x + char('z' + 1)) - s.begin();

      int bad = 0;
      int bad_cnt = std::count(x.begin(), x.end(), a.back());
      auto it = cnts[a.back() - 'a'].find(bad_cnt);
      if (it != cnts[a.back() - 'a'].end()) {
        bad = lower_bound(it->second.begin(), it->second.end(), r) -
              lower_bound(it->second.begin(), it->second.end(), l);
      }
      ans += r - l - bad - 1;
    }

    printf("%lld\n", ans);
  }

  return 0;
}
