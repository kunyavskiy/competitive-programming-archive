#include <iostream>
#include <fstream>
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

void pre_order(int v, const vector<int> &a, const vector<int> &b, vector<int> &o) {
  if (v == -1) return;
  o.push_back(v);
  pre_order(a[v], a, b, o);
  pre_order(b[v], a, b, o);
}

void post_order(int v, const vector<int> &a, const vector<int> &b, vector<int> &o) {
  if (v == -1) return;
  post_order(a[v], a, b, o);
  post_order(b[v], a, b, o);
  o.push_back(v);
}


void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<int> a(n);
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
  }
  vector<int> o1, o2;
  pre_order(0, a, b, o1);
  post_order(0, a, b, o2);

  vector<int> perm(n);
  for (int i = 0; i < n; i++) {
    perm[o1[i]] = o2[i];
  }

  vector<int> ans(n, -1);
  int l = 0;
  for (int i = 0; i < n; i++) {
    if (ans[i] != -1) continue;
    int cur = (l % k) + 1;
    l++;
    for (int j = i; ans[j] == -1; j = perm[j]) {
      ans[j] = cur;
    }
  }

  if (l < k) {
    printf("Impossible\n");
  } else {
    for (int x : ans) {
      printf("%d ", x);
    }
    printf("\n");
  }
}


int main() {
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);

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
