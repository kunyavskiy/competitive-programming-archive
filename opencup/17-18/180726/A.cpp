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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> a(n);
  for (int i = 0; i < n; i++) {
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      int x;
      scanf("%d", &x);
      a[i].push_back(x - 1);
    }
  }
  vector<int> b(m, -1);
  for (int i = n - 1; i >= 0; i--) {
    for (int x : a[i]) {
      if (b[x] == -1) {
        b[x] = i;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (b[i] == -1) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  for (int i = 0; i < n; i++) {
    cout << i + 1 << " ";
  }
  cout << "\n";
  for (int i = 0; i < m; i++) {
    cout << b[i] + 1 << " ";
  }
  cout << "\n";

  return 0;
}
