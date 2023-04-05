#include <utility>
#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "B"

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

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int w, h, k;
  while (scanf("%d%d%d", &w, &h, &k) == 3) {
    vector<pair<int, pii>> cs;
    forn (i, k) {
      int x, y;
      scanf("%d%d", &x, &y), x--, y--;
      assert(0 <= x && x < w);
      assert(0 <= y && y < h);
      cs.pb(mp(x + y, mp(x, y)));
    }
    cs.pb(mp(w + h - 2, mp(w - 1, h - 1)));
    sort(cs.begin(), cs.end());

    string result;
    int cx = 0, cy = 0;
    for (auto c : cs) {
      int x, y;
      tie(x, y) = c.second;
      if (cx <= x && cy <= y) {
        while (cx < x) {
          result += 'D';
          cx++;
        }
        while (cy < y) {
          result += 'R';
          cy++;
        }
      } else {
        cx = -1;
        cy = -1;
        break;
      }
    }
    if (cx == w - 1 && cy == h - 1) {
      printf("%s\n", result.c_str());
    } else {
      printf("Impossible\n");
    }
  }

  return 0;
}
