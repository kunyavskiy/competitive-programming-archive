#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "C"

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

char s[30][30];

bool solve() {
  int n;
  if (scanf("%d", &n) != 1) {
    return false;
  }

  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }

  vector<int> cnt(26);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cnt[s[i][j] - 'A']++;
    }
  }

  char res = 0;
  for (int j = 0; j < 26; j++)
    if (cnt[j] == n - 1) {
      res = 'A' + j;
    }

  int r, c;
  r = c = -1;
  for (int i = 0; i < n; i++) {
    bool ok = 1;
    for (int j = 0; j < n; j++) {
      if (s[i][j] == res) {
        ok = 0;
      }
    }
    if (ok) r = i;
  }


  for (int j = 0; j < n; j++) {
    bool ok = 1;
    for (int i = 0; i < n; i++) {
      if (s[i][j] == res) {
        ok = 0;
      }
    }
    if (ok) c = j;
  }

  printf("%d %d %c\n", r + 1, c + 1, res);
  return 1;
}

int main() {
  #ifdef LOCAL
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
  #endif

  while (solve());
  return 0;
}
