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

vector<bool> used;
vector<bool> anyused;
vector<vector<int>> order;
int n, m;

void go(int mask) {
  if (mask == (1 << m) - 1) {
    return;
  }
  for (int i = 0; i < m; i++) {
    if (!(mask & (1 << i))) {
      int x = *find_if(order[i].begin(), order[i].end(), [](int x) { return !used[x]; });
      anyused[x] = true;
      used[x] = true;
      go(mask | (1 << i));
      used[x] = false;
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  while (scanf("%d%d", &n, &m) == 2) {
    order = vector<vector<int>>(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &order[i][j]);
        --order[i][j];
      }
    }
    used = vector<bool>(n);
    anyused = vector<bool>(n);
    go(0);
    vector<int> good;
    for (int i = 0; i < n; i++) {
      if (anyused[i]) {
        good.push_back(i);
      }
    }
    printf("%d\n", (int)good.size());
    for (int x : good) {
      printf("%d ", x+1);
    }
    printf("\n");
  }

  return 0;
}
