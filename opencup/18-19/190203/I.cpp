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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, k, p;
  while (scanf("%d%d%d", &n, &k, &p) == 3) {
    vector<vector<int>> v(n, vector<int>(k));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < k; j++) {
        int x;
        scanf("%d", &x);
        v[i][x - 1] = j;
      }
    }

    auto better = [&](int x, int y) {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        cnt += v[i][x] < v[i][y];
      }
      return 2 * cnt > n;
    };

    vector<vector<int>> cur;
    cur.push_back(vector<int>());
    cur[0].push_back(0);

    const int BUBEN = 400;
    auto rebuild = [&](int size) {
      vector<int> all;
      for (const auto &x:cur) {
        all.insert(all.end(), x.begin(), x.end());
      }
      cur = vector<vector<int>>();
      for (int j = 0; j < (int) all.size(); j += size) {
        cur.push_back(vector<int>(all.begin() + j, all.begin() + min(j + size, (int) all.size())));
      }
    };

    for (int i = 1; i < k; i++) {
      if (i % BUBEN == 0) {
        rebuild(BUBEN);
      }
      if (better(cur.back().back(), i)) {
        cur.back().push_back(i);
      } else {
        for (auto &x : cur) {
          if (better(i, x[0])) {
            x.insert(x.begin(), i);
            break;
          }
          if (better(i, x.back())) {
            for (int j = 0;; j++) {
              if (better(x[j], i) && better(i, x[j + 1])) {
                x.insert(x.begin() + j + 1, i);
                break;
              }
            }
            break;
          }
        }
      }
    }
    rebuild(p);
    for (int x : cur[0]) {
      printf("%d ", x + 1);
    }
    printf("\n");
  }


  return 0;
}
