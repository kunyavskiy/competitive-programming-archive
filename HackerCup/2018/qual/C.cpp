#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
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

bool bad_find(string s, string t) {
  int i, j;
  i = j = 0;
  while (true) {
    if (i >= (int)s.size()) return true;
    if (j >= (int)t.size()) return false;
    if (s[i] == t[j]) {
      i++;
      j++;
      continue;
    }
    if (i == 0) {
      j++;
      continue;
    }
    i = 0;
  }
}

void solve() {
  static char s[2010];
  scanf("%s", s);
  int n = strlen(s);
  vector<int> p(n);
  for (int i = 1; i < n; i++) {
    int j = p[i - 1];
    while (j && s[i] != s[j]) j = p[j - 1];
    if (s[i] == s[j]) j++;
    p[i] = j;
  }

  for (int i = 1; i < n - 1; i++) {
    for (char c = 'A'; c <= 'Z'; c++) {
      if (c != s[i] && c != s[0]) {
        int j = p[i - 1];
        while (j && c != s[j]) j = p[j - 1];
        if (s[j] == c) j++;
        if (j > 0) {
          string res;
          res += string(s, s + i);
          res += string(s + j - 1, s + n);
          printf("%s\n", res.c_str());
          assert(res.find(s) != string::npos);
          assert(!bad_find(s, res));
          return;
        }
      }
    }
  }
  printf("Impossible\n");
}


int main() {
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);


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
