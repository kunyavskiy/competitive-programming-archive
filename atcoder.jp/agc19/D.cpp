#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <algorithm>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


int solve(string A, string B, int len) {
  B = B + B;
  int ans = 1e9;
  vector<int> l(len), r(len);

  int last = 2 * len;
  for (int i = 2 * len - 1; i >= 0; i--) {
    if (B[i] == '1') {
      last = i;
    }
    if (i < len) {
      assert(last != 2 * len);
      r[i] = last - i;
    }
  }
  last = -1;
  for (int i = 0; i < 2 * len; i++) {
    if (B[i] == '1') {
      last = i;
    }
    if (i >= len) {
      assert(last != -1);
      l[i - len] = i - last;
    }
  }

  for (int shift = 0; shift <= len; shift++) {
    vector<bool> need(len);
    int cnt = 0;
    for (int i = 0; i < len; i++) {
      need[i] = (A[i] != B[i + shift]);
      cnt += need[i];
    }

    vector<pair<int, int>> v;
    for (int i = 0; i < len; i++) {
      if (need[i]) {
        v.push_back({l[i], r[i]});
      }
    }
    sort(v.rbegin(), v.rend());
    int rv = shift;

    for (int i = 0; i < (int) v.size(); i++) {
      ans = min(ans, 2 * (v[i].first + rv) - shift + cnt);
      rv = max(rv, v[i].second);
    }
    ans = min(ans, 2 * rv - shift + cnt);
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  static char A[2010], B[2010];
  while (scanf("%s%s", A, B) == 2) {
    int n = strlen(A);
    if (find(B, B + n, '1') == B + n) {
      if (find(A, A + n, '1') != A + n) {
        printf("-1\n");
        continue;
      } else {
        printf("0\n");
        continue;
      }
    }
    int ans1 = solve(A, B, n);
    reverse(A, A + n);
    reverse(B, B + n);
    int ans2 = solve(A, B, n);
    printf("%d\n", min(ans1, ans2));
  }

  return 0;
}
