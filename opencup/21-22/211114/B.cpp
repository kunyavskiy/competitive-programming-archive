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

const int MAXN = 1.1e6;

char s_[MAXN];
char t_[MAXN];

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    scanf("%s%s", s_, t_);
    vector<int> s[2];
    s[0].resize(n);
    s[1].resize(n);
    for (int i = 0; i < n; i++) {
      s[0][i] = s_[i] - '0';
      s[1][i] = t_[i] - '0';
    }
    set<int> n9;
    n9.insert(n);
    for (int i = 0; i < n; i++) {
      if (s[0][i] + s[1][i] != 9) {
        n9.insert(i);
      }
    }
    auto get_carry = [&](int pos) {
      int nxt = *n9.upper_bound(pos);
      return nxt != n && s[0][nxt] + s[1][nxt] >= 10;
    };
    for (int i = 0; i < q; i++) {
      int r, c, d;
      scanf("%d%d%d", &r, &c, &d);
      --c; --r;
      int ans2 = 0;
      if (s[r][c] != d) ans2++;
      int old_value = s[0][c] + s[1][c] + get_carry(c);
      if (s[0][c] + s[1][c] == 9) n9.insert(c);
      s[r][c] = d;
      if (s[0][c] + s[1][c] == 9) n9.erase(c);
      int new_value = s[0][c] + s[1][c] + get_carry(c);
      int ans1 = new_value % 10;
      ans2 += (old_value % 10 != new_value % 10);
      if (old_value / 10 != new_value / 10) {
        auto prev = n9.lower_bound(c);
        int prev_pos;
        if (prev == n9.begin()) {
          prev_pos = 0;
        } else {
          --prev;
          prev_pos = *prev;
        }
        ans2 += c - prev_pos;
      }
      printf("%d %d\n", ans1, ans2);
    }
  }

  return 0;
}
