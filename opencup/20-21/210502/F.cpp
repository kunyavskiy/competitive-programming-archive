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

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n[2];
  while (scanf("%d%d", &n[0], &n[1]) == 2) {
    vector<bool> attacted[2];

    map<int, vector<pair<int, pair<int, int>>>> by[2];
    for (int p = 0; p < 2; p++) {
      for (int i = 0; i < n[p]; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        by[0][x].push_back({y, {p, i}});
        by[1][y].push_back({x, {p, i}});
      }
    }

    string used[2];
    used[0] = string(n[0], '0');
    used[1] = string(n[1], '0');

    for (auto &mp : by) {
      for (auto &[_, rks] : mp) {
        int last_p = -1, last_id = -1;
        sort(rks.begin(), rks.end());
        for (auto &[_, rk] : rks) {
          auto &[p, id] = rk;
          if (p != last_p && last_p != -1) {
            used[p][id] = '1';
            used[last_p][last_id] = '1';
          }
          last_p = p;
          last_id = id;
        }
      }
    }

    printf("%s\n%s\n", used[0].c_str(), used[1].c_str());
  }

  return 0;
}
