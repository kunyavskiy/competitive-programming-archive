#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>
#include <vector>

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


class ParallelSolver {
  string output_buffer;
  static int solved;
public:
  static int testNum;
  int _testId;

  explicit ParallelSolver(int testId) : _testId(testId) {
    printf("Case #%d: ", testId);
  }

  __attribute__((format(printf, 2, 3)))
  void printf(const char *format, ...) {
    va_list ap;
    va_start (ap, format);
    char *output_part;
    vasprintf(&output_part, format, ap);
    output_buffer += output_part;
    free(output_part);
    va_end (ap);
  }

  virtual void solve() = 0;

  string run() {
    solve();
#pragma omp critical
    {
      solved++;
      if ((solved - 1) * 100 / testNum != solved * 100 / testNum || solved <= 20 || testNum - solved <= 20)
        TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", solved * 100 / testNum, solved, testNum, testNum - solved);
    }
    return std::move(output_buffer);
  }
};

int ParallelSolver::solved;
int ParallelSolver::testNum;

void PreCalc() {
}

class Solver : public ParallelSolver {
  vector<int> a;
  vector<int> b;
  vector<int> x;
  vector<int> y;
public:
  explicit Solver(int _testId) : ParallelSolver(_testId) {
    int n, m;
    scanf("%d%d", &n, &m);
    a.resize(n);
    b.resize(n - 1);
    x.resize(m);
    y.resize(m);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n - 1; i++) {
      scanf("%d", &b[i]);
    }
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &x[i], &y[i]);
      --x[i];
    }
  }

  void solve() override {
    int n = a.size();
    vector<vector<long long>> dpl(n, vector<long long>(n + 1));
    vector<vector<long long>> dpr(n, vector<long long>(n + 1));
    vector<vector<long long>> mx(n - 1, vector<long long>(n));
    for (int i = 0; i < n - 1; i++) {
      mx[i][i + 1] = b[i];
      for (int j = i + 1; j < n - 1; j++) {
        mx[i][j + 1] = max(mx[i][j], (ll) b[j]);
      }
    }

    vector<long long> asum(n + 1);
    for (int i = 0; i < n; i++) {
      asum[i + 1] = asum[i] + a[i];
    }
    vector<long long> bsum(n);
    for (int i = 0; i < n - 1; i++) {
      bsum[i + 1] = bsum[i] + b[i];
    }

    auto left = [&](int l, int r) {
      assert(l);
      long long have = asum[r] - asum[l];
      long long need = bsum[r - 1] - bsum[l - 1];
      return need - have;
    };
    auto right = [&](int l, int r) {
      long long have = asum[r] - asum[l];
      long long need = bsum[r] - bsum[l];
      return need - have;
    };
    auto change = [&](int l, int r) {
      if (l == r - 1) return 0LL;
      long long have = asum[r] - asum[l];
      long long need = bsum[r - 1] - bsum[l] + mx[l][r - 1];
      return need - have;
    };

    dpl[0][n] = dpr[0][n] = 0;

    for (int l = n - 1; l >= 1; l--) {
      for (int i = 0; i + l <= n; i++) {
        int j = i + l;
        dpl[i][j] = 1LL << 60;
        dpr[i][j] = 1LL << 60;
        if (i) {
          dpl[i][j] = min(dpl[i][j], max(dpl[i - 1][j], left(i, j)));
        }
        if (j != n) {
          dpr[i][j] = min(dpr[i][j], max(dpr[i][j + 1], right(i, j)));
        }
        dpl[i][j] = min(dpl[i][j], max(dpr[i][j], change(i, j)));
        dpr[i][j] = min(dpr[i][j], max(dpl[i][j], change(i, j)));
      }
    }

//    for (int i = 0; i < n; i++) {
//      for (int j = 0; j <= n; j++) {
//        eprintf("%3lld/%3lld ", dpl[i][j], dpr[i][j]);
//      }
//      eprintf("\n");
//    }

    for (int i = 0; i < (int)x.size(); i++) {
      printf("%s", (min(dpl[x[i]][x[i] + 1], dpr[x[i]][x[i] + 1]) <= y[i]) ? "Y" : "N");
    }
    printf("\n");
  }

};

int main() {
#ifdef LOCAL
//  freopen("e.in", "r", stdin);
//  freopen("e.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &ParallelSolver::testNum);

  vector<std::unique_ptr<Solver>> solvers(ParallelSolver::testNum);

  for (int i = 0; i < ParallelSolver::testNum; i++) {
    solvers[i] = make_unique<Solver>(i + 1);
  }

  vector<std::string> results(ParallelSolver::testNum);

//#pragma omp parallel for
  for (int i = 0; i < ParallelSolver::testNum; i++) {
    results[i] = solvers[i]->run();
    solvers[i] = nullptr;
  }

  for (const auto &result : results) {
    printf("%s", result.c_str());
  }

  TIMESTAMP(end);
  return 0;
}
