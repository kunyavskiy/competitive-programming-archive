#include <bitset>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

#ifdef LOCAL
const int L = 50;
#else
const int L = 300100;
#endif

struct item {
  int d, tf, ts;
};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
#endif
  int n, q;
  scanf("%d%d", &n, &q);
  vector<item> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d%d", &v[i].d, &v[i].tf, &v[i].ts);
  }
  sort(v.begin(), v.end(),
       [](const item &a, const item &b) { return a.ts < b.ts; });
  vector<int> max_fast(v.size() + 1);
  vector<int64_t> sum_fast(v.size() + 1);
  for (int i = n - 1; i >= 0; i--) {
    max_fast[i] = max(max_fast[i + 1], v[i].tf);
    sum_fast[i] = sum_fast[i + 1] + v[i].d;
  }
  bitset<L> b;
  b[0] = 1;
  vector<pair<int64_t, int>> can;
  can.emplace_back(sum_fast[0], max_fast[0]);
  int64_t sum_slow = 0;
  for (int i = 0; i < n; i++) {
    sum_slow += v[i].d;
    if (sum_slow >= 2 * L) {
      break;
    }
    b = b | (b << v[i].d);
    int x = (sum_slow + 1) / 2;
    auto best = b[x] ? x : b._Find_next(x);
    can.emplace_back(best + sum_fast[i + 1], max(max_fast[i + 1], v[i].ts));
  }
  vector<int> ans(L, std::numeric_limits<int>::max());
  for (auto [l, t] : can) {
    if (l < L) {
      ans[l] = min(ans[l], t);
    }
  }
  for (int i = 1; i < L; i++) {
    ans[i] = min(ans[i], ans[i - 1]);
  }
  for (int i = 0; i < L; i++) {
    if (ans[i] == numeric_limits<int>::max()) {
      ans[i] = -1;
    }
  }
  for (int i = 0; i < q; i++) {
    int l;
    scanf("%d", &l);
    printf("%d\n", ans[l]);
  }
}