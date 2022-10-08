#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

const int MAXN = 1100;

int g[MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n);
    std::iota(a.begin(), a.end(), 0);
    std::iota(b.begin(), b.end(), 0);
    mt19937 rnd(239239);
    while (true) {
      shuffle(a.begin(), a.end(), rnd);
      shuffle(b.begin(), b.end(), rnd);
      bool bad = false;
      for (int i = 0; i < n; i++) {
        vector<int> d(n, numeric_limits<int>::max());
        queue<int> q;
        q.push(i);
        d[i] = 0;
        while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (int u : {a[v], b[v]}) {
            if (d[u] > d[v] + 1) {
              d[u] = d[v] + 1;
              q.push(u);
            }
          }
        }
        if (*max_element(d.begin(), d.end()) > 4) {
//          eprintf("max[%d] = %d\n", i, *max_element(d.begin(), d.end()));
          bad = true;
          break;
        }
      }
      if (!bad) break;
    }
    for (int i = 0; i < n; i++) {
      printf("%d %d\n", a[i] + 1, b[i] + 1);
    }
  }


  return 0;
}
