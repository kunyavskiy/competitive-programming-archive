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
  string s, t;
  int n, m;
public:
  explicit Solver(int _testId) : ParallelSolver(_testId) {
    static char buf[1'100'000];
    scanf("%d%d", &n, &m);
    scanf("%s", buf);
    s = buf;
    scanf("%s", buf);
    t = buf;
  }

  void solve() override {
    auto get_pos = [&](int st, const string& s) {
      string s_part = s.substr(st * m + 1, m);
      reverse(s_part.begin(), s_part.end());
      vector<int> pos;
      for (int i = 0; i < m; i++) {
        if (s_part[i] == 'A'){
          pos.push_back(i);
        }
      }
      return pos;
    };

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      vector<int> poss = get_pos(i, s);
      vector<int> post = get_pos(i, t);
      while (poss.size() < post.size()) poss.push_back(m);
      while (post.size() < poss.size()) post.push_back(m);
      for (int i = 0; i < (int)poss.size(); i++) {
        ans += abs(poss[i] - post[i]);
      }
    }
    printf("%lld\n", ans);
  }

};

int main() {
#ifdef LOCAL
//  freopen("b.in", "r", stdin);
//  freopen("b.out", "w", stdout);
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
