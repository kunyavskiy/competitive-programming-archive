#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct topic {
  int time, need, index;
};

void solve() {
  int n; ll t;
  scanf("%d%lld", &n, &t);
  vector<topic> v(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &v[i].time, &v[i].need);
    v[i].index = i + 1;
  }
  sort(v.begin(), v.end(), [](const topic& a, const topic& b) {
    return a.need < b.need;
  });
  multiset<int> got_ok, got_nok;
  multiset<int> ngot_ok, ngot_nok;
  for (int i = 0; i < n; i++) {
    ngot_nok.insert(v[i].time);
  }
  int best_k = 0, best_ans = 0;
  int ptr = 0;

  auto get_first = [&](multiset<int>& a, multiset<int>& b) {
    assert(!b.empty());
    t -= *b.begin();
    a.insert(*b.begin());
    b.erase(b.begin());
  };
  auto unget_last = [&](multiset<int>& a, multiset<int>& b) {
    assert(!a.empty());
    t += *a.rbegin();
    b.insert(*a.rbegin());
    a.erase(--a.end());
  };

  for (int k = 1; k <= n; k++) {
    while (ptr < n && v[ptr].need <= k) {
      auto it = got_nok.find(v[ptr].time);
      if (it != got_nok.end()) {
        got_ok.insert(v[ptr].time);
        got_nok.erase(it);
      } else {
        it = ngot_nok.find(v[ptr].time);
        ngot_ok.insert(v[ptr].time);
        ngot_nok.erase(it);
      }
      ptr++;
    }
    if (!ngot_ok.empty()) {
      get_first(got_ok, ngot_ok);
    } else {
      get_first(got_nok, ngot_nok);
    }
    while (!got_ok.empty() && !ngot_ok.empty() && *got_ok.rbegin() > *ngot_ok.begin()) {
      get_first(got_ok, ngot_ok);
      unget_last(got_ok, ngot_ok);
    }
    while (t < 0 && !got_ok.empty() && !ngot_nok.empty() && *got_ok.rbegin() > *ngot_nok.begin()) {
      unget_last(got_ok, ngot_ok);
      get_first(got_nok, ngot_nok);
    }
    while (!ngot_ok.empty() && !got_nok.empty() && t + *got_nok.rbegin() - *ngot_ok.begin() >= 0) {
      get_first(got_ok, ngot_ok);
      unget_last(got_nok, ngot_nok);
    }

    if (t >= 0 && (int)got_ok.size() > best_ans) {
      best_ans = got_ok.size();
      best_k = k;
    }
  }

  printf("%d\n%d\n", best_ans, best_k);
  auto split = partition(v.begin(), v.end(), [&](const topic& t) { return t.need <= best_k; });
  sort(v.begin(), split, [](const topic& a, const topic& b) { return a.time < b.time; });
  sort(split, v.end(), [](const topic& a, const topic& b) { return a.time < b.time; });
  vector<int> ans;
  for (int i = 0; i < best_ans; i++) {
    printf("%d ", v[i].index);
  }
  for (int i = 0; i < best_k - best_ans; i++) {
    printf("%d ", split[i].index);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-- > 0)
    solve();

  return 0;
}
