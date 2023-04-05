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

vector<int> readVector() {
  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }
  sort(v.begin(), v.end());
  return v;
}

const int INF = (1 << 30);

int solve(int n, int s, int i, const vector<int> &order,
          vector<int> & p0,
          vector<int> & p1,
          vector<int> & pick0, vector <int> &pick1) {
  if (i == int(order.size())) {
    return 0;
  }
  int team = (order[i] < n ? 0 : 1);
  int ans = team == 0 ? -INF : INF;
  int num = order[i];
  eprintf("i %d num %d team %d\n", i, num, team);
  if (pick0[num] < s) {
    assert(!p0.empty());
    pick0[num] += 1;
    int w = p0.back();
    p0.pop_back();
    int cur = (team == 0 ? w : -w) + solve(n, s, i + 1, order, p0, p1, pick0, pick1);
    if (team == 0) {
      ans = max(ans, cur);
    } else {
      ans = min(ans, cur);
    }
    p0.push_back(w);
    pick0[num] -= 1;
  }
  if (pick1[num] < 1) {
    assert(!p1.empty());
    pick1[num] += 1;
    int w = p1.back();
    p1.pop_back();
    int cur = (team == 0 ? w : -w) + solve(n, s, i + 1, order, p0, p1, pick0, pick1);
    if (team == 0) {
      ans = max(ans, cur);
    } else {
      ans = min(ans, cur);
    }
    p1.push_back(w);
    pick1[num] -= 1;
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, s;
  scanf("%d%d", &n, &s);
  vector <int> order(2 * n * (s + 1));
  for (int i = 0; i < 2 * n * (s + 1); ++i) {
    scanf("%d", &order[i]);
    --order[i];
  }
  vector <int> p0 = readVector();
  vector <int> p1 = readVector();
  vector <int> pick0(2 * n, 0), pick1(2 * n, 0);
  printf("%d\n", solve(n, s, 0, order, p0, p1, pick0, pick1));
  return 0;
}
