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

#define TASKNAME "L"

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

int inv[100];

struct clause {
  int x, valx;
  int y, valy;
};

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (int i = 0; i < 3; i++) {
    for (int& x : v) {
      int t;
      scanf("%d", &t);
      x |= (t << i);
    }
  }

  for (int i = 0; i < n; i++) {
    if (v[i] & 4) {
      inv[i] = 1;
      v[i] = 7 - v[i];
    }
  }

  int ans[4];
  memset(ans, -1, sizeof(ans));

  vector<clause> res;

  for (int i = 0; i < n; i++) {
    if (v[i] == 0) {
      res.push_back({i, 1, i, 0});
      continue;
    }
    if (ans[v[i]] == -1) {
      ans[v[i]] = i;
    } else {
      res.push_back({i, 1, ans[v[i]], 1});
      res.push_back({i, 0, ans[v[i]], 0});
    }
  }

  if (ans[1] == -1 && ans[2] != -1) {
    ans[1] = ans[2];
    ans[2] = -1;
  }

  assert(ans[1] != -1);
  if (ans[2] == -1) {
    res.push_back({ans[3], 0, ans[1], 0});
  } else if (ans[3] == -1) {
    res.push_back({ans[2], 1, ans[1], 0});
  } else {
    printf("-1\n");
    return 0;
  }

  printf("%d\n", (int)res.size());
  for (clause x : res) {
    if (inv[x.x]) x.valx = !x.valx;
    if (inv[x.y]) x.valy = !x.valy;
    if (!x.valx) printf("!");
    printf("x%d -> ", x.x + 1);
    if (!x.valy) printf("!");
    printf("x%d\n", x.y + 1);
  }

  return 0;
}
