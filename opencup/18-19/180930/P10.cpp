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
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int w, h;
  static char buf[3];


  scanf("%d%d", &w, &h);

  vector<vector<string>> m(w, vector<string>(h));
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      scanf("%s", buf);
      m[x][y] = buf;
    }
  }

  int r;
  scanf("%d", &r);

  set<pair<pair<int, int>, pair<int, int>>> river;

  for (int i = 0; i < r; i++) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    river.insert({{x1, y1}, {x2, y2}});
    river.insert({{x2, y2}, {x1, y1}});
  }

  int M;
  scanf("%d", &M);

  int x1, y1, x2, y2;
  scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

  vector<vector<pair<int, int>>> d(w, vector<pair<int, int>>(h, {1000000000, 1000000000}));
  vector<vector<pair<int, int>>> prev(w, vector<pair<int, int>>(h, {-1, -1}));

  d[x1][y1] = {0, 0};

  set<pair<pair<int, int>, pair<int, int>>> s;
  s.insert({d[x1][y1], {x1, y1}});

  while (!s.empty()) {
    auto p = *(s.begin());
    s.erase(p);
    int x = p.second.first;
    int y = p.second.second;
    const int dx[] = {-1, -1, 0, 0, 1, 1};
    const int dy[] = {-1, 0, -1, 1, 0, 1};
    for (int i = 0; i < 6; i++) {
      int xx = x + dx[i];
      int yy = y + dy[i];
      if (xx >= 0 && xx < w && yy >= 0 && yy < h) {
        if (m[xx][yy][0] == 'm') continue;
        int D = 1;
        if (m[x][y][0] == 'p' && m[xx][yy][0] == 'h') D++;
        if (m[xx][yy][1] == 'f' || m[xx][yy][1] == 'm') D++;
        if (river.count({{x, y}, {xx, yy}})) {
          D = M;
        }
        pair<int, int> nd;
        if (d[x][y].second >= M) {
          nd = {d[x][y].first + 1, D};
        } else {
          nd = {d[x][y].first, d[x][y].second + D};
        }
        if (d[xx][yy] > nd) {
          s.erase({d[xx][yy], {xx, yy}});
          d[xx][yy] = nd;
          prev[xx][yy] = {x, y};
          s.insert({d[xx][yy], {xx, yy}});
        }
      }
    }
  }

  if (d[x2][y2].first == 1000000000) {
    cout << "They shall not pass\n";
  } else {
    cout << "Come this way\n";
    cout << d[x2][y2].first + 1 << "\n";
    vector<pair<int, int>> path;
    pair<int, int> cur = {x2, y2};
    while (cur != make_pair(-1, -1)) {
      path.push_back(cur);
      cur = prev[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    cout << path.size() << "\n";
    for (auto p : path) {
      cout << p.first << " " << p.second << "\n";
    }
  }

  return 0;
}
