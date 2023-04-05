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

vector<int> g[100003];
set<int> s[100003];

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) {
    int x;
    scanf("%d", &x);
    g[x].push_back(i);
  }
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  ll res = 0;
  for (int i = n - 1; i >= 0; i--) {
    int best = -1;
    for (int j : g[i]) {
      if (best == -1 || s[j].size() > s[best].size()) best = j;
    }
    if (best != -1)
      s[i].swap(s[best]);
    for (int j : g[i]) {
//      cout << i << "->" << j << endl;
      if (j == best) continue;
      for (int x : s[j]) {
        if (s[i].find(x) == s[i].end()) {
          s[i].insert(x);
        } else {
          s[i].erase(x);
        }
      }
    }
    {
      int x = i;
      if (s[i].find(x) == s[i].end()) {
        s[i].insert(x);
      } else {
        s[i].erase(x);
      }
    }
    {
      int x = a[i];
      if (s[i].find(x) == s[i].end()) {
        s[i].insert(x);
      } else {
        s[i].erase(x);
      }
    }
//    cout << i;
//    for (int x : s[i]) {
//      cout << " " << x;
//    }
//    cout << endl;
    res += s[i].size();
  }

  cout << res / 2 << endl;

  return 0;
}
