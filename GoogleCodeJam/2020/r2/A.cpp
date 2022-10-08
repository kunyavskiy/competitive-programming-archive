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

void solve2(ll L, ll R, ll &la, ll &La, ll &Ra) {
  La = L;
  Ra = R;
  for (la = 1; la <= max(La, Ra); la++) {
    if (La >= Ra) {
      La -= la;
    } else {
      Ra -= la;
    }
  }
  la--;
}

void solve() {
  ll L, R;
  scanf("%lld%lld", &L, &R);
  ll cur = 0;

#ifdef LOCAL
  ll la, La, Ra;
  solve2(L, R, la, La, Ra);
#endif
  {
    ll diff = abs(L - R);
    ll l = 0;
    ll r = 2.1e9;
    while (r - l > 1) {
      ll m = (l + r) / 2;
      if (m * (m + 1) / 2 <= diff) {
        l = m;
      } else {
        r = m;
      }
    }

    if (L >= R) {
      cur = l;
      L -= l * (l + 1) / 2;
    } else {
      cur = l;
      R -= l * (l + 1) / 2;
    }
  }
  if (R > L && R >= cur + 1) {
    cur++;
    R -= cur;
    assert(R <= L);
  }

  auto get_mod2_sum = [](ll from, ll to) {
    if (to % 2 != from % 2) to--;
    if (to < from) return 0LL;
    ll ans =  (from + to) * 1LL * ((to - from) / 2 + 1) / 2;
    return ans;
  };

  ll l = cur;
  ll r = 2.1e9;
  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (get_mod2_sum(cur + 1, m) <= L && get_mod2_sum(cur + 2, m) <= R) {
      l = m;
    } else {
      r = m;
    }
  }

  L -= get_mod2_sum(cur + 1, l);
  R -= get_mod2_sum(cur + 2, l);
#ifdef LOCAL
  assert(l == la);
  assert(L == La);
  assert(R == Ra);
#endif
  printf("%lld %lld %lld\n", l, L, R);
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
