#include <algorithm>
#include <utility>
#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "H"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

class fenv_tree {
    static int f(int x) { return x & -x; }

  public:
    fenv_tree(int n) : tr(n + 1, 0) {}
    void add(int x, int v) {
      for (x++; x < sz(tr); x += f(x))
        tr[x] += v;
    }
    ll get(int x) {
      ll res = 0;
      for (x++; x > 0; x -= f(x))
        res += tr[x];
      return res;
    }
    ll get(int l, int r) {
      return get(r) - get(l - 1);
    }

  private:
    vll tr;
};

vvi chi;
vi intr;
int tim;
vector<pii> ltim, rtim;

void dfs(int v) {
  if (v < 0) {
    int id = -v - 1;
    assert(0 <= id && id < sz(intr));
    intr[id] = tim;
    tim++;
    return;
  }
  v--;
  assert(0 <= v && v < sz(chi));
  assert(sz(chi[v]) == 2);
  int st = tim;
  dfs(chi[v][0]);
  int mid = tim;
  dfs(chi[v][1]);
  int en = tim;

  ltim[v] = mp(st, mid - 1);
  rtim[v] = mp(mid, en - 1);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, qcnt;
  while (scanf("%d%d", &n, &qcnt) == 2) {
    vi worigin(n + 1);
    forn (i, n + 1) {
      scanf("%d", &worigin[i]);
    }
    vi lens(n);
    chi = vvi(n, vi(2));
    forn (i, n) {
      scanf("%d%d%d", &lens[i], &chi[i][0], &chi[i][1]);
    }

    intr = vi(n + 1, -1);
    ltim = vector<pii>(n, mp(-1, -1));
    rtim = vector<pii>(n, mp(-1, -1));
    tim = 0;
    dfs(1);
    assert(tim == n + 1);

    fenv_tree tr(n + 1);
    forn (i, sz(intr)) {
      assert(intr[i] >= 0 && intr[i] <= n);
      tr.add(intr[i], worigin[i]);
    }

    while (qcnt --> 0) {
      int t;
      scanf("%d", &t);
      if (t == 1) {
        int id, v;
        scanf("%d%d", &id, &v);
        id--;
        assert(0 <= id && id < sz(intr));

        tr.add(intr[id], v - worigin[id]);
        worigin[id] = v;
      } else if (t == 2) {
        int id;
        scanf("%d", &id);
        id--;
        assert(0 <= id && id < sz(ltim));

        ll sl = tr.get(ltim[id].first, ltim[id].second);
        ll sr = tr.get(rtim[id].first, rtim[id].second);
        assert(sl > 0 && sr > 0);
        printf("%.16f\n", (double)sr * lens[id] / (sl + sr));
      } else {
        assert(false);
      }
    }
    fflush(stdout);
  }

  return 0;
}
