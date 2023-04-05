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
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    map<int, vector<pair<int, int>>> mp1, mp2;
    
    struct Event {
      int x;
      int type;
      int y, add;
      int l, r;
      
      bool operator< (const Event &e) const {
        if (x != e.x) return x < e.x;
        return type < e.type;
      }
    };
    vector<Event> ev;
    
    for (int i = 0; i < n; i++) {
      int x1, y1, x2, y2;
      scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
      
      mp1[y1].push_back({x1, x2 - 1});
      ev.push_back({x1, 0, y1, +1, 0, 0});
      ev.push_back({x2, 0, y1, -1, 0, 0});

      mp2[x2].push_back({y1, y2 - 1});
      ev.push_back({x2, 1, 0, 0, y1, y2 - 1});
      
      mp1[y2].push_back({x1 + 1, x2});
      ev.push_back({x1 + 1, 0, y2, +1, 0, 0});
      ev.push_back({x2, 0, y2, -1, 0, 0});
      
      mp2[x1].push_back({y1 + 1, y2});
      ev.push_back({x1, 1, 0, 0, y1 + 1, y2});
    }
    
    bool any = 0;
    
    auto solve = [&](vector<pair<int, int>> v) {
      sort(v.begin(), v.end());
      for (int i = 1; i < (int)v.size(); i++) {
        if (v[i - 1].second >= v[i].first) {
          return true;
        }
      }
      return false;
    };

    for (auto it : mp1) {
      any |= solve(it.second);
      if (any) break;
    }
    for (auto it : mp2) {
      any |= solve(it.second);
      if (any) break;
    }
    sort(ev.begin(), ev.end());
    
    multiset<int> st;
    
    for (auto cur : ev) {
      if (cur.type == 0) {
        if (cur.add == +1) {
          st.insert(cur.y);
        } else {
          st.erase(st.find(cur.y));
        }
      } else {
        auto it = st.lower_bound(cur.l);
        if (it != st.end() && *it <= cur.r) {
          any = 1;
          break;
        }
      }
    }
    cout << (int)any << endl;
  }

  return 0;
}
