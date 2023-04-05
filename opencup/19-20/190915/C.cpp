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
//#undef LOCAL

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

vector<vector<int>> a;
int n;

int init() {
#ifdef LOCAL
  cin >> n;
  a.resize(n, vector<int>(n));
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> a[i][j];
  return n;
#else
  cin >> n;
  return n;
#endif
}

int best_x = 0, best_y = 0, best_val = -1;
int qr = 0;
int ask(int x, int y) {
  if (!(0 <= x && x < n && 0 <= y && y < n)) {
    return -1;
  }
  static map<pair<int, int>, int> mp;
  if (mp.count({x, y})) return mp[{x, y}];
  qr++;
  assert(qr <= 3 * n + 210);

  int z;
#ifdef LOCAL
  z = a[x][y];
#else
  cout << "? " << x + 1 << " " << y + 1 << endl;
  cin >> z;
#endif
  if (best_val < z) {
    best_val = z;
    best_x = x;
    best_y = y;
  }
  mp[{x, y}] = z;
  return z;
}

void answer(int x, int y) {
  db(qr);
  db2(x, y);
#ifdef LOCAL
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) assert(a[i][j] <= a[x][y]);
#else
  cout << "! " << x + 1 << " " << y + 1 << endl;
#endif
}

void solve() {
  int n = init();

  int lx = 0, rx = n - 1;
  int ly = 0, ry = n - 1;
  while (1) {
    db2(lx, rx);
    db2(ly, ry);
    if (rx - lx >= ry - ly) {
      int mx = (lx + rx) / 2;

      vector<pair<int, pair<int, int>>> vct;
      for (int y = ly; y <= ry; y++) {
        vct.push_back({ask(mx, y), {mx, y}});
      }
      sort(vct.begin(), vct.end());
      reverse(vct.begin(), vct.end());
//      for (auto o : vct) db3(o.first, o.second.first, o.second.second);

      int x = vct[0].second.first, y = vct[0].second.second;
//      db2(x, y);
      for (int dx = -1; dx <= 1; dx += 1) {
        for (int dy = -1; dy <= 1; dy += 1) {
          ask(x+dx, y+dy);
        }
      }
//      db3(best_x, best_y, best_val);
      if (best_x < x) {
        rx = x - 1;
      } else if (best_x > x) {
        lx = x + 1;
      } else {
        answer(best_x, best_y);
        return;
      }
    } else {
      int my = (ly + ry) / 2;

      vector<pair<int, pair<int, int>>> vct;
      for (int x = lx; x <= rx; x++) {
        vct.push_back({ask(x, my), {x, my}});
      }
      sort(vct.begin(), vct.end());
      reverse(vct.begin(), vct.end());
//      for (auto o : vct) db3(o.first, o.second.first, o.second.second);

      int x = vct[0].second.first, y = vct[0].second.second;
//      db2(x, y);
      for (int dx = -1; dx <= 1; dx += 1) {
        for (int dy = -1; dy <= 1; dy += 1) {
          ask(x+dx, y+dy);
        }
      }
//      db3(best_x, best_y, best_val);

      if (best_y < y) {
        ry = y - 1;
      } else if (best_y > y) {
        ly = y + 1;
      } else {
        answer(best_x, best_y);
        return;
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
#endif

  solve();

  return 0;
}
