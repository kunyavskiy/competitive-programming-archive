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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<ll> a(n), b(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%lld", &b[i]);
  }
  vector<ll> diff(n), my(n), rem(n);
  vector<int> splits;
  {
    ll d = 0, m = 0, m2 = 0;
    for (int i = 0; i < n; i++) {
      d += a[i] - b[i];
      m += a[i];
      m2 += a[i];
      if (m2 >= k) {
        m2 = m - rem[i - 1];
        if (m2 >= k) {
          n = i;
          rem.resize(n);
          diff.resize(n);
          my.resize(n);
          break;
        }
        splits.push_back(i - 1);
      }
      diff[i] = d;
      my[i] = m;
      rem[i] = min(my[i], my[i] - diff[i]);
    }
  }

  int best_last_cut = n;

  for (int i = 0; i < n; i++) {
    ll last_done_min = my[i] - k;
    ll last_done_max = my[i] - diff[i] - k;
//    eprintf("%lld %lld %lld %lld %lld\n", rem[i], my[i], diff[i], last_done_min, last_done_max);
    if (last_done_max <= last_done_min) continue;
    if (last_done_min < 0 && 0 <= last_done_max) {
      best_last_cut = -1;
      continue;
    }
    int id = upper_bound(rem.begin(), rem.end(), last_done_min) - rem.begin();
    if (id != (int)rem.size() && rem[id] <= last_done_max) {
//      eprintf("win at %d by %d\n", i, id);
      best_last_cut = min(best_last_cut, id);
    }
  }

//  eprintf("best_last = %d\n", best_last_cut);

  if (best_last_cut == n) {
    printf("-1\n");
    return;
  }
  vector<int> cuts;
  for (int i : splits) {
    if (i <= best_last_cut) {
      cuts.push_back(i);
    }
  }
  if (best_last_cut != -1) {
    cuts.push_back(best_last_cut);
  }
  sort(cuts.begin(), cuts.end());
  cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
  printf("%d\n", (int)cuts.size());
  for (int x : cuts) {
    printf("%d ", x + 1);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
