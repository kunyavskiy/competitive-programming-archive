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

#define TASKNAME "C"

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

const int MAXL = 5000100;
const int MAXK = 55;

const ll INF = 1LL << 60;

int k;
char sc[MAXL];
int s[MAXL];
int c[MAXK][MAXK];

const int MAGIC = 5;

int best[MAXK][MAGIC];
int bestv[MAXK][MAGIC];

ll dp[MAGIC][MAGIC];
ll ndp[MAGIC][MAGIC];

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  scanf("%d ", &k);
  fgets(sc, MAXL, stdin);
  int n = strlen(sc);

  while (sc[n - 1] == '\r' || sc[n - 1] == '\n') n--;
  sc[n] = 0;

  for (int i = 0; i < n; i++) {
    if (sc[i] >= 'a' && s[i] <= 'z') {
      s[i] = sc[i] - 'a';
    } else {
      s[i] = sc[i] - 'A' + 26;
    }
  }

  for (int i = 0; i < k; i++) {
    for (int j = 0; j < k; j++) {
      scanf("%d", &c[i][j]);
    }
  }

  if ((k == 1 && n >= 2) || (k == 2 && n >= 3)) {
    printf("-1\n");
    return 0;
  }

  if (n == 1) {
    printf("0\n");
    return 0;
  }

  int best_cnt = k >= MAGIC ? MAGIC : k;

  for (int i = 0; i < k; i++) {
    vector<pair<int, int>> t;
    for (int j = 0; j < k; j++) {
      t.push_back(make_pair(c[i][j], j));
    }
    sort(t.begin(), t.end());
    for (int j = 0; j < best_cnt; j++) {
      best[i][j] = t[j].second;
      bestv[i][j] = t[j].first;
    }
  }

  for (int i = 0; i < best_cnt; i++)
    for (int j = 0; j < best_cnt; j++) {
      dp[i][j] = (best[s[0]][i] != best[s[1]][j]) ? (bestv[s[0]][i] + bestv[s[1]][j]) : INF;
    }

  for (int i = 2; i < n; i++) {
    for (int j = 0; j < best_cnt; j++) {
      for (int k = 0; k < best_cnt; k++) {
        ndp[j][k] = INF;
        if (best[s[i]][k] != best[s[i-1]][j]) {
          for (int q = 0; q < best_cnt; q++) {
            if (best[s[i]][k] != best[s[i - 2]][q]) {
              ndp[j][k] = min(ndp[j][k], dp[q][j] + bestv[s[i]][k]);
            }
          }
        }
      }
    }
    for (int j = 0; j < best_cnt; j++) {
      for (int k = 0; k < best_cnt; k++) {
        dp[j][k] = ndp[j][k];
      }
    }
  }

  ll ans = INF;
  for (int j = 0; j < best_cnt; j++) {
    for (int k = 0; k < best_cnt; k++) {
      ans = min(ans, dp[j][k]);
    }
  }

  printf("%lld\n", ans);
  return 0;
}
