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

void solve() {
    int n, c;
    scanf("%d%d", &n, &c);
    char s[20], t[20];
    scanf("%s%s", s, t);
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == t[i]) {
            start |= 1 << i;
        }
    }
    vector<int> disabled(1 << n);
    for (int i = 0; i < c; i++) {
        scanf("%s", s);
        int mask = 0;
        for (int j = 0; j < n; j++) {
            if (s[j] == '=') {
                mask |= 1 << j;
            }
        }
        disabled[mask] = true;
    }
    vector<int> mt(1 << n, -1);
    vector<char> used(1 << n);

    auto dfs = [&](auto dfs, int v) -> bool {
        if (used[v]) return false;
        used[v] = true;
        for (int i = 0; i < n; i++) {
            int other = v ^ (1 << i);
            if (disabled[other]) continue;
            if (mt[other] == -1 || dfs(dfs, mt[other])) {
                mt[other] = v;
                mt[v] = other;
                return true;
            }

        }
        return false;
    };

    for (int i = 0; i < (1 << n); i++) {
        if (disabled[i]) continue;
        if (i == start) continue;
        if (__builtin_popcount(i) % 2 == __builtin_popcount(start) % 2) {
            fill(used.begin(), used.end(), 0);
            int r = dfs(dfs, i);
            eprintf("Start from %d: %d\n", i, r);
        }
    }
    fill(used.begin(), used.end(), 0);
    if (dfs(dfs, start)) {
        printf("Alice\n");
    } else {
        printf("Bob\n");
    }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
      solve();
  }

  return 0;
}
