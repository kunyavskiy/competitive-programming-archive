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
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n;
    scanf("%d", &n);
    vector<vector<int>> a(n, vector<int>(n)), b(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        a[i][j] = i;
        b[i][j] = n - 1 - j;
      }
    }

    struct pt {
      int x, y, z;
    };
    vector<vector<pair<pt, pt>>> ans(n, vector<pair<pt, pt>>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - i; j++) {
        pt p1 = pt({i, j, 0});
        pt p2 = pt({i, j, 1});
        assert(a[i][j] <= b[i][j]);
        ans[a[i][j]][b[i][j]] = {p1, p2};
      }
    }

    cout << "Case #" << test << ":" << endl;
    cout << "YES" << endl;
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        cout << i+1 << " " << j+1;
        cout << " " << ans[i][j].first.x << " " << ans[i][j].first.y << " " << ans[i][j].first.z;
        cout << " " << ans[i][j].second.x << " " << ans[i][j].second.y << " " << ans[i][j].second.z;
        cout << endl;
      }
    }
  }

  return 0;
}
