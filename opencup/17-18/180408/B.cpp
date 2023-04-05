#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

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

const int MAXN = 310000;

const int MAGIC = 400;

struct query {
  int l, r;
  int id;
};

int cnt[MAXN];
int tot;

int add(int val, int add) {
  tot -= cnt[val] % 2;
  cnt[val] += add;
  tot += cnt[val] % 2;
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, q;
  scanf("%d%d", &n, &q);
  vector<int> a(n);
  vector<int> zs;
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  vector<int> vs = a;
  vs.push_back(0);
  sort(vs.begin(), vs.end());
  vs.erase(unique(vs.begin(), vs.end()), vs.end());
  for (int i = 0; i < n; i++) {
    a[i] = lower_bound(vs.begin(), vs.end(), a[i]) - vs.begin();
  }

  vector<query> qs(q);
  for (int i = 0; i < q; i++) {
    qs[i].id = i;
    scanf("%d%d", &qs[i].l, &qs[i].r);
    --qs[i].l;
  }

  sort(qs.begin(), qs.end(), [](const query& a, const query&b) {
    return make_pair(a.l / MAGIC, a.r) < make_pair(b.l / MAGIC, b.r);
  });

  int curl = 0;
  int curr = 0;

  vector<int> ans(q);

  for (query x : qs) {
    while (curr < x.r) {
      add(a[curr++], 1);
    }
    while (curr > x.r) {
      add(a[--curr], -1);
    }
    while (curl < x.l) {
      add(a[curl++], -1);
    }
    while (curl > x.l) {
      add(a[--curl], 1);
    }

    ans[x.id] = (x.r - x.l + tot - cnt[0] - cnt[0] % 2) / 2;

    eprintf("id = %d, l = %d, r = %d, ans = %d\n", x.id, x.l, x.r, ans[x.id]);
  }

  for (int i = 0; i < q; i++) {
    printf("%d\n", ans[i]);
  }

  return 0;
}
