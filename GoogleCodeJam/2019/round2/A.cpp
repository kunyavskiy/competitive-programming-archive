#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

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

struct pt {
  int x, y;
  bool operator<(const pt& other) const {
    return tie(y, x) < tie(other.y, other.x);
  }
};

struct rat {
  int x, y;
  bool operator<(const rat & other) const {
    return x * 1LL * other.y < y * 1LL * other.x;
  }

  bool operator==(const rat& other) const {
    return x * 1LL * other.y == y * 1LL * other.x;
  }
};

void solve() {
  int n;
  scanf("%d", &n);
  vector<pt> v(n);
  for (pt &p : v) {
    scanf("%d%d", &p.x, &p.y);
  }
  sort(v.begin(), v.end());

  vector<rat> events;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int dx = v[j].x - v[i].x;
      int dy = v[j].y - v[i].y;
      if (dx >= 0 && dy >= 0) {
        continue;
      }
      events.push_back({abs(dx), abs(dy)});
    }
  }

  sort(events.begin(), events.end());
  events.erase(unique(events.begin(), events.end()), events.end());

  printf("%d\n", (int)events.size() + 1);
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
