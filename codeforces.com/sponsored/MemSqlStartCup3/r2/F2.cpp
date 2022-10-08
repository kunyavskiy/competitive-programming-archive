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

double d[65][21][21];
string s;
int r, c;

double solve(int pos, int a, int b) {
  if (a == r) {
    return 0;
  }
  if (b == r) {
    return 1;
  }
  double& ans = d[pos][a][b];
  if (ans > -0.5) {
    return ans;
  }
  int rr = 2 * r - a - b;
  int cc = 2 * c + 2 * r - pos - rr;
  if (cc < 0) {
    return ans = 0;
  }
  assert(rr > 0);
  double prob = rr * 1.0 / (rr + cc);
  if (s[pos] == 'A') {
    return ans = prob * solve(pos + 1, a + 1, b) + (1.0 - prob) * solve(pos + 1, a, b);
  } else {
    return ans = prob * solve(pos + 1, a, b + 1) + (1.0 - prob) * solve(pos + 1, a, b);
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  scanf("%d%d", &r, &c);
  s = string(r + c, 'A') + string(r + c, 'B');

  vector<pair<string, double>> v;
  do {
    for (int i = 0; i <= 2 * (r + c); i++)
      for (int j = 0; j <= r; j++)
        for (int k = 0; k <= r; k++) {
          d[i][j][k] = -1;
        }
    double score = 0.5 - solve(0,0,0);
    if (v.empty() || abs(v.back().second) > abs(score) + 1e-9) {
      v.clear();
    }
    if (v.empty() || abs(v.back().second) > abs(score) - 1e-9) {
      v.push_back({s, score});
    }
  } while (next_permutation(s.begin(), s.end()));

  for (auto x : v) {
    printf("%s %f\n", x.first.c_str(), 0.5 - x.second);
  }

  return 0;
}