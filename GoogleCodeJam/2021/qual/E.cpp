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

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

void solve() {
  constexpr int N = 100;
  constexpr int Q = 10000;
  vector<string> v(N);
  for (auto &x : v) {
    static char buf[Q + 1];
    scanf("%s", buf);
    x = buf;
  }
  vector<double> s(N);
  for (int i = 0; i < N; i++) {
    double cnt = count(v[i].begin(), v[i].end(), '1') * 1.0 / Q;
    double lf = -3;
    double rg = 3;
    for (int it = 0; it < 60; it++) {
      double m = (lf + rg) / 2;
      // [m-3..m+3]
      auto f = [&](double x) { return x - log(exp(m) + exp(x));};
      double acnt = (f(3) - f(-3)) / 6;
      if (acnt > cnt) {
        rg = m;
      } else {
        lf = m;
      }
    }
    s[i] = lf;
  }

  auto cov = [](const string& a, const string &b) {
    int cnta = 0, cntb= 0, cntab = 0;
    for (int i = 0; i < Q; i++) {
      if (a[i]=='1') cnta++;
      if (b[i] == '1') cntb++;
      if (a[i] == '1' && b[i] == '1') cntab++;
    }
    return cntab * 1.0 / Q - (cnta * 1.0 / Q) * (cntb * 1.0 / Q);
  };

  double best = 1e9;
  int best_id = -1;
  for (int i = 0; i < N; i++) {
    double score = 0;
    for (int j = 0; j < N; j++) {
      if (i == j) continue;
      double c = cov(v[i], v[j]);
      // int [-3,3] 1/(1 + e^(x - s[i]))(1+e^(x - s[j]));
      double e1 = exp(s[i]);
      double e2 = exp(s[j]);
      auto f = [&](double x) {
        if (fabs(e1 - e2) < 1e-6) {
          return x + 1 / (1 + exp(x - s[i])) - log(e1 + exp(x));
        }
        return x + (e2 * log(e1 + exp(x)) - e1 * log(e2 + exp(x))) / (e1 - e2);
      };
      auto f2 = [&](double s, double x) { return x - log(exp(s) + exp(x));};
      double EProd = (f(3) - f(-3)) / 6;
      double E1 = (f2(s[i], 3) - f2(s[i], -3)) / 6;
      double E2 = (f2(s[j], 3) - f2(s[j], -3)) / 6;
      double ec = EProd - E1 * E2;
      score += c / ec;
    }
    if (score < best) {
      best = score;
      best_id = i;
    }
    eprintf("%d: %lf\n", i, score);
  }
  printf("%d\n", best_id + 1);
}


int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);
  scanf("%*d");

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
