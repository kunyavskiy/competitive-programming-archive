#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <set>

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

vector<pair<int, int>> gen_rand(int n) {
  vector<int> p1(n), p2(n);

  for (int i = 0; i < n; i++) {
    p1[i] = p2[i] = i;
  }

  do {
    random_shuffle(p1.begin(), p1.end());
    random_shuffle(p2.begin(), p2.end());

    vector<pair<int, int>> es;
    for (int i = 0; i < n; i++) {
      es.push_back({min(i, p1[i]), max(i, p1[i])});
      es.push_back({min(i, p2[i]), max(i, p2[i])});
    }
    sort(es.begin(), es.end());
    if (unique(es.begin(), es.end()) == es.end()) {
      return es;
    }
  } while (true);
}

void solve_real(int n) {
  do {
    auto es = gen_rand(n);
    eprintf("rand\n");
    set<vector<pair<int, int>>> s;
    vector<int> p(n);

    for (int i = 0; i < n; i++) {
      p[i] = i;
    }

    bool fail = false;

    do {
      vector<pair<int, int>> ees;
      for (auto x : es) {
        ees.push_back({min(p[x.first], p[x.second]), max(p[x.first], p[x.second])});
      }
      sort(ees.begin(), ees.end());
      if (!s.insert(ees).second) {
        fail = true;
      } else if (s.size() % 1000 == 0){
        eprintf("checked %d\n", (int)s.size());
      }
    } while (!fail && next_permutation(p.begin(), p.end()));

    if (!fail) {
      eprintf("succes:\n");
      for (auto x : es) {
        eprintf("%d %d\n", x.first, x.second);
      }
      return;
    } else {
      eprintf("fail:\n");
    }
  } while (true);
}

void solve() {
  int l, r;
  scanf("%d%d", &l, &r);
  solve_real(l + rand() % (r - l + 1));
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
