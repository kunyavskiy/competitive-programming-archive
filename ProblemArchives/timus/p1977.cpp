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

class segm_tree {
  struct Node {
    double sum;
    bool setZero;
    double a, b;
    int sumlen;

    Node(int sumlen = 0) : sum(0), setZero(false), a(0), b(0), sumlen(sumlen) {}
    void push(Node &l, Node &r) {
       if (setZero) {
        l.zero();
        r.zero();
        setZero = false;
      }
      l.add(a, b);
      r.add(a, b + a * l.sumlen);
      a = b = 0;
    }
    void zero() {
      sum = 0;
      setZero = true;
      a = b = 0;
    }
    void add(double na, double nb) {
      sum += nb * sumlen;
      sum += na * double(sumlen) * (sumlen - 1) / 2;
      a += na; b += nb;
    }
  };

  static const int MAXOFF = 1 << 19;
  Node ns[2 * MAXOFF];
  int off;

  double _get(int v, int l, int r, int curl, int curr) {
    if (curr < l || r < curl) return 0;
    if (l <= curl && curr <= r)
      return ns[v].sum;

    assert(v < off);
    int mid = (curl + curr) >> 1;
    ns[v].push(ns[2 * v], ns[2 * v + 1]);
    return _get(2 * v, l, r, curl, mid) + _get(2 * v + 1, l, r, mid + 1, curr);
  }
  void _zero(int v, int l, int r, int curl, int curr) {
    if (curr < l || r < curl) return;
    if (l <= curl && curr <= r) {
      ns[v].zero();
      return;
    }

    assert(v < off);
    int mid = (curl + curr) >> 1;
    ns[v].push(ns[2 * v], ns[2 * v + 1]);
    _zero(2 * v, l, r, curl, mid);
    _zero(2 * v + 1, l, r, mid + 1, curr);
    ns[v].sum = ns[2 * v].sum + ns[2 * v + 1].sum;
  }
  void _add(int v, int l, int r, int curl, int curr, double a, double b) {
    if (curr < l || r < curl) return;
    if (l <= curl && curr <= r) {
      ns[v].add(a, b);
      return;
    }

    assert(v < off);

    int mid = (curl + curr) / 2;

    ns[v].push(ns[2 * v], ns[2 * v + 1]);
    _add(2 * v, l, r, curl, mid, a, b);
    _add(2 * v + 1, l, r, mid + 1, curr, a, b + a * ns[2 * v].sumlen);
    ns[v].sum = ns[2 * v].sum + ns[2 * v + 1].sum;
  }

  int *xs;
  int xlen;

  public:
  void init(int *_xs, int _xlen) {
    xs = _xs;
    xlen = _xlen;

    off = 1;
    while (off < xlen - 1) off <<= 1;
    memset(ns, 0, sizeof ns);

    for (int i = 0; i + 1 < xlen; i++)
      ns[off + i].sumlen = xs[i + 1] - xs[i];
    for (int i = off - 1; i >= 1; i--)
      ns[i].sumlen = ns[2 * i].sumlen + ns[2 * i + 1].sumlen;
  }
  void add(int l, int r, double a, double b) {
    l = lower_bound(xs, xs + xlen, l) - xs;
    r = upper_bound(xs, xs + xlen, r) - xs - 1;
    assert(0 <= l && l <= r && r < off);
    _add(1, l, r, 0, off - 1, a, b);
  }
  void zero(int l, int r) {
    l = lower_bound(xs, xs + xlen, l) - xs;
    r = upper_bound(xs, xs + xlen, r) - xs - 1;
    assert(0 <= l && l <= r && r < off);
    _zero(1, l, r, 0, off - 1);
  }
  double get(int l, int r) {
    l = lower_bound(xs, xs + xlen, l) - xs;
    r = upper_bound(xs, xs + xlen, r) - xs - 1;
    assert(0 <= l && l <= r && r < off);
    double res = _get(1, l, r, 0, off - 1);
    return res;
  }
};

struct Op {
  double curt;
  bool isSave;
  int l, r;
  bool operator<(const Op &o2) const { return curt < o2.curt; }
};

segm_tree s;

const int MAXM = 1e5 + 1e3;
Op ops[MAXM];
int xs[3 * MAXM + 100];

int main(){     
  #ifdef LOCAL
  freopen(TASKNAME".in","r",stdin);
  freopen(TASKNAME".out","w",stdout);
  #endif

  int n;
  double p;
  while (scanf("%d%lf", &n, &p) == 2) {
    int xlen = 0;
    xs[xlen++] = 0;
    xs[xlen++] = n;

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
      scanf("%lf", &ops[i].curt);

      char buf[10];
      scanf("%s", buf);
      if (!strcmp(buf, "save")) {
        int l, r;
        scanf("%d%d", &l, &r), l--, r--;
        ops[i].isSave = true;
        ops[i].l = l;
        ops[i].r = r;
        xs[xlen++] = l;
        xs[xlen++] = r + 1;
      } else if (!strcmp(buf, "enforce")) {
        int mid, d;
        scanf("%d%d", &mid, &d), mid--;
        ops[i].isSave = false;
        ops[i].l = mid;
        ops[i].r = d;
        xs[xlen++] = mid - d + 1;
        xs[xlen++] = mid;
        xs[xlen++] = mid + d;
      }
    }
    sort(xs, xs + xlen);
    xlen = unique(xs, xs + xlen) - xs;
    sort(ops, ops + m);

    s.init(xs, xlen);

    double oldt = 0;
    double storage = 0;

    for (int i = 0; i < m; i++) {
      double curt = ops[i].curt;
      s.add(0, n - 1, 0, (curt - oldt) * p);

      if (ops[i].isSave) {
        double sum = s.get(ops[i].l, ops[i].r);
        storage += sum;
        printf("%.9lf\n", storage);
        s.zero(ops[i].l, ops[i].r);
      } else {
        int mid = ops[i].l, d = ops[i].r;

        double x = storage / (double(d) * d);
        if (d > 1)
          s.add(mid - d + 1, mid - 1, x, -(mid - d) * x);
        s.add(mid, mid + d - 1, -x, (mid + d) * x);
        storage = 0;
      }
      oldt = curt;
    }
  }

  TIMESTAMP(end);
  return 0;
}
