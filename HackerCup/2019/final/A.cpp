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

string do_solve(int k) {
  int k0 = k;
  string s;
  int cur = 0;
  while (k > 0) {
    int rem = sqrt(2 * k);
    while (rem * (rem + 1) / 2 >= k) rem--;
    while ((rem + 1) * (rem + 2) / 2 <= k) rem++;
    k -= rem * (rem + 1) / 2;
    s += string(rem, 'A' + (cur % 3));
    cur++;
  }
  assert(s.size() <= 1000);
  if (s.size() <= 100) {
    int got = 0;
    for (int i = 0; i < (int)s.size(); i++) {
      for (int j = i + 1; j <= (int)s.size(); j++) {
        string t = s.substr(i, j - i);
        string tt = t;
        reverse(tt.begin(), tt.end());
        if (t == tt) {
          got++;
        }
      }
    }
    assert(got == k0);
  }

  return s;
}

class Solver : public ParallelSolver {
  int k;
public:
  explicit Solver(int _testId) : ParallelSolver(_testId) {
    scanf("%d", &k);
  }

  void solve() override {
    printf("%s\n", do_solve(k).c_str());
  }

};

int main() {
#ifdef LOCAL
//  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
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
