#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "J"

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
typedef unsigned long long ull;
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

const int h = 8;
const int w = 8;

static ull bit(int x, int y) { return 1ULL << (y * w + x); }

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };
const char *dc = "rdlu";

ull fclean = 0, fbullet = 0;

#pragma pack(push, 1)
struct State {
  ull bricks;
  int cnt;
  char x, y;

  State go(char c) const {
    if ('a' <= c && c <= 'z') {
      int d = strchr(dc, c) - dc;
      int nx = x + dx[d], ny = y + dy[d];
      if (nx < 0 || ny < 0 || nx >= w || ny >= h)
        return *this;
      ll nbit = bit(nx, ny);
      if (!(fclean & nbit) || (bricks & nbit))
        return *this;
      return { bricks, cnt, (char) nx, (char) ny };
    } else {
      c += 'a' - 'A';
      assert('a' <= c && c <= 'z');
      int d = strchr(dc, c) - dc;
      int nx = x + dx[d], ny = y + dy[d];
      while (nx >= 0 && ny >= 0 && nx < w && ny < h) {
        ll nbit = bit(nx, ny);
        if (!(fbullet & nbit))
            return *this;
        if (bricks & nbit) {
          return { bricks & ~nbit, cnt, x, y };
        }
        nx += dx[d];
        ny += dy[d];
      }
      return *this;
    }
  }

  bool operator<(const State &s2) const {
    if (bricks != s2.bricks)
      return bricks < s2.bricks;
    if (x != s2.x)
      return x < s2.x;
    if (y != s2.y)
      return y < s2.y;
    return false;
  }

  bool operator==(const State &s2) const {
    return bricks == s2.bricks && x == s2.x && y == s2.y;
  }
};
#pragma pack(pop)

char f[h][w + 1];
char s1[35], s2[35];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  while (scanf("%d%s%s", &n, s1, s2) == 3) {
    assert((int)strlen(s1) == n);
    assert((int)strlen(s2) == n);

    int x0 = -1, y0 = -1;
    fclean = fbullet = 0;
    ull fbricks = 0;
    forn (y, h) {
      scanf("%s", f[y]);
      assert(strlen(f[y]) == w);
      forn (x, w) {
        assert(strchr(".WABT", f[y][x]));
        if (f[y][x] == 'T') {
          assert(x0 < 0);
          x0 = x;
          y0 = y;
          f[y][x] = '.';
        }
        if (f[y][x] == '.' || f[y][x] == 'B') {
          fclean |= bit(x, y);
        }
        if (f[y][x] != 'A') {
          fbullet |= bit(x, y);
        }
        if (f[y][x] == 'B') {
          fbricks |= bit(x, y);
        }
      }
    }

    vector<State> q, qn;
    q.pb({ fbricks, 1, (char) x0, (char) y0 });
    forn (iter, n) {
      qn.clear();
      qn.reserve(2 * sz(q));
      for (State s : q) {
        qn.pb(s.go(s1[iter]));
        qn.pb(s.go(s2[iter]));
      }

      int rem = 0;
      for (int ne = iter + 1; ne < n; ne++) {
        bool cur = false;
        cur |= 'a' <= s1[ne] && s1[ne] <= 'z';
        cur |= 'a' <= s2[ne] && s2[ne] <= 'z';
        rem += cur;
      }
      vector<vector<ull>> bmsk(h, vector<ull>(w));
      forn (ty, h)
        forn (tx, w) {
          ull cur = bit(tx, ty);
          for (int i = iter + 1; i < n; i++) {
            ull ne = 0;
            forn (y, h)
            forn (x, w) if (cur & bit(x, y)) {
              {
                State s = {0, 0, (char) x, (char) y};
                s = s.go(s1[i]);
                ne |= bit(s.x, s.y);
              }
              {
                State s = {0, 0, (char) x, (char) y};
                s = s.go(s2[i]);
                ne |= bit(s.x, s.y);
              }
            }
            cur = cur | ne;
          }
          bmsk[ty][tx] = cur;
          //bmsk[ty][tx] = -1;
          /*forn (y, h)
            forn (x, w)
              if (abs(x - tx) + abs(y - ty) <= rem) {
                msk |= bit(x, y);
              }*/
        }
      for (State &s : qn) {
        s.bricks &= bmsk[s.y][s.x];
      }

      q.swap(qn);
      qn.clear();
      sort(q.begin(), q.end());
      int ptr = 0;
      forn (i, sz(q))
        if (ptr && q[ptr - 1] == q[i]) {
          q[ptr - 1].cnt += q[i].cnt;
        } else {
          q[ptr++] = q[i];
        }
      eprintf("ptr = %d, before=%d\n", ptr, sz(q));
      q.resize(ptr);
    }
    vector<vector<ll>> data(h, vector<ll>(w));
    for (State s : q) {
      data[s.y][s.x] += s.cnt;
    }
    forn (y, h)
    forn (x, w) {
      ll a = data[y][x], b = 1 << n;
      ll d = __gcd(a, b);
      a /= d; b /= d;
      printf(LLD "/" LLD "%c", a, b, "\n "[x + 1 < w]);
    }
    #ifdef DEBUG
    eprintf("\n");
    printf("\n");
    #endif
  }

  return 0;
}
