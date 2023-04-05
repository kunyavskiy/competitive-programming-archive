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
#include <numeric>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

struct state {
  int day;
  int meet;
  vector<int> done;
  vector<int> ndone;

  bool operator<(const state &rhs) const {
    return std::tie(day, meet, done, ndone) < std::tie(rhs.day, rhs.meet, rhs.done, rhs.ndone);
  }

};

vector<int> cnt;
set<state> seen;
int ans, n;

void solve(state s) {
  if (ans == n) return;
  if (s.meet == 0) {
    s.done.insert(s.done.end(), s.ndone.rbegin(), s.ndone.rend());
    s.ndone.clear();
    s.day++;

    if (s.day == (int)cnt.size()) {
      ans = max<int>(ans, count(s.done.begin(), s.done.end(), 1));
      return;
    } else {
      s.meet = cnt[s.day];
      reverse(s.done.begin(), s.done.end());
      swap(s.done, s.ndone);
    }
  }
  if (s.ndone.empty()) {
    return;
  }
  if (accumulate(s.ndone.begin(), s.ndone.end(), 0) < s.meet) {
    return;
  }
  if (seen.count(s)) {
    return;
  }
  seen.insert(s);
  int last = s.ndone.back();
  s.ndone.pop_back();
  for (int i = 0; i <= s.meet && i <= last; i++) {
    vector<int> done = s.done;
    if (i) done.insert(lower_bound(done.begin(), done.end(), i), i);
    if (last - i) done.insert(lower_bound(done.begin(), done.end(), last - i), last - i);
    solve({s.day, s.meet - i, std::move(done), s.ndone});
  }
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int m;
  while (scanf("%d%d", &n, &m) == 2) {
    ans = 0;
    cnt = vector<int>(m);
    for (int &x : cnt) {
      scanf("%d", &x);
    }
    seen.clear();
    solve({0, cnt[0], {}, {n}});
    printf("%d\n", ans);
    eprintf("%d\n", (int)seen.size());
  }


  return 0;
}
