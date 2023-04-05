//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "J"

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
typedef pair<int,int> pii;


const ll INF = (1LL << 50);

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  vector <pii> team(m, pii(0, 0));
  for (int i = 1; i <= n; ++i) {
    int x;
    scanf("%d", &x);
    --x;
    team[x].first = i;
    team[x].second += 1;
  }
  sort(team.begin(), team.end());
  ll res = INF;
  vector <bool> can(k + 1, false);
  can[0] = true;
  int maxCnt = 0;
  for (int i = 0; i < m; ++i) {
    int cnt = team[i].second;
    int curT = team[i].first;
    for (int j = k; j >= 0; --j) {
      if (j >= cnt && can[j - cnt]) {
        can[j] = true;
        maxCnt = max(maxCnt, j);
      }
    }
    if (n - maxCnt <= k) {
      res = min(res, ll(maxCnt) * curT + ll(n - maxCnt) * n);
    }
  }
  printf("%lld\n", res == INF ? -1 : res);

  return 0;
}
