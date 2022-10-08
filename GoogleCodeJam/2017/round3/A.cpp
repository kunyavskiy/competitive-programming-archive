#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

int f[15];

int get_next(int x, int L) {
  static int cnt[10];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 0; i < L; i++) {
    if (x % 10) {
      cnt[(x % 10) - 1]++;
    }
    x /= 10;
  }
  x = 0;
  for (int i = L; i >= 1; i--) {
    x = (x * 10 + cnt[i]);
  }
  return x;
}

void PreCalc() {
  f[0] = 1;
  for (int i = 1; i <= 10; i++) {
    f[i] = f[i - 1] * i;
  }
}

set<int> anss;
int add_ans = 0;

void go(int n, int l) {
  if (anss.find(n) != anss.end()) {
    return;
  }
  anss.insert(n);

  static int d[10];

  int sum = 0;

  for (int i = 0; i < l; i++) {
    d[i] = n % 10;
    n /= 10;
    sum += d[i];
  }
  reverse(d, d + l);

  if (sum > l) {
    return;
  }

  int ssum = 0;

  vector<int> dd;
  for (int i = sum; i < l; i++) {
    dd.push_back(0);
  }
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < d[i]; j++) {
      dd.push_back(i + 1);
      ssum += i + 1;
    }
  }
  if (ssum > l) {
    int res = f[l] / f[l - sum];
    for (int i = 0; i < l; i++) {
      res /= f[d[i]];
    }
    add_ans += res;
  } else {
    do {
      int x = 0;
      for (int i = 0; i < l; i++) {
        x = 10 * x + dd[i];
      }
      go(x, l);
    } while (next_permutation(dd.begin(), dd.end()));
  }
}

void solve() {
  int l, n;
  static char s[100];
  scanf("%s", s);
  l = strlen(s);
  sscanf(s, "%d", &n);

  eprintf("%s\n", s);

  add_ans = 0;
  anss.clear();
  go(n, l);

  printf("%d\n", (int)anss.size() + add_ans);
}


int main() {
//  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);

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