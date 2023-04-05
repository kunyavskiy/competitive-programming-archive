#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "H"

#ifdef LOCAL
static struct __timestamper {
    string what;
    __timestamper(const char* what) : what(what){};
    __timestamper(const string& what) : what(what){};
	~__timestamper(){
        TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct RangeTree {
  int kk;
  vector <double> sum;
  vector <double> factor;

  RangeTree() {}
  RangeTree(const vector <double> & v) {
    int n = int(v.size());
    kk = 1;
    while (kk < n) {
      kk *= 2;
    }
    sum.assign(2 * kk + 10, 0.0);
    factor.assign(2 * kk + 10, 1.0);

    for (int i = 0; i < n; ++i) {
      sum[i + kk] = v[i];
    }
    for (int i = kk - 1; i >= 1; --i) {
      sum[i] = sum[2 * i] + sum[2 * i + 1];
    }
  }

  double getSum(int L, int R) {
    return getSum(1, 0, kk - 1, L, R);
  }

  void mult(int L, int R, double x) {
    mult(1, 0, kk - 1, L, R, x);
  }

  double getSum(int t, int Lt, int Rt, int L, int R) {
    if (Rt < L || R < Lt) {
      return 0.0;
    }
    if (L <= Lt && Rt <= R) {
      return sum[t];
    }
    pushModify(t);
    int Mt = (Lt + Rt) / 2;
    return getSum(2 * t, Lt, Mt, L, R) + getSum(2 * t + 1, Mt + 1, Rt, L, R);
  }

  void mult(int t, int Lt, int Rt, int L, int R, double x) {
    if (Rt < L || R < Lt) {
      return;
    }
    if (L <= Lt && Rt <= R) {
      multEntire(t, x);
      return;
    }
    pushModify(t);
    int Mt = (Lt + Rt) / 2;
    mult(2 * t, Lt, Mt, L, R, x);
    mult(2 * t + 1, Mt + 1, Rt, L, R, x);
    update(t);
  }

  void update(int t) {
    sum[t] = sum[2 * t] + sum[2 * t + 1];
  }

  void pushModify(int t) {
    multEntire(2 * t, factor[t]);
    multEntire(2 * t + 1, factor[t]);
    factor[t] = 1.0;
  }

  void multEntire(int t, double x) {
    sum[t] *= x;
    factor[t] *= x;
  }
};

bool solve() {
  int n, m;
  if (scanf("%d%d", &n, &m) != 2) { return false; }
  eprintf("%d %d\n", n, m);
  vector <double> p(n);
  for (int i = 0; i < n; ++i) {
    scanf("%lf", &p[i]);
  }

  vector <double> powP(n, 1.0);
  const int K = 15;
  vector <RangeTree> trees(K + 1);
  for (int j = 1; j <= K; ++j) {
    for (int i = 0; i < n; ++i) {
      powP[i] *= -p[i];
    }
    trees[j] = RangeTree(powP);
  }

  for (int i = 0; i < m; ++i) {
    int t, L, R;
    scanf("%d%d%d", &t, &L, &R);
    --L, --R;
    if (t == 0) {
      double res = 0, factor = -1.0;
      for (int j = 1; j <= K; ++j) {
        factor *= -1.0;
        res += trees[j].getSum(L, R) / (factor * j);
      }
      printf("%.20lf\n", res);
    } else {
      double X;
      scanf("%lf", &X);
      double powX = 1.0;
      for (int j = 1; j <= K; ++j) {
        powX *= X;
        trees[j].mult(L, R, powX);
      }
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  while(solve());

  return 0;
}
