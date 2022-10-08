#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>

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

void solve(int b) {
  int done = 0;
  auto query = [&](int x) {
    printf("%d\n", x + 1);
    fflush(stdout);
    int r;
    assert(scanf("%d", &r) == 1);
    ++done;
    return r;
  };
  string s(b, '?');
  int pt = 0;
  while (pt < b - pt) {
    if (done % 10 == 9) {
      query(1);
      continue;
    }
    if (done % 10 == 0 && done) {
      for (int i = 0; i < pt; i++) {
        if (s[i] == s[b - i - 1]) {
          if (query(i) != s[i] - '0') {
            for (int j = 0; j < b; j++) {
              if (s[j] != '?') {
                s[j] ^= 1;
              }
            }
          }
          break;
        }
      }
      for (int i = 0; i < pt; i++) {
        if (s[i] != s[b - i - 1]) {
          if (query(i) != s[i] - '0') {
            reverse(s.begin(), s.end());
          }
          break;
        }
      }
    }
    assert(done % 10 <= 8);
    s[pt] = query(pt) + '0';
    s[b - pt - 1] = query(b - pt - 1) + '0';
    pt++;
  }

  eprintf("%s\n", s.c_str());
  printf("%s\n", s.c_str());
  fflush(stdout);
  char c;
  scanf(" %c", &c);
  if (c != 'Y') {
    exit(0);
  }
}


int main() {
//#ifdef LOCAL
//  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
//#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  int b;
  sscanf(buf, "%d%d", &testNum,  &b);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    solve(b);
  }

  TIMESTAMP(end);
  return 0;
}
