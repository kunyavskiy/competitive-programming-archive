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

#define TASKNAME "A"

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

void diffs(int n, ll *a, ll *diffs, ll m) {
  for (int i = 0; i < n - 1; i++) {
    diffs[i] = a[i + 1] - a[i];
  }
  diffs[n - 1] = a[0] + m - a[n - 1];
}

#define start startasdjsajdlsajd

const int MAX = (1 << 17) - 1;
const int MAXN = 2 * 100100;
int cnt[MAX + 1];
int start[MAX + 1];
ll tmpArr[MAXN];

ll ca[MAXN * 3 + 10], cb[MAXN];
int p[MAXN * 3 + 10];

void my_sort(int n, ll *a) {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < n; ++i) {
    cnt[a[i] & MAX]++;
  }
  start[0] = 0;
  for (int i = 1; i < MAX; ++i) {
    start[i] = start[i - 1] + cnt[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    tmpArr[start[a[i] & MAX]++] = a[i];
  }

  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < n; ++i) {
    cnt[tmpArr[i] >> 17]++;
  }
  start[0] = 0;
  for (int i = 1; i < MAX; ++i) {
    start[i] = start[i - 1] + cnt[i - 1];
  }
  for (int i = 0; i < n; ++i) {
    a[start[tmpArr[i] >> 17]++] = tmpArr[i];
  }
}

#define CUR_TIME (clock()*1.0/CLOCKS_PER_SEC)

double KMPtime = 0.0;
double sortTime = 0.0;

ll get_k(int n, ll *a0, ll *a, ll *b, ll m) {
  for (int i = 0; i < n; ++i) {
    a[i] = a0[i] % m;
  }
  sortTime -= CUR_TIME;
  my_sort(n, a);
  sortTime += CUR_TIME;
  diffs(n, a, ca, m);
  diffs(n, b, cb, m);
  int caSize = n;
  int cbSize = n;
  ca[caSize++] = -1;
  memcpy(ca + caSize, cb, cbSize * sizeof(cb[0]));
  caSize += cbSize;
  memcpy(ca + caSize, cb, cbSize * sizeof(cb[0]));
  caSize += cbSize;

  KMPtime -= CUR_TIME;
  for (int i = 1; i < caSize; i++) {
    int j = p[i-1];
    while (j && ca[i] != ca[j]) j = p[j-1];
    if (ca[i] == ca[j]) j++;
    p[i] = j;
    if (p[i] == n) {
      return (b[i - 2 * n] - a[0] + m) % m;
    }
  }
  KMPtime += CUR_TIME;
  return -1;
}

ll a[MAXN];
ll b[MAXN];
ll a2[MAXN];

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%lld", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%lld", &b[i]);
  }

  ll bmax = *max_element(b, b+n);
  // ll mpred_
  ll m_pred = accumulate(b, b + n, 0) / n;

  sort(b, b + n);

  for (int i = 0; ; i++) {
    for (int j = (i == 0 ? 1 : -1); j <= 1; j += 2) {
      ll mod = m_pred + i * j;
      //fprintf(stderr, "check %lld (diff = %lld), n = %d\n", mod, abs(mod - 3269136750), n);
      if (mod <= bmax) continue;
      ll k = get_k(n, a, a2, b, mod);
      if (k != -1) {
        printf("%lld %lld\n", mod, k);
        return 0;
      }
    }
  }
  eprintf("sortTime %.10lf KMPtime %.10lf\n", sortTime, KMPtime);
  return 0;
}
