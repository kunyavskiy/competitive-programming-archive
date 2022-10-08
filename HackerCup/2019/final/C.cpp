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
  vector<vector<bool>> solved;
public:
  explicit Solver(int _testId) : ParallelSolver(_testId) {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
      static char buf[210];
      scanf("%s", buf);
      solved.emplace_back(m);
      for (int j = 0; j < m; j++) {
        solved[i][j] = buf[j] == 'Y';
      }
    }
  }

  void solve() override {
    int m = solved[0].size();
    int n = solved.size();
    for (int f = 1; f < n; f++) {
      vector<bool> won(n);
      won[0] = won[f] = true;
      for (int i = 0; i < m; i++) {
        if (solved[0][i] && solved[f][i]) {
          for (int p = 1; p < n; p++) {
            if (!solved[p][i]) {
              won[p] = true;
            }
          }
        }
      }
      bool found = false;
      for (int i = 0; i < m; i++) {
        if (!solved[0][i] && solved[f][i]) {
          bool ok = true;
          for (int p = 0; p < n; p++) {
            if (!won[p] && solved[p][i]) {
              ok = false;
              break;
            }
          }
          if (ok) {
            found = true;
            break;
          }
        }
      }
      if (!found) {
        continue;
      }
      for (int i = 0; i < m; i++) {
        if (solved[0][i]) {
          for (int p = 1; p < n; p++) {
            if (!solved[p][i]) {
              won[p] = true;
            }
          }
        }
      }
      if (all_of(won.begin(), won.end(), [](bool x) { return x;})) {
        printf("Y\n");
        return;
      }
    }
    printf("N\n");
  }

};

int main() {
#ifdef LOCAL
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
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

#pragma omp parallel for
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
