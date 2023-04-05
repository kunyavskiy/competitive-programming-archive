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
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    static char s[310'000];
    scanf("%s", s);
    const char names[] = {'L', 'R', 'U', 'D'};
    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, 1, -1};

    auto to_id = [&](char c) {
      return find(names, names + 4, c) - names;
    };

    vector<int> sdx(n + 1), sdy(n + 1);
    for (int i = 0; i < n; i++) {
      int id = to_id(s[i]);
      sdx[i + 1] = sdx[i] + dx[id];
      sdy[i + 1] = sdy[i] + dy[id];
    }

    vector<vector<pair<int, int>>> ans(n+1, vector<pair<int, int>>(4));
    for (int i = 0; i < 4; i++) {
      ans[n][i] = {dx[i], dy[i]};
    }

    map<pair<int, int>, int> last;

    for (int i = n - 1; i >= 0; i--) {
      last[{sdx[i + 1], sdy[i + 1]}] = i;
      for (int j = 0; j < 4; j++) {
        auto it = last.find({sdx[i] - dx[j], sdy[i] - dy[j]});
        if (it == last.end()) {
          ans[i][j] = {sdx.back() - sdx[i] + dx[j], sdy.back() - sdy[i] + dy[j]};
        } else {
          ans[i][j] = ans[it->second + 1][to_id(s[it->second]) ^ 1];
        }
      }
    }

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      auto it = last.find({-x, -y});
      pair<int, int> res;
      if (it == last.end()) {
        res = {sdx.back() + x, sdy.back() + y};
      } else {
        res = ans[it->second + 1][to_id(s[it->second]) ^ 1];
      }
      printf("%d %d\n", res.first, res.second);
    }
  }

  return 0;
}
