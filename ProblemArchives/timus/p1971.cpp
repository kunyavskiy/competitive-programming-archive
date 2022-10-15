#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <sstream>
//#include <iostream>

#define pb push_back
#define mp make_pair
#define TASKNAME ""

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#ifndef LOCAL
#undef assert
void assert(bool x) {
  if (!x) printf("%d\n", 5 / 0);
}
void assert2(bool x) {
  if (!x) {
    int *tmp = new int[1];
    tmp[int(1e5)] = 100 / 23;
  }
}
#else
#define assert2 assert
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef linux
#define LLD "%lld"
#else
#define LLD "%I64d"
#endif

#define sz(x) ((int)(x).size())

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

class Solver {
  static const ll INF = 2e9;
  multiset<int> all;

  public:
  Solver() : all() {}
  void add(int x) {
    all.insert(x);
  }
  void del(int x) {
    multiset<int>::iterator it = all.find(x);
    assert(it != all.end());
    all.erase(it);
  }
  ll getProd() {
    if (sz(all) >= 40) return INF;

    ll cur = 1;
    for (multiset<int>::iterator it = all.begin(); it != all.end(); it++) {
      cur *= *it;
      if (cur >= INF) return INF;
    }
    return cur;
  }
};

int main(){     
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  int n;
  while (scanf("%d", &n) == 1) {
    map<string, int> opts;
    Solver s;
    for (int i = 0; i < n; i++) {
      char buf[16];
      int k;
      scanf("%s%d", buf, &k);
      opts[buf] = k;
      s.add(k);
    }

    int w, h;
    ll spd;
    int m;
    scanf("%d%d%I64d%d", &w, &h, &spd, &m);

    for (int i = 0; i <= m; i++) {
      ll ck = s.getProd(); // 1e10
      ck *= w; // 2.6e13
      ck *= h; // 5.2e16
      // fps = spd / ck
//      eprintf("%.2lf\n", double(spd) / ck);
      if (/* spd/ck < 10 */ spd < ck * 10) {
        printf("Slideshow\n");
      } else if (/* spd/ck >= 60 */ spd >= ck * 60) {
        printf("Perfect\n");
      } else {
        printf("So-so\n");
      }

      if (i == m) break;

      char op[16], buf[16];
      scanf("%s", op);
      if (!strcmp(op, "Resolution")) {
        scanf("%d%d", &w, &h);
      } else {
        scanf("%s", buf);
        map<string, int>::iterator it = opts.find(buf);
        assert(it != opts.end());

        if (!strcmp(op, "On")) s.add(it->second);
        else if (!strcmp(op, "Off")) s.del(it->second);
        else assert(false);
      }
    }
  }

  TIMESTAMP(end);
  return 0;
}
