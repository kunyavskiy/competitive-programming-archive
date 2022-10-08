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

struct Solver {
  explicit Solver(int n) {}
  vector<bool> finished;
  vector<int> decreased;
  int todo;

  int result(int val) {
    if (val) {
      decreased[todo]++;
    } else {
      finished[todo] = true;
    }
  }

  int get_next() {
    return 0;
  }

  pair<int, int> get_answer() {
    return {0, 1};
  }
};


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, t, c;
  scanf("%d%d%d", &n, &t, &c);
  vector<Solver> solvers(t, Solver(n));

  while (true) {
    bool any = false;
    for (int i = 0; i < t; i++) {
      int t = solvers[i].get_next();
      printf("%d ", t);
      any = any || t;
    }
    printf("\n");
    fflush(stdout);
    if (!any) break;
    for (int i = 0; i < t; i++) {
      int a;
      scanf("%d", &a);
      solvers[i].result(a);
    }
  }

  for (int i = 0; i < t; i++) {
    auto x = solvers[i].get_answer();
    printf("%d %d ", x.first, x.second);
  }
  printf("\n");
  fflush(stdout);

  return 0;
}
