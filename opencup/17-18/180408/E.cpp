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


const int MAXN = 500100;

multiset<int> s[1 << BITS];
ll sum[1 << BITS];
map<int, int> g[1 << BITS];

ll get(int v) {
  int max = *s[v].rbegin();
  return min(sum[v] / 2, sum[v] - max);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  ll res = 0;

  for (int i = 1; i < n; i++) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    --a, --b;
    g[a][b] = w;
    g[b][a] = w;
    sum[a] += w;
    sum[b] += w;
    s[a].insert(w);
    s[b].insert(w);
    res += w;
  }

  for (int i = 0; i < n; i++) {
    res -= get(i);
  }

  printf("%lld\n", res);

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w);
    --a, --b;
    res += get(a);
    res += get(b);
    int oldw = g[a][b];
    res += w - oldw;
    g[a][b] = g[b][a] = w;
    sum[a] += w - oldw;
    sum[b] += w - oldw;
    s[a].erase(s[a].find(oldw));
    s[b].erase(s[b].find(oldw));
    s[a].insert(w);
    s[b].insert(w);
    res -= get(a);
    res -= get(b);
    printf("%lld\n", res);
  }



  return 0;
}
