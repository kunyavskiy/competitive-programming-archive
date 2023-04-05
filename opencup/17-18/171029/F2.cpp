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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MOD = int(1e9) + 7;
void madd(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int m;
  while (scanf("%d", &m) == 1) {
    vvi qs(m);
    for (vi &q : qs) {
      int l;
      scanf("%d", &l);
      q.resize(l);
      for (int &x : q)
        scanf("%d", &x);
    }

    vi perm(m);
    for (int i = 0; i < m; i++) perm[i] = i;

    int ans = 0;
    do {
      vi cur;
      for (int i = 0; i < m; i++) {
        cur.insert(cur.end(), qs[perm[i]].begin(), qs[perm[i]].end());
      }
      for (int l = 0; l < (int)cur.size(); l++) {
        int tmp = 0;
        for (int r = l; r < (int)cur.size(); r++) {
          tmp = __gcd(tmp, cur[r]);
          madd(ans, tmp);
        }
      }
    } while (next_permutation(perm.begin(), perm.end()));
    printf("%d\n", ans);
  }
  return 0;
}
