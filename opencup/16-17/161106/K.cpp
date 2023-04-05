#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "K"

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

int MOD;
inline void madd(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}
inline int mmul(int a, int b) {
  return (int)(ll(a) * b % MOD);
}
inline int mpow(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = mmul(a, a))
    if (b & 1) res = mmul(res, a);
  return res;
}

class MagicSet {
  public:
    MagicSet() : a(1), ia(1), b(0) {}
    void prepareYourHashmap(int n) {
      vals.rehash(n);
    }
    void insert(int v, int id) {
      v = invConv(v);
      auto it = vals.find(v);
      if (it == vals.end()) {
        vals.insert(mp(v, mp(1, id)));
      } else {
        it->second.first++;
      }
    }

    void multiplyBy(int x, int ix) {
      #ifdef DEBUG
      assert(0 <= x && x < MOD);
      assert(0 <= ix && ix < MOD);
      assert(mmul(x, ix) == 1);
      #endif
      a = mmul(a, x);
      ia = mmul(ia, ix);
      b = mmul(b, x);
      #ifdef DEBUG
      assert(mmul(a, ia) == 1);
      #endif
    }

    void increaseBy(int x) {
      #ifdef DEBUG
      assert(0 <= x && x < MOD);
      #endif
      madd(b, x);
    }

    pii get(int v) {
      v = invConv(v);
      auto it = vals.find(v);
      if (it != vals.end()) {
        return it->second;
      } else {
        return mp(0, -1);
      }
    }

  private:
    // Real items are (a * val + b)
    // a * ia == 1
    int a, ia, b;
    unordered_map<int, pii> vals;

    int invConv(int v) {
      #ifdef DEBUG
      int v0 = v;
      #endif
      assert(0 <= v && v < MOD);
      madd(v, MOD - b);
      v = mmul(v, ia);
      #ifdef DEBUG
      int v1 = mmul(v, a);
      madd(v1, b);
      assert(v1 == v0);
      #endif
      return v;
    }
};


int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  static const int MAXN = int(1e5) + 10;
  static char str[MAXN];
  int tn;
  while (scanf("%s%d%d", str, &tn, &MOD) == 3) {
    assert(MOD >= 11);

    vi as(tn);
    for (int &a : as)
      scanf("%d", &a);

    vll acnt(tn);
    vi al(tn, -1), ar(tn, -1);

    int TEN = 10;
    int ITEN = mpow(TEN, MOD - 2);
    assert(mmul(TEN, ITEN) == 1);

    int n = strlen(str);
    MagicSet s;
    s.prepareYourHashmap(n);
    forn (i, n) {
      s.insert(0, i);
      s.multiplyBy(TEN, ITEN);
      s.increaseBy(str[i] - '0');
      forn (tid, tn) {
        pii res = s.get(as[tid]);
        acnt[tid] += res.first;
        if (al[tid] < 0 && res.second >= 0) {
          al[tid] = res.second;
          ar[tid] = i;
        }
      }
    }
    forn (i, tn) {
      printf(LLD " %d %d\n", acnt[i], al[i] + 1, ar[i] + 1);
    }
  }

  return 0;
}
