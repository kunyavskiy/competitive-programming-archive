#include <iostream>
#include <fstream>
#include <cassert>

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

void fix(string &s) {
  int pt = 0;
  while (pt < (int)s.size() && s[pt] == '0') pt++;
  assert(pt != (int)s.size());
  s = s.substr(pt, string::npos);
}

void solve() {
  string s, t;
  cin >> s;
  t = string(s.size(), '0');
  bool any = false;
  for (int i = 0; i < (int)s.size(); i++) {
    if (s[i] > '0' + !i) {
      for (int j = 1; '0' + j <= s[i]; j++) {
        if (j != 4 && s[i] - j != '4') {
          t[i] += j;
          s[i] -= j;
          any = true;
          break;
        }
      }
    }
  }
  if (!any) {
    t.back() = '1';
    s[0] = '0';
    for (int i = 1; i < (int)s.size(); i++) {
      s[i] = '9';
    }
  }

  fix(s);
  fix(t);
  printf("%s %s\n", s.c_str(), t.c_str());
}


int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
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
