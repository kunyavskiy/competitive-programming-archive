#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef vector<ll> vll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const long long linf = 1e18;
const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

class segm_tree {
  vi tr;
  int off;

  public:
  segm_tree(const vi &vals) {
    off = 1; while (off < sz(vals)) off <<= 1;
    tr = vi(2 * off, INF);
    for (int i = 0; i < sz(vals); i++)
      tr[off + i] = vals[i];
    for (int i = off - 1; i >= 1; i--)
      tr[i] = min(tr[2 * i], tr[2 * i + 1]);
  }
  int get(int l, int r) {
    l += off; r += off;
    int res = INF;
    while (l <= r) {
      if (l & 1) res = min(res, tr[l++]);
      if (!(r & 1)) res = min(res, tr[r--]);
      l >>= 1; r >>= 1;
    }
    return res;
  }
};
class fenv_tree {
  vll tr;
  static int f(int x) { return x & -x; }

  public:
  fenv_tree(int n) : tr(n + 1, 0) {}
  void add(int x, int v) {
    assert(0 <= x && x + 1 < sz(tr));
    for (x++; x < sz(tr); x += f(x))
      tr[x] += v;
  }
  ll get(int x) {
    ll res = 0;
    for (x++; x > 0; x -= f(x))
      res += tr[x];
    return res;
  }
};

vi calcLastLess(const vi &as) {
  int n = sz(as);
  vi res(n, -1);
  vector<pii> st;

  for (int i = 0; i < sz(as); i++) {
    while (!st.empty() && st.back().first >= as[i])
      st.pop_back();
    if (!st.empty())
      res[i] = st.back().second;
    st.pb(mp(as[i], i));
  }

/*  #ifdef DEBUG
  for (int i = 0; i < sz(as); i++) {
    int x = i - 1;
    while (x >= 0 && as[x] >= as[i])
      x--;
    assert(x == res[i]);
  }
  #endif*/
  return res;
}

vi calcNextLess(vi as) {
  reverse(as.begin(), as.end());
  vi res = calcLastLess(as);
  reverse(res.begin(), res.end());
  for (int i = 0; i < sz(res); i++)
    res[i] = sz(as) - 1 - res[i];
  return res;
}

const int MAXL = 1e5 + 1e3;
char input[MAXL + 1];
char s[2 * MAXL + 1];

int main() {
/*  #ifdef DEBUG
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
  #else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif*/

  while (scanf("%s", input) >= 1) {
    int l = strlen(input);
    for (int i = 0; i < l; i++) {
      s[2 * i] = input[i];
      s[2 * i + 1] = '.';
    }
    s[2 * l] = 0;
    l *= 2;

    vi cols(l), sarr(l, -1);
    vi lcp(l - 1);
    {
      reverse(s, s + l);
      vi was;
      for (int i = 0; i < l; i++)
        was.pb(s[i]);
      sort(was.begin(), was.end());
      was.erase(unique(was.begin(), was.end()), was.end());

      for (int i = 0; i < l; i++)
        cols[i] = lower_bound(was.begin(), was.end(), s[i]) - was.begin();

      for (int cslen = 1; cslen < l; cslen <<= 1) {
        vi firs1(l + 1, -1), nes1(l, -1);
        for (int i = 0; i < l; i++) {
          int b = -1;
          if (i + cslen < l) b = cols[i + cslen];
          
          b++;
          nes1[i] = firs1[b];
          firs1[b] = i;
        }

        vi firs2(l, -1);
        vi nes2(l, -1);
        for (int b = sz(firs1) - 1; b >= 0; b--)
          for (int id = firs1[b]; id >= 0; id = nes1[id]) {
            int a = cols[id];
            nes2[id] = firs2[a];
            firs2[a] = id;
          }

        pii prev(-1, -1);
        int ccol = -1;

        vi ncols(l);
        for (int a = 0; a < sz(firs2); a++)
        for (int id = firs2[a]; id >= 0; id = nes2[id]) {
          assert(a == cols[id]);
          int b = -1;
          if (id + cslen < l) b = cols[id + cslen];
          b++;

          assert(prev <= mp(a,b));
          if (prev != mp(a, b)) {
            prev = mp(a,b);
            ccol++;
          }
          ncols[id] = ccol;
        }
        cols.swap(ncols);
      }
      for (int i = 0; i < l; i++)
        sarr[cols[i]] = i;

      int cval = 0;
      for (int i = 0; i < l; i++) {
        if (cols[i] == l - 1) {
          cval = 0;
        } else {
          int i2 = sarr[cols[i] + 1];
          while (i + cval < l && i2 + cval < l && s[i + cval] == s[i2 + cval])
            cval++;
          lcp[cols[i]] = cval;
        }
        cval = max(0, cval - 1);
      }
/*      #ifdef DEBUG
      for (int i = 0; i < l; i++) {
        assert(sarr[i] >= 0);
      }
      for (int i = 0; i + 1 < l; i++)
          assert(strcmp(s + sarr[i], s + sarr[i + 1]) < 0);
      for (int i = 0; i + 1 < l; i++) {
        int tmp = 0;
        while (sarr[i] + tmp < l && sarr[i + 1] + tmp < l && s[sarr[i] + tmp] == s[sarr[i + 1] + tmp])
          tmp++;
        assert(tmp == lcp[i]);
      }
      #endif*/

      reverse(s, s + l);

      reverse(cols.begin(), cols.end());
      for (int i = 0; i < l; i++)
        sarr[i] = l - 1 - sarr[i];
    }

    vi pals(l);
    timestamp("ff0");
    {
      int r = 0, ri = 0;
      pals[0] = 1;
      for (int i = 1; i < l; i++) {
        int k = 0;
        if (i <= r) k = min(r - i + 1, pals[2 * ri - i]);
/*        #ifdef DEBUG
        for (int i2 = 0; i2 < k; i2++) {
          assert(i >= i2 && i + i2 < l);
          assert(s[i - i2] == s[i + i2]);
        }
        #endif*/

        while (i >= k && i + k < l && s[i - k] == s[i + k])
          k++;
        pals[i] = k;
        if (i + k - 1 > r) {
          r = i + k - 1;
          ri = i;
        }
      }  
    }
    timestamp("ff1");

    segm_tree tr(lcp);

    vector<pii> rqs;
    timestamp("ff2");
    vi lasless = calcLastLess(sarr);
    timestamp("ff3");
    vi nexless = calcNextLess(sarr);
    timestamp("ff4");

    for (int i = 0; i < l; i++) if (s[i] != '.') {
      int pos = cols[i];
      int lef = lasless[pos];
      int rig = nexless[pos];

      int cval = 0;
      if (lef >= 0)
        cval = max(cval, tr.get(lef, pos - 1));
      if (rig < l)
        cval = max(cval, tr.get(pos, rig - 1));
      // len should be > cval

//      eprintf("i=%d, cval=%d, l=%d, pos=%d, r=%d\n", i, cval, lef, pos, rig);

      // among [0..i-cval] get palindromes
      int cl = (cval + 1) / 2;
      rqs.pb(mp(i - cl, i));
//      eprintf("requst(%d, %d)\n", i - cl, i);
    }
    sort(rqs.begin(), rqs.end());

/*    for (int i = 0; i < l; i++)
      eprintf("%d%c", pals[i] + i - 1, "\n "[i + 1 < l]);
    for (int i = 0; i < l; i++)
      eprintf("%d%c", pals[i], "\n "[i + 1 < l]);*/

    vector<ll> anses(l);

    fenv_tree trsum(2 * l + 1);

    int cpos = 0;
    for (int i = 0; i < sz(rqs);) {
      while (cpos <= rqs[i].first) {
        trsum.add(2 * l - (pals[cpos] + cpos - 1), 1);
        cpos++;
      }
      
      int st = i;
      while (i < sz(rqs) && rqs[i].first == rqs[st].first) {
        int res = trsum.get(2 * l - rqs[i].second);
        anses[rqs[i].second] = res;
        i++;
      }
    }

    for (int i = 2; i < l; i++)
      anses[i] += anses[i - 2];
    for (int i = 0; i < l; i += 2)
      printf("%I64d%c", anses[i], "\n "[i + 2 < l]);
    break;
  }

  timestamp("end");
  return 0;
}
