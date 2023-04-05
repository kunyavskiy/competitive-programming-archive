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

#define pw(x) (((__int128)1) << x)

const int N = 128;
int cnt = 0;



void rec(__int128 mask, int mn) {
  if (mn == N) {
    cnt++;
    if (cnt % (int)1e4 == 0) cerr << cnt << endl;
    return;
  }
  rec(mask, mn + 1);
  if (!(mask & pw(mn))) {
    mask |= pw(mn);

    vector<int> vct;
    for (int i = 0; i < N; i++) if (mask & pw(i)) vct.push_back(i);

    vector<int> cand;
    cand.push_back(mn);

    bool ok = 1;
    for (int q = 0; ok && q < (int)cand.size(); q++) {
      int val = cand[q];

      for (int i = 0; ok && i < (int)vct.size(); i++) {
        int nw;

        nw = val & vct[i];
        if (!(mask & pw(nw))) {
          ok &= nw >= mn;
          mask |= pw(nw);
          vct.push_back(nw);
          cand.push_back(nw);
        }

        nw = val | vct[i];
        if (!(mask & pw(nw))) {
          ok &= nw >= mn;
          mask |= pw(nw);
          vct.push_back(nw);
          cand.push_back(nw);
        }
      }
    }
    if (ok) {
      rec(mask, mn + 1);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  rec(8, 0);
  cout << cnt << endl;
//  cout << ans.size() << endl;

  return 0;
}
