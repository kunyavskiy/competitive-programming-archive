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

  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> total(n);
  vector<vector<int>> data(k, vector<int>(n));
  for (auto& x : data) {
    for (int i = 0; i < n; i++) {
      scanf("%d", &x[i]);
      total[i] += x[i];
    }
  }

  if (k == 2) {
    printf("%d\n", 2);
    printf("%d %d\n", 1, 2);
    printf("%d %d\n", 2, 3);
    return 0;
  }

  vector<pair<int, int>> res;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      double ans = 0;
      for (const auto&d : data) {
        ans += (d[i] - total[i] *1.0/ k) * (d[j] - total[j] * 1.0 / k);
      }
      if (ans > k / 8.0) {
        res.emplace_back(i, j);
      }
    }
  }

  printf("%d\n", (int)res.size());
  for (auto x : res) {
    printf("%d %d\n", x.first + 1 , x.second + 1);
  }

  return 0;
}
