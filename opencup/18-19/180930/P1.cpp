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

char s[102];

void solve_test() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s", s);
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0;i < n; i++) {
    for (int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int x = i;
      int y = j;
      int res = a[x][y];
      for (int k = 0; s[k]; k++) {
        char c = s[k];
        if (c == 'U') x--;
        if (c == 'D') x++;
        if (c == 'L') y--;
        if (c == 'R') y++;
        if (x < 0 || x >= n || y < 0 || y >= m) {
          res = 0;
          break;
        }
        res += a[x][y];
      }
      cout << res << " ";
    }
    cout << "\n";
  }

}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);


  int n;
  scanf("%d", &n);
  for  (int i= 0; i < n; i++) solve_test();

  return 0;
}
