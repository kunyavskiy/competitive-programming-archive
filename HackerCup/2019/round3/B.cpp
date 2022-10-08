#include <iostream>
#include <fstream>
#include <vector>
#include <map>

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

const int MAXC = 1e9;
vector<int> primes;

void PreCalc() {
  vector<bool> is_prime(1e5, true);
  for (int i = 2; i * i < MAXC; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      for (int j = 2 * i; j < (int)is_prime.size(); j += i) {
        is_prime[j] = false;
      }
    }
  }
}

void solve() {
  map<int, pair<int, int>> x;
  auto init = [&](int p) {
    if (x.find(p) == x.end()) {
      x[p] = {0, 100};
    }
  };
  auto le = [&](int p, int d) {
    init(p);
    x[p].second = min(x[p].second, d);
  };
  auto ge = [&](int p, int d) {
    if (!d) return;
    init(p);
    x[p].first = max(x[p].first, d);
  };
  auto eq = [&](int p, int d) {
    le(p, d);
    ge(p, d);
  };
  auto fail = [&](int p) {
    le(p, 1);
    ge(p, 2);
  };

  auto count_gcd = [&](int p, int da, int db) {
    if (p == 1) return;
    if (da == db) {
      ge(p, db);
    } else if (da > db){
      eq(p, db);
    } else {
      fail(p);
    }
  };
  auto count_lcm = [&](int p, int da, int db) {
    if (p == 1) return;
    if (da == db) {
      le(p, db);
    } else if (da < db) {
      eq(p, db);
    } else {
      fail(p);
    }
  };


  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    char c;
    int a, b;
    scanf(" %c %d %d", &c, &a, &b);

    auto count = [&](int p, int da, int db) {
      if (c == 'G') {
        count_gcd(p, da, db);
      } else {
        count_lcm(p, da, db);
      }
    };
    for (int p : primes) {
      int da, db;
      da = db = 0;
      while (a % p == 0) {
        da++;
        a /= p;
      }
      while (b % p == 0) {
        db++;
        b /= p;
      }
      count(p, da, db);
    }
    if (a == b) {
      count(a, 1, 1);
    } else {
      count(a, 1, 0);
      count(b, 0, 1);
    }
  }

  int ans = 1;
  for (auto [p, lims] : x) {
    if (lims.first > lims.second) {
      printf("-1\n");
      return;
    }
    for (int i = 0; i < lims.first; i++) {
      if (ans > MAXC / p) {
        printf("-1\n");
        return;
      }
      ans *= p;
    }
  }
  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
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
