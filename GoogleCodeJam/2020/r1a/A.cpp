#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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

string solve() {
  int n;
  cin >> n;
  vector<string> s(n);
  for (auto &x : s) {
    cin >> x;
  }
  string prefix, suffix;
  while (true) {
    char c = 0;
    for (auto &x : s) {
      if (x[0] != '*') {
        if (c == 0) {
          c = x[0];
        } else if (c != x[0]) {
          return "*";
        }
        x.erase(x.begin());
      }
    }
    if (c) {
      prefix += c;
    } else {
      break;
    }
  }

  while (true) {
    char c = 0;
    for (auto &x : s) {
      if (x.back() != '*') {
        if (c == 0) {
          c = x.back();
        } else if (c != x.back()) {
          return "*";
        }
        x.erase(--x.end());
      }
    }
    if (c) {
      suffix += c;
    } else {
      break;
    }
  }
  reverse(suffix.begin(), suffix.end());

  for (auto& x : s) {
    assert(x[0] == '*' && x.back() == '*');
    for (char c : x) {
      if (c != '*') {
        prefix += c;
      }
    }
  }
  return prefix + suffix;
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  int testNum;
  cin >> testNum;

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: %s\n", testId, solve().c_str());
  }

  TIMESTAMP(end);
  return 0;
}
