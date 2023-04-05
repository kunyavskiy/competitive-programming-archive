#include <iostream>
#include <cstring>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 55;

int a[MAXN][MAXN], fl[MAXN], fr[MAXN];
int p[MAXN], d[MAXN], mt[MAXN];
bool used[MAXN];
int n;

void iterate(int nv) {
  memset(d, 100, sizeof(d));
  memset(used, 0, sizeof(used));

  d[n] = 0;
  int l = n;
  mt[n] = nv;

  while (mt[l] != -1) {
    int k = mt[l];
    int nl = -1;
    used[l] = true;
    for (int i = 0; i < n; i++)
      if (!used[i]) { /*BOXNEXT*/
        if (d[i] > d[l] + a[k][i] + fl[k] + fr[i]) { /*BOXNEXT*/
          d[i] = d[l] + a[k][i] + fl[k] + fr[i];
          p[i] = l;
        }
        if (nl == -1 || d[nl] > d[i])
          nl = i;
      }

    int add = d[nl];

    for (int i = 0; i <= n; i++)
      if (used[i])
        fr[i] += add, fl[mt[i]] -= add;
      else
        d[i] -= add;
    l = nl;
  }

  while (l != n) {
    mt[l] = mt[p[l]];
    l = p[l];
  }
}

void hungrian() {
  memset(mt, -1, sizeof(mt));
  for (int i = 0; i < n; i++)
    iterate(i);
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += a[mt[i]][i];
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
      a[i][j] = -a[i][j];
    }
  }

  hungrian();

  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += (fl[i] + fr[i]) * n;
  }

  printf("%d\n", sum);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", fl[i] + fr[j]);
    }
    printf("\n");
  }


  return 0;
}
