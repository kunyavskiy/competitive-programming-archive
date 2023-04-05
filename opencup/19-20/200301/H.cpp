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

int solve(string a, string b, string c) {
//  eprintf("====\n%s %s %s\n", a.c_str(), b.c_str(), c.c_str());
  c = c + c;
  int ans = numeric_limits<int>::max();
  int n = (int) b.size();
  for (int it = 0; it < n; it++) {
    string req(n, '0');
    for (int i = 0; i < n; i++) {
      if (a[i] == b[i]) {
        break;
      }
      req[i] = 'A' + 'B' + 'C' - a[i] - b[i];
    }
    if (req.back() != '0') {
      vector<int> p(n);
      auto fixp = [&](int &j, char ch) {
        while (j && req[j] != ch) {
          j = p[j - 1];
        }
        if (req[j] == ch) j++;
      };
      auto norm = [&](int x) {
        return min(x, n - x);
      };
      for (int i = 1; i < n; i++) {
        fixp(p[i] = p[i - 1], req[i]);
      }
      int pos = 0;
      for (int i = 0; i < 2 * n; i++) {
        fixp(pos, c[i]);
        if (pos == n) {
//          eprintf("%d %d %d\n", it, i - n + 1, norm(it) + norm(i - n + 1));
          ans = min(ans, norm(it) + norm(i - n + 1));
        }
      }
    }
    rotate(b.begin(), b.begin() + 1, b.end());
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif
  
  string a, b, c;
  while (cin >> a >> b >> c) {
    int ans1 = solve(a, b, c);
    int ans2 = solve(b, a, c);
    int ans3 = solve(c, b, a);
    int ans = min(ans1, min(ans2, ans3));
    if (ans == numeric_limits<int>::max()) {
      printf("-1\n");
    } else {
      printf("%d\n", ans);
    }
  }

  return 0;
}
