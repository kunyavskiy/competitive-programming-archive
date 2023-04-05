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

#define TASKNAME "F"

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

const int N = (int) 2e5 + 100;
int w[N], p[N], val[N], ans[N], answer[N];

bool cmp(int a, int b){
  return w[a] > w[b];
}

bool solve()
{
  int n;
  if (scanf("%d", &n) <= 0) return false;

  for (int i = 1; i <= n; i++) {
    ans[i] = -1;
    val[i] = -1;
    p[i] = i;
    scanf("%d", &w[i]);
  }
  sort(p + 1, p + n + 1, cmp);

  int mx = 0, prv = 0;
  for (int i = 1; i <= n; i++)
  {
    int v = p[i];
    val[v] = 1;
    while (v > 0)
    {
      ans[v] = val[v];
      if (2 * v <= n)
        ans[v] += max(0, ans[2 * v] );
      if (2 * v + 1 <= n)
        ans[v] += max(0, ans[2 * v + 1] );
//      printf("ans[%d] = %d\n", v, ans[v]);
      mx = max(mx, ans[v] );
      v /= 2;
    }
    for (int j = prv; j < mx; j++)
      answer[j] = w[p[i]];
    prv = mx;
  }
  for (int i = 0; i < n; i++)
    printf("%d ", answer[i] );
  printf("\n");

  return true;
}


int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  while (solve());

  return 0;
}
