#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

struct num {
  static constexpr int BASE = 1000 * 1000 * 1000;
  vector<int> values;

  num(int x) {
    while (x) {
      values.push_back(x % BASE);
      x /= BASE;
    }
  }

  num(const string& s) {
    int cur = 1;
    int curv = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
      curv += (s[i] - '0') * cur;
      cur *= 10;
      if (cur == BASE) {
        values.push_back(curv);
        curv = 0;
        cur = 1;
      }
    }
    if (curv) {
      values.push_back(curv);
    }
    fix();
  }


  bool operator<(const num& a) const {
    if (values.size() != a.values.size()) return values.size() < a.values.size();
    for (int i = (int)values.size() - 1; i >= 0; i--) {
      if (values[i] != a.values[i]) {
        return values[i] < a.values[i];
      }
    }
    return false;
  }

  bool operator==(const num& a) const {
    return values == a.values;
  }

  num& operator-=(const num& a) {
    for (int i = 0; i < (int)a.values.size() || values[i] < 0; i++) {
      if (i < (int)a.values.size()) values[i] -= a.values[i];
      if (values[i] < 0) {
        values[i] += BASE;
        values[i + 1] -= 1;
      }
    }
    fix();
    return *this;
  }

  num& operator/=(int x) {
    int over = 0;
    for (int i = values.size() - 1; i >= 0; i++) {
      over = over * BASE + values[i];
      values[i] = over / x;
      over %= x;
    }
    fix();
    return *this;
  }

  num& operator*=(int x) {
    ll over = 0;
    for (int i = 0; i < (int)values.size(); i++) {
      over = over + values[i] * 1LL * x;
      values[i] = over % BASE;
      over /= BASE;
    }
    while (over) {
      values.push_back(over % BASE);
      over /= BASE;
    }
    fix();
    return *this;
  }


  void fix() {
    while (values.size() && values.back() == 0) values.pop_back();
  }
};

num gcd(num a, num b) {
  if (a.values.empty()) return b;
  if (b.values.empty()) return a;
  int st2 = 0;
  while (!a.values.empty() && !b.values.empty()) {
    int r1 = a.values[0] % 2;
    int r2 = b.values[0] % 2;
    while (r1 && r2) {
      a /= 2;
      r1 = a.values[0] % 2;
      b /= 2;
      r2 = b.values[0] % 2;
      st2++;
    }
    while (r1) {
      a /= 2;
      r1 = a.values[0] % 2;
    }
    while (r2) {
      b /= 2;
      r2 = b.values[0] % 2;
    }
    if (a < b) swap(a, b);
    a -= b;
  }
  if (a.values.empty()) return b;
  return a;
}


void PreCalc() {
}

void solve() {
  int n;
  scanf("%*d%d", &n);
  vector<num> v(n - 1);
  for (int i = 0; i < n - 1; i++) {
    string s;
    cin >> s;
    v.emplace_back(s);
  }
  vector<pair<num, num>> sv(n);

  for (int i = 1; i < n - 1; i++) {
    if (!(v[i] == v[i -1])) {

    }
  }
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
