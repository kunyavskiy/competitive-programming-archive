#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

int mfrac(int a, int b) {
  return mul(a,minv(b));
}

void out(int x) {
  for (int i = 1; i <= 100; i++) {
    if (mul(x,i) <= 100) {
      eprintf("%d[%d/%d]", x, mul(x, i), i);
      return;
    }
  }
  eprintf("%d[??]", x);
}

void PreCalc() {
}

int solve(int n, int k, int h1, int h2, int hlca) {
  int ans = 0;

  auto prob_forb = [&](int cnt_forbidden, int top) {
    int prob = mpow(mfrac(n - cnt_forbidden - 1, n - 1), k);
    int prob2 = 1;
    if (top == 1) {
      sub(prob2, mpow(mfrac(n - cnt_forbidden - 1 - top, n - cnt_forbidden - 1), k));
    } else if (top == 2) {
      add(prob2, mpow(mfrac(n - cnt_forbidden - 1 - 2, n - cnt_forbidden - 1), k));
      sub(prob2, mpow(mfrac(n - cnt_forbidden - 1 - 1, n - cnt_forbidden - 1), k));
      sub(prob2, mpow(mfrac(n - cnt_forbidden - 1 - 1, n - cnt_forbidden - 1), k));
    }
    prob = mul(prob, prob2);
    return prob;
  };

  // 1 - ((n - 1) / n) ^ k
  int tot_prob = 0;
  for (int i = 0; i<= h1; i++) {
    for (int j = 0; j <= h2; j++) {
      if (i <= hlca && j <= hlca) {
        if (i != j) continue;
        int d = h1 + h2 - 2 * hlca;
        int prob = prob_forb(h1 + h2 - hlca - i, i != 0);
        add(tot_prob, prob);
        add(ans, mul(d, prob));
      } else {
        int d = (h1 - i + (i != 0)) + (h2 - j + (j != 0));
        int prob = 1;
        prob = mul(prob, prob_forb(h1 - i + h2 - j, (i != 0) + (j != 0)));
        add(tot_prob, prob);
        add(ans, mul(d, prob));
      }
    }
  }

  assert(tot_prob == 1);

//  out(ans);
//  eprintf("\n");

  return ans;
}

void solve() {
  int n, k, a, b;
  scanf("%d%d%d%d", &n, &k, &a, &b);
  --a, --b;
  vector<int> p(n);
  p[0] = -1;
  for (int i = 1; i < n; i++) {
    scanf("%d", &p[i]);
    --p[i];
  }
  vector<int> es1, es2;
  while (a != 0) {
    es1.push_back(a);
    a = p[a];
  }
  while (b != 0) {
    es2.push_back(b);
    b = p[b];
  }
  reverse(es1.begin(), es1.end());
  reverse(es2.begin(), es2.end());

  int cnt = 0;
  while (cnt < (int)es1.size() && cnt < (int)es2.size() && es1[cnt] == es2[cnt]) {
    cnt++;
  }
  printf("%d\n", solve(n, k, es1.size(), es2.size(), cnt));

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
