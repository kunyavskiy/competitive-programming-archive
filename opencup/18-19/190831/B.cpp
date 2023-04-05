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

struct automaton {
  vector<int> b;
  vector<int> next[2];
  int start;
};

map<vector<int>, vector<int>> test_id;
vector<automaton> ans;

void update(int t, const automaton& cur) {
  if (ans[t].b.empty() || ans[t].b.size() > cur.b.size()) {
    ans[t] = cur;
  }
}

void match(automaton cur) {
  vector<int> vals;
  for (int i = 0; i < 8; i++) {
    int v = cur.start;
    while (cur.b[v] != -1) {
      v = cur.next[(i >> cur.b[v]) & 1][v];
    }
    vals.push_back(v);
    auto it = test_id.find(vals);
    if (it != test_id.end()) {
      for (int t : it->second) {
        update(t, cur);
      }
    }
  }
}

void go(automaton cur) {
  {
    cur.start = cur.b.size() - 1;
    match(cur);
  }
  int sz = cur.b.size();
  if (sz == 6) {
    return;
  }

  cur.b.push_back(-1);
  cur.next[0].push_back(-1);
  cur.next[1].push_back(-1);
  for (int b = 0; b <= 2; b++) {
    for (int n1 = 0; n1 < sz; n1++) {
      for (int n2 = 0; n2 < sz; n2++) {
        cur.b.back() = b;
        cur.next[0].back() = n1;
        cur.next[1].back() = n2;
        go(cur);
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  ans.resize(t);
  for (int i = 0; i < t; i++) {
    int n;
    scanf("%d", &n);
    vector<int> v(n);
    for (int j = 0; j < n; j++) {
      scanf("%d", &v[j]);
    }
    test_id[v].push_back(i);
  }

  automaton start;
  start.b = {-1, -1};
  start.next[0] = {-1, -1};
  start.next[1] = {-1, -1};
  start.start = 0;
  match(start);
  go(start);

  for (auto &x : test_id) {
    automaton v = start;
    v.b.push_back(0);
    v.next[0].push_back(1);
    v.next[1].push_back(0);

    v.b.push_back(0);
    v.next[0].push_back(0);
    v.next[1].push_back(1);

    vector<int> need = x.first;
    while (need.size() < 8) {
      need.push_back(0);
    }

    int reorder[4] = {0, 2, 3, 1};

    v.b.push_back(1);
    v.next[0].push_back(reorder[need[0] + 2 * need[1]]);
    v.next[1].push_back(reorder[need[2] + 2 * need[3]]);

    v.b.push_back(1);
    v.next[0].push_back(reorder[need[4] + 2 * need[5]]);
    v.next[1].push_back(reorder[need[6] + 2 * need[7]]);

    v.b.push_back(2);
    v.next[0].push_back(4);
    v.next[1].push_back(5);

    v.start = v.b.size() - 1;

    match(v);
  }

  for (int i = 0; i < t; i++) {
    int s = ans[i].b.size();
    printf("%d\n", s);
    for (int j = 2; j < s; j++) {
      printf("%d %d %d\n", ans[i].b[j], ans[i].next[0][j], ans[i].next[1][j]);
    }
    printf("%d\n", ans[i].start);
  }

  return 0;
}
