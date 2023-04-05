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

#define all(a) (a).begin(), (a).end()

typedef long long ll;
typedef long double ld;

struct pt {
  int x, y;
};

const ll INF18 = 1e18;

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  vector<pt> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &p[i].x, &p[i].y);
  }
  vector<pair<int,int>> ox;
  vector<pair<int,int>> oy;
  set<pair<int,int>> sxy, sx, sy;

  for (int i = 0; i < n; i++) {
    sxy.insert({p[i].x + p[i].y, i});
    ox.push_back({p[i].x, i});
    oy.push_back({p[i].y, i});
  }
  sort(all(ox));
  sort(all(oy));



  ll ans = 0;
  vector<int> perm;
  int X = 1;
  int Y = 1;
  int cx = 0;
  int cy = 0;
  for (int i = 0; i < n; i++) {
    for (; cx < (int)ox.size() && ox[cx].first <= X; cx++) {
      int id = ox[cx].second;
      int s = p[id].x + p[id].y;
      assert(sxy.erase({s, id}));
      sy.insert({p[id].y, id});
    }

    for (; cy < (int)oy.size() && oy[cy].first <= Y; cy++) {
      int id = oy[cy].second;
      int s = p[id].x + p[id].y;
      assert(sxy.erase({s, id}));
      sx.insert({p[id].x, id});
    }

    ll best = INF18;
    int where = -1;
    if (!sxy.empty() && sxy.begin()->first - (X + Y) < best) {
      best = sxy.begin()->first - (X + Y);
      where = sxy.begin()->second;
    }

    if (!sx.empty() && sx.begin()->first - X < best) {
      best = sx.begin()->first - X;
      where = sx.begin()->second;
    }

    if (!sy.empty() && sy.begin()->first - Y < best) {
      best = sy.begin()->first - Y;
      where = sy.begin()->second;
    }
    ans = min(ans, best);

    perm.push_back(where);
    sxy.erase({p[where].x + p[where].y, where});
    sx.erase({p[where].x, where});
    sy.erase({p[where].y, where});
  }
  db(ans);

  for (auto x: perm) {
    printf("%d ", x + 1);
  }
  puts("");


  return 0;
}
