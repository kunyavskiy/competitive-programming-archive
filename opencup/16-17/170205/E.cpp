#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "E"

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

struct item {
  ll value;
  int pos;

  bool operator<(const item &rhs) const {
    if (value != rhs.value)
      return value < rhs.value;
    return pos < rhs.pos;
  }
};

struct tree {
  vector<item> t;
  vector<ll> upd;
  int lst;

  void recalc(int v) {
    t[v] = max(t[2 * v], t[2 * v + 1]);
  }

  void add(int v, ll val) {
    upd[v] += val;
    t[v].value += val;
  }

  void push(int v) {
    add(2 * v, upd[v]);
    add(2 * v + 1, upd[v]);
    upd[v] = 0;
  }

  void update(int v, int l, int r, int L, int R, ll val) {
    if (r <= L || R <= l) return;
    if (L <= l && r <= R) {
      add(v, val);
      return;
    }
    push(v);
    update(2*v, l, (l + r) / 2, L, R, val);
    update(2*v + 1, (l + r) / 2, r, L, R, val);
    recalc(v);
  }

  item get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) return {-(1LL << 60), 0};
    if (L <= l && r <= R) {
      return t[v];
    }
    push(v);
    item lv = get(2*v, l, (l + r) / 2, L, R);
    item rv = get(2*v + 1, (l + r) / 2, r, L, R);
    return max(lv, rv);
  }


public:

  void init(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    t.resize(2*lst);
    for (int i = 0; i < n; i++) {
      t[i + lst] = {0, i};
    }
    for (int i = lst - 1; i > 0; i--) {
      recalc(i);
    }
    upd.resize(2*lst);
  }

  void update(int l, int r, ll v) {
    update(1, 0, lst, l, r, v);
  }

  item get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  ll get(int pos) {
    return get(1, 0, lst, pos, pos + 1).value;
  }
};

tree A, B;
set<int> s;

struct player {
  int r, p, a, b, id;

  bool operator<(const player &rhs) const {
    return r < rhs.r;
  }
};

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  vector<player> v(n);

  int maxb = 0;
  int id = 0;
  for (player& p : v) {
    scanf("%d %d %d %d", &p.r, &p.p, &p.a, &p.b);
    p.id = id++;
    p.b++;
    maxb = max(maxb, p.b);
  }

  A.init(maxb);
  B.init(maxb);
  s.insert(0);
  s.insert(maxb);

  sort(v.begin(), v.end());
  vector<ll> ans(n);

  for (const player &p : v) {
    ans[p.id] = A.get(p.a, p.b).value + p.p;
    eprintf("get[%d..%d) = %lld\n", p.a, p.b, ans[p.id] - p.p);
    s.insert(p.a);
    s.insert(p.b);
    B.update(p.a, p.b, p.p);
    eprintf("B[%d..%d) += %d\n", p.a, p.b, p.p);

    while (true) {
      item best = B.get(0, maxb);
      eprintf("best = %lld at %d\n", best.value, best.pos);
      if (best.value <= 0) break;
      auto it = s.upper_bound(best.pos);
      assert(it != s.end());
      assert(it != s.begin());
      int rv = *it;
      --it;
      int lv = *it;
      B.update(lv, rv, -best.value);
      A.update(lv, rv, best.value);
      eprintf("B[%d..%d) -= %lld\n", lv, rv, best.value);
      eprintf("A[%d..%d) += %lld\n", lv, rv, best.value);
      if (rv != maxb && B.get(rv) == 0) {
        s.erase(rv);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    printf("%lld\n", ans[i]);
  }


  return 0;
}
