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
#include <random>

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

bool is_prime[101];

#ifdef LOCAL
vector<int> ans;
int total_ops;
bool answered;
int query_(int a, int b) {
  assert(!answered);
  ++total_ops;
  return __gcd(ans[a], ans[b]);
}
void answer(string s) {
  assert(!answered);
  for (int i = 0; i < 100; i++) {
    assert(is_prime[ans[i]] == (s[i] == '1'));
  }
  answered = true;
}
#else
int query_(int a, int b) {
  printf("? %d %d\n", a + 1, b + 1);
  fflush(stdout);
  int res;
  scanf("%d", &res);
  return res;
}
void answer(string s) {
  printf("! %s\n", s.c_str());
  fflush(stdout);
}
#endif

int cache[101][101];
int qlcm[101];

int query(int a, int b) {
  assert(a != b);
  int& c = cache[min(a, b)][max(a,b)];
  if (c == -1) {
    c = query_(a, b);
    qlcm[a] = qlcm[a] * c / __gcd(qlcm[a], c);
    qlcm[b] = qlcm[b] * c / __gcd(qlcm[b], c);
  }
  return c;
}

auto rnd = mt19937();


void solve() {
  memset(cache, -1, sizeof(cache));
  vector<int> all(100);
  for (int i = 0; i < (int)all.size(); i++) {
    qlcm[i] = 1;
    all[i] = i;
  }
  auto find_random = [&](const vector<int> &v, int d) {
    auto dis = uniform_int_distribution<int>(0, v.size() - 1);
    while (true) {
      int a = dis(rnd);
      int b = dis(rnd);
      if (a == b) {
        continue;
      }
      if (query(v[a], v[b]) % d == 0) {
        return v[a];
      }
    }
  };
  auto filter_divs = [&](const vector<int>& v, int d) {
    auto r = find_random(v, d);
    vector<int> ans;
    for (int x : v) {
      if (x == r || query(x, r) % d == 0) {
        ans.push_back(x);
      }
    }
    return ans;
  };
  auto filter_eq = [&](const vector<int>& v, int p, int g) {
    vector<int> ans;
    for (int x : v) {
      if (x != p && query(x, p) == g) {
        ans.push_back(x);
      }
    }
    return ans;
  };
  auto filter_known = [&](const vector<int>& v, int p) {
    vector<int> ans;
    for (int x : v) {
      if (qlcm[x] == p) {
        ans.push_back(x);
      }
    }
    return ans;
  };
  vector<int> even = filter_divs(all, 2);
  vector<int> tens = filter_divs(even, 5);
  assert(tens.size() == 10);
  for (int i = 0; i < 10; i++) {
    for (int j = i + 1; j < 10; j++) {
      query(tens[i], tens[j]);
    }
  }
  int p60 = find(qlcm, qlcm + 100, 60) - qlcm;
#ifdef LOCAL
  assert(ans[p60] == 60);
#endif

  vector<int> p70c;
  for (int i : tens) {
    if (qlcm[i] == 10 || qlcm[i] == 70) {
      p70c.push_back(i);
    }
  }
  int p70;
  assert(p70c.size() == 2);
  auto dis = uniform_int_distribution<int>(0, 99);
#ifdef LOCAL
  assert(min(ans[p70c[0]], ans[p70c[1]]) == 10);
  assert(max(ans[p70c[0]], ans[p70c[1]]) == 70);
#endif

  while (true) {
    int a = dis(rnd);
    if (a == p70c[0] || a == p70c[1])
      continue;
    if (query(a, p70c[0]) % 7 == 0) {
      p70 = p70c[0];
      break;
    }
    if (query(a, p70c[1]) % 7 == 0) {
      p70 = p70c[1];
      break;
    }
  }
#ifdef LOCAL
  assert(ans[p70] == 70);
#endif


  vector<int> primes = filter_eq(filter_eq(all, p60, 1), p70, 1);
  vector<int> primes2 = filter_eq(filter_eq(all, p60, 2), p70, 2);
  vector<int> primes3 = filter_eq(filter_eq(all, p60, 3), p70, 1);
  vector<int> primes5 = filter_eq(filter_eq(all, p60, 5), p70, 5);
  vector<int> primes7 = filter_eq(filter_eq(all, p60, 1), p70, 7);

#ifdef LOCAL
  auto dump = [](vector<int> pos) {
    vector<int> v;
    for (int x: pos) {
      v.emplace_back(ans[x]);
    }
    sort(v.begin(), v.end());
    eprintf("%d: ", (int)v.size());
    for (int x : v) {
      eprintf("%d ", x);
    }
    eprintf("\n");
  };
  eprintf("======\n");
#endif

  for (auto p90 : filter_known(all, 30)) {
    primes3 = filter_eq(primes3, p90, 3);
  }
  for (auto p90 : filter_known(all, 90)) {
    primes3 = filter_eq(primes3, p90, 3);
  }
  for (auto p50 : filter_known(all, 50)) {
    primes5 = filter_eq(primes5, p50, 5);
  }
  for (auto p14 : filter_known(all, 14)) {
    primes7 = filter_eq(primes7, p14, 7);
  }


  primes7 = filter_known(primes7, 7);
  for (int i : primes5) {
    if (primes7.size() > 1) primes7 = filter_eq(primes7, i, 1);
  }
  primes5 = filter_known(primes5, 5);
  for (int i : primes3) {
    if (primes5.size() > 1) primes5 = filter_eq(primes5, i, 1);
  }
  primes3 = filter_known(primes3, 3);
  for (int i : primes2) {
    if (primes3.size() > 1) primes3 = filter_eq(primes3, i, 1);
  }
  primes2 = filter_known(primes2, 2);
  for (int i : primes) {
    if (primes2.size() > 1) primes2 = filter_eq(primes2, i, 1);
  }

#ifdef LOCAL
  dump(primes);
  dump(primes2);
  dump(primes3);
  dump(primes5);
  dump(primes7);
#endif

  assert(primes.size() == 22);
  assert(primes2.size() == 1);
  assert(primes3.size() == 1);
  assert(primes5.size() == 1);
  assert(primes7.size() == 1);

  auto result = string(100, '0');
  for (int x : primes) {
    result[x] = '1';
  }
  result[primes2[0]] = '1';
  result[primes3[0]] = '1';
  result[primes5[0]] = '1';
  result[primes7[0]] = '1';
  answer(result);
}

int main() {
  for (int i = 1; i <= 100; i++) {
    is_prime[i] = true;
    for (int j = 2; j * j <= i; j++) {
      if (i % j == 0) {
        is_prime[i] = false;
      }
    }
  }

  for (int i = 0; i < 1000; i++) {
#ifdef LOCAL
    ans.resize(100);
    for (int j = 0; j < 100; j++) {
      ans[j] = j + 1;
    }
    shuffle(ans.begin(), ans.end(), mt19937());
    answered = false;
#endif
    solve();
#ifdef LOCAL
    assert(answered);
#endif
  }
#ifdef LOCAL
  eprintf("Total ops = %d, avg = %lf\n", total_ops, total_ops / 1000.0);
#endif

  return 0;
}
