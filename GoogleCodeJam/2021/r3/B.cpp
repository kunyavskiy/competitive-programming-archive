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

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

bool check(const vector<string>& s) {
  int r = s.size();
  int c = s[0].size();
  auto is_a = [&](int a, int b, char e) {
    return 0 <= a && a < r && 0 <= b && b < c && s[a][b] == e;
  };
  auto is_square = [&](int i, int j, int sz) {
    for (int t = 0; t < sz; t++) {
      if (!is_a(i + t, j + t, '\\')) return false;
      if (!is_a(i + t, j - 1 - t, '/')) return false;
      if (!is_a(i + 2 * sz - 1 - t, j + t, '/')) return false;
      if (!is_a(i + 2 * sz - 1 - t, j - 1 - t, '')) return false;
    }
    return true;
  };
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      for (int sz = 1; sz <= min(r, c); sz++) {
        if (is_square(i, j, sz)) return false;
      }
    }
  }
  return true;
}

bool go(int r, int c, vector<string>& s, vector<int>&rs, vector<int>&cs) {
  if (c == (int)cs.size()) {
    return rs[r] == 0 && go(r + 1, 0, s, rs, cs);
  }
  if (r == (int)rs.size()) {
    return all_of(cs.begin(), cs.end(), [](int x) { return x == 0; }) && check(s);
  }
  s[r][c] = '\\';
  if (go(r, c + 1, s, rs, cs)) return true;
  s[r][c] = '/';
  rs[r]--, cs[c]--;
  if (go(r, c + 1, s, rs, cs)) return true;
  rs[r]++, cs[c]++;
  return false;
}

void solve() {
  int r, c;
  scanf("%d%d", &r, &c);
  vector<int> rs(r), cs(c);
  for (int i = 0; i < r; i++) scanf("%d", &rs[i]);
  for (int i = 0; i < c; i++) scanf("%d", &cs[i]);

  vector<string> res(r, string(c, '?'));
  if (go(0, 0, res, rs, cs)) {
    printf("POSSIBLE\n");
    for (int i = 0; i < r; i++) {
      printf("%s\n", res[i].c_str());
    }
  } else {
    printf("IMPOSSIBLE\n");
  }


}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
