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

vector<int> p;
vector<set<int>> s;

int get(int x) {
  if (p[x] == x) return x;
  return p[x] = get(p[x]);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, k, m;
  while (scanf("%d%d%d", &n, &k, &m) == 3) {
    p = vector<int>(n, 0);
    s = vector<set<int>>(n);
    for (int i = 0; i < n; i++) {
      p[i] = i;
    }

    for (int i = 0; i < k; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      s[a].insert(b);
      s[b].insert(a);
    }

    vector<int> ans;

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      a = get(a);
      b = get(b);
      if (s[a].count(b) == 0) {
        ans.push_back(i);
        if (p[a] != p[b]) {
          if (s[a].size() > s[b].size()) {
            swap(a, b);
          }
          for (int x : s[a]) {
            s[x].erase(a);
            s[x].insert(b);
            s[b].insert(x);
          }
          s[a].clear();
          p[a] = b;
        }
      }
    }

    printf("%d\n", (int)ans.size());
    for (int i : ans) {
      printf("%d ", i + 1);
    }
    printf("\n");
  }


  return 0;
}
