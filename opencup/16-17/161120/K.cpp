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

#define TASKNAME "K"

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

const int MAXN = 1000100;

vector<int> primes;
int p[MAXN];
int mu[MAXN];

int a[MAXN];
int b[MAXN];


int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  mu[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (p[i] == 0) {
      p[i] = i;
      primes.push_back(i);
    }
    mu[i] = (p[i / p[i]] == p[i]) ? 0 : -mu[i / p[i]];
    for (int j = 0; j < (int)primes.size() && primes[j] <= p[i] && primes[j] * i < MAXN; j++) {
      p[primes[j] * i] = primes[j];
    }
  }

  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    a[x]++;
  }
  for (int i = 0; i < m; i++) {
    int x;
    scanf("%d", &x);
    b[x]++;
  }

  ll ans[2];
  ans[0] = ans[1] = 0;

  for (int g = 1; g < MAXN; g++) {
    if (!mu[g]) {
      continue;
    }
    int cnt[2][2];
    memset(cnt, 0, sizeof(cnt));
    for (int i = g; i < MAXN; i += g) {
      if (mu[i] == -1) {
        cnt[0][1] += a[i];
        cnt[1][1] += b[i];
      } else if (mu[i] == 1) {
        cnt[0][0] += a[i];
        cnt[1][0] += b[i];
      }
    }

//    if (g <= 10) {
//      eprintf("g = %d, mu[g] = %d, ans[0] += %lld, ans[1] += %lld\n", g, mu[g], cnt[0][0] * 1LL * cnt[1][0] + cnt[0][1] * 1LL * cnt[1][1], cnt[0][1] * 1LL * cnt[1][0] + cnt[0][0] * 1LL * cnt[1][1]);
//    }

    ans[0] += mu[g] * (cnt[0][0] * 1LL * cnt[1][0] + cnt[0][1] * 1LL * cnt[1][1]);
    ans[1] += mu[g] * (cnt[0][1] * 1LL * cnt[1][0] + cnt[0][0] * 1LL * cnt[1][1]);
  }

  printf("%lld %lld %lld\n", ans[1], n * 1LL * m - ans[0] - ans[1], ans[0]);
  return 0;
}
