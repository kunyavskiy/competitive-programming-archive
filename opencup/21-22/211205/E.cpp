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
  int n, k;
  scanf("%d%d", &n, &k);
  vector<vector<int>> ev(n);
  vector<int> eptr(n);
  vector<vector<int>> people;
  vector<char> isOk;
  vector<set<int>> canBeIll;
  set<int> ill;
  for (int i = 0; i < n; i++) {
    ill.insert(i);
  }
  int shift = 0;
  auto decode = [&] {
    int a;
    scanf("%d", &a);
    return (a + shift - 1) % n;
  };
  auto output = [&](int val) {
    if (val == -1) {
      printf("TAK\n");
      shift = 0;
    } else {
      printf("NIE %d\n", val + 1);
      shift = val + 1;
    }
  };
  for (int it = 0; it < k; it++) {
    char c;
    scanf(" %c", &c);
    if (c == 'K') {
      int cnt;
      scanf("%d", &cnt);
      vector<int> v(cnt);
      for (int i = 0; i < cnt; i++) {
        v[i] = decode();
      }
      int bads = count_if(v.begin(), v.end(), [&](int x) { return ill.count(x);});
      if (bads == 0) continue;
      std::set<int> badSet;
      for (int x : v) {
        if (!ill.insert(x).second) {
          badSet.insert(x);
        }
        ev[x].push_back(people.size());
      }
      people.push_back(std::move(v));
      isOk.push_back(false);
      canBeIll.push_back(std::move(badSet));
    } else if (c == 'P') {
      int x = decode();
      ill.erase(x);
    } else if (c == 'N') {
      int x = decode();
      queue<int> q;
      auto make_ok = [&](int p, int x) {
        int &i = eptr[p];
        while (i < (int)ev[p].size() && ev[p][i] <= x) {
          if (!isOk[ev[p][i]]) {
            isOk[ev[p][i]] = true;
            q.push(ev[p][i]);
          }
          i++;
        }
        if (i == (int)ev[p].size()) {
          ill.erase(p);
        } else {
          canBeIll[ev[p][i]].erase(p);
          if (canBeIll[ev[p][i]].empty()) {
            isOk[ev[p][i]] = true;
            q.push(ev[p][i]);
          }
        }
      };
      make_ok(x, numeric_limits<int>::max());
      while (!q.empty()) {
        int e = q.front();
        q.pop();
        for (int p : people[e]) {
          make_ok(p, e);
        }
      }
    } else if (c == 'Q') {
      int x = decode();
      auto iter = ill.lower_bound(x);
      int ans;
      if (iter != ill.end()) {
        ans = *iter;
      } else if (!ill.empty()) {
        ans = *ill.begin();
      } else {
        ans = -1;
      }
      output(ans);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
