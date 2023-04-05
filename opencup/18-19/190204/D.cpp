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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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

struct tree {
  int global_xor;
  int n;
  vector<ll> vals;
  int p;
  tree(const vector<int> &v) : global_xor(0), n(v.size()), vals(2 * n), p(__builtin_ctz(n)) {
    assert(!(n & (n - 1)));
    for (int i = 0; i < n; i++) {
      vals[n + i] = v[i];
    }
    for (int i = n - 1; i > 0; i--) {
      vals[i] = vals[2 * i] + vals[2 * i + 1];
    }
  }
  void add(int pos, ll x) {
    pos ^= global_xor;
    pos += n;
    while (pos) {
      vals[pos] += x;
      pos /= 2;
    }
  }

  ll get(int pos) {
    return vals[(pos ^ global_xor) + n];
  }

  ll sum(int v, int l, int r, int L, int R, int d) {
    if (R <= l || r <= L) {
      return 0;
    }
    if (L <= l && r <= R) {
      return vals[v];
    }
    int m = (l + r) / 2;
    return sum(2 * v + ((global_xor >> d) & 1), l, m, L, R, d - 1) +
           sum(2 * v + 1 - ((global_xor >> d) & 1), m, r, L, R, d - 1);
  }

  ll sum(int l, int r) {
    return sum(1, 0, n, l, r, p - 1);
  }

  void print(int v, int d) {
    if (d == -1) {
      eprintf("%lld ", vals[v]);
      return;;
    }
    print(2 * v + ((global_xor >> d) & 1), d - 1);
    print(2 * v + 1 - ((global_xor >> d) & 1), d - 1);
  }

  void print() {
    print(1, p - 1);
    eprintf("\n");
  }

  void dump(int v, int d, vector<ll>& x) {
    if (d == -1) {
      x.push_back(vals[v]);
      return;;
    }
    dump(2 * v + ((global_xor >> d) & 1), d - 1, x);
    dump(2 * v + 1 - ((global_xor >> d) & 1), d - 1, x);
  }

  vector<ll> dump() {
    vector<ll> x;
    dump(1, p - 1, x);
    return x;
  }

};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int p, q;
  while (scanf("%d%d", &p, &q) == 2) {
    int n = 1 << p;
    vector<vector<int>> intersting(p);
    vector<vector<int>> intersting_pos(p, vector<int>(n, -1));
    vector<int> init(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &init[i]);
    }
    tree t(init);
    auto add_to_interesting = [&](int x) {
      for (int i = 0; i < p; i++) {
        if (x & (1 << i)) {
          if (intersting_pos[i][x] == -1) {
            intersting_pos[i][x] = intersting[i].size();
            intersting[i].push_back(x);
          }
        }
      }
    };

    auto remove_from_interesting = [&](int x) {
      for (int i = 0; i < p; i++) {
        if (x & (1 << i)) {
          if (intersting_pos[i][x] != -1) {
            int pos = intersting_pos[i][x];
            if (pos + 1 != (int)intersting[i].size()) {
              swap(intersting[i][pos], intersting[i].back());
              intersting_pos[i][intersting[i][pos]] = pos;
            }
            intersting_pos[i][x] = -1;
            intersting[i].pop_back();
          }
        }
      }
    };


    auto do_and = [&](int x) {
      t.global_xor &= x;
      for (int i = 0; i < p; i++) {
        if (x & (1 << i)) continue;
        for (int pos : intersting[i]) {
          int r = pos | (1 << i);
          r ^= t.global_xor;
          int l = r & x;
          ll val = t.get(r);
          t.add(l, val);
          t.add(r, -val);
          intersting_pos[i][r ^ t.global_xor] = -1;
          remove_from_interesting(r ^ t.global_xor);
          add_to_interesting(l ^ t.global_xor);
        }
        intersting[i].clear();
      }
    };
    for (int i = 0; i < n; i++) {
      if (init[i]) {
        add_to_interesting(i);
      }
    }

#ifdef LOCAL
    vector<ll> cur(init.size());
    for (int i = 0; i < n; i++) {
      cur[i] = init[i];
    }
#endif

    char type[10];
    for (int qq = 0; qq < q; qq++) {
      scanf("%s", type);
      if (!strcmp(type, "add")) {
        int pos, v;
        scanf("%d%d", &pos, &v);
        t.add(pos, v);
        add_to_interesting(pos ^ t.global_xor);
#ifdef LOCAL
        cur[pos] += v;
#endif
      } else if (!strcmp(type, "sum")) {
        int l, r;
        scanf("%d%d", &l, &r);
        ll res = t.sum(l, r + 1);
        printf("%lld\n", res);
#ifdef LOCAL
        ll res2 = 0;
        for (int i = l; i <= r; i++) {
          res2 += cur[i];
        }
        assert(res == res2);
#endif
      } else if (!strcmp(type, "xor")) {
        int x;
        scanf("%d", &x);
        t.global_xor ^= x;
#ifdef LOCAL
        vector<ll> ncur(cur.size());
        for (int i = 0; i < n; i++) {
          ncur[i ^ x] += cur[i];
        }
        cur = ncur;
#endif
      } else if (!strcmp(type, "and")) {
        int x;
        scanf("%d", &x);
        do_and(x);
#ifdef LOCAL
        vector<ll> ncur(cur.size());
        for (int i = 0; i < n; i++) {
          ncur[i & x] += cur[i];
        }
        cur = ncur;
#endif
      } else if (!strcmp(type, "or")) {
        int x;
        scanf("%d", &x);
        do_and(((1 << p) - 1) ^ x);
        t.global_xor ^= x;
#ifdef LOCAL
        vector<ll> ncur(cur.size());
        for (int i = 0; i < n; i++) {
          ncur[i | x] += cur[i];
        }
        cur = ncur;
#endif
      }
#ifdef LOCAL
      eprintf("???? ");
      t.print();
      eprintf("|");
      for (int i = 0; i < n; i++) {
        eprintf(" %lld", t.vals[n + i]);
      }
      eprintf("\n");
      assert(cur == t.dump());
#endif
    }
  }


  return 0;
}
