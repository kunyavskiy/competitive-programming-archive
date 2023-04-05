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
  freopen("p5.in", "r", stdin);
  freopen("p5.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  int tm[6][6];
  memset(tm,0,sizeof(tm));
  multiset<int> s[2];
  multiset<int> l[2];
  int cur_time = 0;


  struct event {
    int ty;
    int tm, team;
  };

  vector<event> events;

  for (int i = 0; i < n; i++) {
    int m, sec, ss;
    scanf("%d:%d.%d", &m, &sec, &ss);
    int t = (m * 60 + sec) * 10 + ss;
    int team;
    scanf("%d", &team);
    --team;
    char name[100];
    scanf(" %s", name);
    if (name == string("minor")) {
      events.push_back({0, t, team});
    } else if (name == string("major")) {
      events.push_back({1, t, team});
    } else if (name == string("goal")) {
      events.push_back({2, t, !team});
    }
  }
  int fin = 60 * 60 * 10;
  for (int i = 0; cur_time < fin; ) {
    int next = fin;
    if (i < (int)events.size()) next = min(next, events[i].tm);
    if (!s[0].empty()) next = min(next, *s[0].begin());
    if (!s[1].empty()) next = min(next, *s[1].begin());
    if (!l[0].empty()) next = min(next, *l[0].begin());
    if (!l[1].empty()) next = min(next, *l[1].begin());

    int cnt1 = 5 - s[0].size() - l[0].size();
    int cnt2 = 5 - s[1].size() - l[1].size();
    //eprintf("%02d:%02d.%d..%02d:%02d.%d %dx%d\n", cur_time / 600, cur_time % 600 / 10, cur_time % 10,
    //        next / 600, next % 600 / 10, next % 10, cnt1, cnt2);
    tm[cnt1][cnt2] += (next - cur_time);
    cur_time = next;
    if (i < (int)events.size() && next == events[i].tm) {
      int team = events[i].team;
      if (events[i].ty == 0) {
        s[team].insert(next + 2 * 60 * 10);
      } else if (events[i].ty == 1) {
        l[team].insert(next + 5 * 60 * 10);
      } else if (events[i].ty == 2) {
        if (!s[team].empty() && (s[team].size() + l[team].size() > s[!team].size() + l[!team].size())) {
          s[team].erase(s[team].begin());
        }
      }
      i++;
    }
    else if (!s[0].empty() && *s[0].begin() == next) s[0].erase(s[0].begin());
    else if (!s[1].empty() && *s[1].begin() == next) s[1].erase(s[1].begin());
    else if (!l[0].empty() && *l[0].begin() == next) l[0].erase(l[0].begin());
    else if (!l[1].empty() && *l[1].begin() == next) l[1].erase(l[1].begin());
  }

  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j <= 5; j++) {
      if (tm[i][j] > 0) {
        int min = tm[i][j] / 600;
        int sec = tm[i][j] % 600 / 10;
        int ss = tm[i][j] % 10;
        printf("%dx%d %02d:%02d.%d\n", i, j, min, sec, ss);
      }
    }
  }

  return 0;
}
