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

int n;

struct generator {
  int pt;
  int shift;
  vector<ll> &b;

  generator(int shift, vector<ll>& b) : pt(0), shift(shift), b(b){}

  ll next(ll at_least) {
    ll pos = at_least + shift;
    while (b[pt] <= pos) pt++;
    return b[pt] - shift;
  }

  int get_id() const {
    int id = pt % (2 * n);
    if (id < n) {
      return id;
    } else {
      return 2 * n - id - 1;
    }
  }
};

struct graph {
  vector<int> dsu;
  vector<bool> flag;
  explicit graph(int sz) {
    dsu.resize(sz);
    flag.resize(sz);
    for (int i = 0; i < sz; i++) {
      dsu[i] = i;
    }
  }

  int get(int a) {
    if (a == dsu[a]) return a;
    return dsu[a] = get(dsu[a]);
  }

  bool add_edge(int a, int b) {
    a = get(a);
    b = get(b);
    if (flag[a] && flag[b]) {
      return false;
    }
    if (a == b) {
      flag[a] = true;
    } else {
      dsu[a] = b;
      flag[b] = flag[a] || flag[b];
    }
    return true;
  }
};

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  ll L;
  while (scanf("%lld%d", &L, &n) == 2) {
    vector<int> a(n);
    vector<ll> b(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      --a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
      scanf("%lld", &b[i]);
      --b[i];
    }
    sort(b.begin(), b.end());
    for (int i = n - 1; i >= 0; i--) {
      b.push_back(2 * L - b[i] - 1);
    }
    for (int i = 0; i < 2 * n; i++) {
      b.push_back(b[i] + 2LL * L);
    }
    b.push_back(numeric_limits<ll>::max());
    vector<generator> generators;
    generators.reserve(2 * n);
    for (int i = 0; i < n; i++) {
      generators.emplace_back(a[i], b);
      generators.emplace_back(2LL * L - a[i] - 1, b);
    }


    auto try_time = [&](ll time) {
      eprintf("try %lld\n", time);
      graph g(n);
      for (int i = 0; i < 2 * n; i += 2) {
        bool ok1 = generators[i].next(time - 1) == time;
        bool ok2 = generators[i + 1].next(time - 1) == time;
        if (!ok1 && !ok2) {
          return false;
        }
      }
      for (int i = 0; i < 2 * n; i += 2) {
        bool ok1 = generators[i].next(time - 1) == time;
        bool ok2 = generators[i + 1].next(time - 1) == time;
        int a, b;
        if (ok1 && ok2) {
          a = generators[i].get_id();
          b = generators[i + 1].get_id();
        } else if (ok1) {
          a = b = generators[i].get_id();
        } else if (ok2) {
          a = b = generators[i + 1].get_id();
        } else {
          assert(false);
        }
        if (!g.add_edge(a, b)) {
          return false;
        }
      }
      return true;
    };

    ll cur_time = 0;
    vector<ll> vals;
    vals.resize(2 * n);
    while (cur_time < 2 * L) {
      if (try_time(cur_time)) {
        break;
      }
      vals.clear();
      for (auto &g : generators) {
        vals.push_back(g.next(cur_time));
      }
#ifdef LOCAL
      eprintf("next(%lld) = ", cur_time);
      for (long long val : vals) {
        eprintf("%lld ", val);
      }
      eprintf("\n");
#endif
      nth_element(vals.begin(), vals.begin() + n - 1, vals.end());
      cur_time = vals[n - 1];
    }

    if (cur_time < 2 * L) {
      printf("%lld\n", cur_time);
    } else {
      printf("-1\n");
    }
  }

  return 0;
}
