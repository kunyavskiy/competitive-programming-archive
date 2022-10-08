#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

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


int s, e;

struct state {
  int min_up, max_up;
  int max_left, min_right;
  int count;

  state down(int x, int y) {
    int nmax_left = max_left;
    int nmin_right = min_right;
    if (y >= s) nmax_left = min(nmax_left, x);
    if (y >= e) nmin_right = max(nmin_right, x);
    return {min_up, max_up, nmax_left, nmin_right, count};
  }

  state up(int , int ) {
    return {min_up, max_up, max_left, min_right, count};
  }

  state left(int x, int y) {
    return {y >= s ? min_up : max(min_up, x), max_up, max_left, min_right, count};
  }

  state right(int x, int y) {
    return {min_up, y >= e ? max_up: min(max_up, x), max_left, min_right, count};
  }

};

bool operator<(const state &lhs, const state &rhs) {
  return std::tie(lhs.min_up, lhs.max_up, lhs.max_left, lhs.min_right) <
         std::tie(rhs.min_up, rhs.max_up, rhs.max_left, rhs.min_right);
}

bool operator==(const state &lhs, const state &rhs) {
  return std::tie(lhs.min_up, lhs.max_up, lhs.max_left, lhs.min_right) ==
         std::tie(rhs.min_up, rhs.max_up, rhs.max_left, rhs.min_right);
}

bool operator!=(const state &lhs, const state &rhs) {
  return !(rhs == lhs);
}

void solve() {
  int n;
  scanf("%d%d%d", &n, &s, &e);

  vector<pair<int, int>> ps(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &ps[i].first, &ps[i].second);
  }

  /*if (s > e) {
    swap(s, e);
    for (int i = 0; i < n; i++) {
      ps[i].first = 1e9 - ps[i].first;
    }
  }*/

  sort(ps.begin(), ps.end(), [](const pair<int, int> &a, const pair<int, int> &b) { return a.second > b.second; });

  vector<state> sts;
  sts.push_back({0, (int)1e9, (int)1e9, 0, 1});

  for (auto p : ps) {
    vector<state> nst;
    eprintf("====\n");

    for (state s : sts) {
      nst.push_back(s.down(p.first, p.second));
      if (p.first <= s.max_left) {
        nst.push_back(s.left(p.first, p.second));
      } else {
        eprintf("(%d, %d) can't left for [%d,%d,%d,%d:%d]\n", p.first, p.second, s.min_up, s.max_up, s.max_left, s.min_right, s.count);
      }
      if (p.first >= s.min_right) {
        nst.push_back(s.right(p.first, p.second));
      } else {
        eprintf("(%d, %d) can't right for [%d,%d,%d,%d:%d]\n", p.first, p.second, s.min_up, s.max_up, s.max_left, s.min_right, s.count);
      }
      if (s.min_up <= p.first && p.first <= s.max_up) {
        nst.push_back(s.up(p.first, p.second));
      } else {
        eprintf("(%d, %d) can't up for [%d,%d,%d,%d:%d]\n", p.first, p.second, s.min_up, s.max_up, s.max_left, s.min_right, s.count);
      }
    }
    for (state s : nst) {
      eprintf("[%d,%d,%d,%d:%d], ", s.min_up, s.max_up, s.max_left, s.min_right, s.count);
    }
    eprintf("\n==\n");
    sort(nst.begin(), nst.end());
    int ptr = 0;
    for (int i = 0; i < (int)nst.size(); i++) {
      if (ptr && nst[ptr-1] == nst[i]) {
        add(nst[ptr - 1].count, nst[i].count);
      } else {
        nst[ptr++] = nst[i];
      }
    }
    nst.resize(ptr);
    for (state s : nst) {
      eprintf("[%d,%d,%d,%d:%d], ", s.min_up, s.max_up, s.max_left, s.min_right, s.count);
    }
    eprintf("\n");
    sts = nst;
  }

  int ans = mpow(4, n);
  for (state s : sts) {
    sub(ans, s.count);
  }

  printf("%d\n", ans);

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
