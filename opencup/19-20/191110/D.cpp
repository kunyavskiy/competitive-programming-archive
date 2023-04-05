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

int subsolve(vector<int> r, vector<int> s) {
  int n = r.size();

  multiset<int> st;
  vector<vector<int>> ev(n);

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    for (int id : ev[i]) {
      st.erase(st.find(s[id]));
    }
    st.insert(s[i]);
    if (i + r[i] + 1 < n) {
      ev[i + r[i] + 1].push_back(i);
    }

    if (st.size() > 1) {
      auto it = st.end();
      ans[i] += *--it;
      ans[i] += *--it;
    }
  }

  st.clear();
  ev.assign(n, vector<int>());
  for (int i = n - 1; i >= 0; i--) {
    for (int id : ev[i]) {
      st.erase(st.find(s[id]));
    }

    if (st.size() > 0) {
      auto it = st.end();
      ans[i] += *--it;
    }
    st.insert(s[i]);
    if (i - r[i] - 1 >= 0) {
      ev[i - r[i] - 1].push_back(i);
    }
  }
//  dbv(ans);
  int res = 0;
  for (int i = 1; i < n - 1; i++) res = max(res, ans[i]);
  return res;
}

int solve(vector<int> r, vector<int> s) {
  int ans = subsolve(r, s);
  reverse(r.begin(), r.end());
  reverse(s.begin(), s.end());
  ans = max(ans, subsolve(r, s));
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<int> r(n), s(n);
    for (int i = 0; i < n; i++) scanf("%d%d", &r[i], &s[i]);

    printf("%d\n", solve(r, s));
  }

  return 0;
}
