#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "A"

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

int have[13][4];
bool BAD;

void get() {
  char c1, c2;
  scanf(" %c %c", &c1, &c2);
  const char* vals1 = "A23456789XJQK";
  const char* vals2 = "CDHS";
  int v1 = strchr(vals1, c1) - vals1;
  int v2 = strchr(vals2, c2) - vals2;
  eprintf(" %c%c", c1, c2);
  have[v1][v2] = 1;
}

int bad[52];
int badc[4][4];
int es[4][4];
int vs[4];

void remove(int i, int j) {
  have[i][j] = 0;
  vs[j]--;
  for (int k = 0; k < 4; k++) {
    if (have[i][k]) {
      es[j][k]--;
      es[k][j]--;
    }
  }
}

void add(int i, int j) {
  for (int k = 0; k < 4; k++) {
    if (have[i][k]) {
      es[j][k]++;
      es[k][j]++;
    }
  }
  vs[j]++;
  have[i][j] = 1;
}

int used[4];

void dfs(int v, int c) {
  used[v] = c;
  for (int i = 0; i < 4; i++) {
    if (es[v][i] && !used[i]) {
      dfs(i, c);
    }
  }
}

bool check(int deleted) {
  memset(used, 0, sizeof(used));
  int comp = 0;
  for (int i = 0; i < 4; i++) {
    if (vs[i] > 0 && !used[i]) {
      dfs(i, ++comp);
    }
  }
  if (comp <= deleted)
    return true;
  if (deleted == 0) {
    return comp == 1;
  }
  if (comp > deleted + 1) {
    for (int i = 0; i < 52; i++) bad[i] = 1;
    BAD = true;
    return false;
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++)
      if (used[i] == used[j]) {
        badc[i][j] = 1;
      }
  }
  return false;
}

set<ll> cache;

bool brute(int n, int k, int last, ll mask) {
  if (k == n) { return true;}
  ll hash = mask * 64 + last;
  if (cache.count(hash)) { return false; }
  cache.insert(hash);
  for (int i = 0; i < 52; ++i) {
    if (have[i / 4][i % 4] && (k == 0 || (last / 4 == i / 4) || (last % 4 == i % 4))) {
      have[i / 4][i % 4] = 0;
      if (brute(n, k + 1, i, mask | (1LL << i))) {
        have[i / 4][i % 4] = 1;
        return true;
      }
      have[i / 4][i % 4] = 1;
    }
  }
  return false;
}

void stupid(int n, bool expected) {
#ifdef LOCAL
  eprintf("exp %d\n", expected ? 1 : 0);
  (void)n;
  //assert(brute(n, 0, -1) == expected);
#endif
}


bool solve(int n) {
  memset(bad, 0, sizeof(bad));
  memset(es, 0, sizeof(es));
  memset(badc, 0, sizeof(badc));
  memset(vs, 0, sizeof(vs));
  for (int i = 0; i< 13; i++) {
    for (int j = 0; j < 4; j++) {
      if (have[i][j]) {
        vs[j]++;
        for (int k = j + 1; k < 4; k++) {
          if (have[i][k]) {
            es[j][k]++;
            es[k][j]++;
          }
        }
      }
    }
  }
  if (!check(0)) return false;
  if (n <= 3) return true;
  for (int i = 0; !BAD && i < 52; i++) {
    if (!have[i / 4][i % 4]) continue;
    remove(i / 4, i % 4);
    if (!check(1)) {
      bad[i] = 1;
    }
    for (int j = i + 1; !BAD && j < 52; j++) {
      if (!have[j / 4][j % 4]) continue;
      remove(j / 4, j % 4);
      if (!check(2)) {
        bad[i] = bad[j] = 1;
      }
      for (int k = j + 1; !BAD && k < 52; k++) {
        if (!have[k / 4][k % 4]) continue;
        remove(k / 4, k % 4);
        if (!check(3)) {
          bad[i] = bad[j] = bad[k] = 1;
        }
        add(k / 4, k % 4);
      }
      add(j / 4, j % 4);
    }
    add(i / 4, i % 4);
  }

  for (int i = 0; i < 52; i++)
    for (int j = i + 1; j < 52; j++)
      if (have[i / 4][i % 4] && have[j / 4][j % 4] && !bad[i] && !bad[j] && !badc[i % 4][j % 4]) {
        return true;
      }
  return false;
}

int main() {
  #ifdef LOCAL
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
  #endif

  int n;
  while (scanf("%d", &n) == 1) {
    BAD = false;
    eprintf("%d", n);
    memset(have, 0, sizeof(have));
    for (int i = 0; i < n; i++) {
      get();
    }
    eprintf("\n");
    cache.clear();
    if (solve(n) && (n >= 10 || brute(n, 0, -1, 0))) {
      stupid(n, true);
      puts("YES");
    } else {
      stupid(n, false);
      puts("NO");
    }
  }

  return 0;
}
