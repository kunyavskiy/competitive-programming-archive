#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

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

vector<pair<int, int>> parse_line() {
  vector<pair<int, int>> res;
  char buf[100];
  for (int i = 0; i < 10; i++) {
    scanf(" %[^,\r\n]", buf);
    if (!strcmp(buf, "-")) {
      res.emplace_back(-1, -1);
    } else {
      int a, b;
      sscanf(buf, "%d%d", &a, &b);
      res.emplace_back(a, b);
    }
    if (i != 9) {
      scanf(" ,");
    }
  }
  return res;
}

vector<int> get_result(vector<pair<int, int>> ts) {
  vector<int> res(2);
  for (auto x : ts) {
    if (x.first != -1) {
      res[0]--;
      res[1] += x.first + x.second * 20;
      res.push_back(x.first);
    }
  }
  sort(res.begin() + 2, res.end(), greater<int>());
  return res;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<vector<pair<int, int>>> teams;

  for (int i = 0; i < n; i++) {
    teams.push_back(parse_line());
  }

  for (auto &team : teams) {
    for (auto x : team) {
      eprintf("%d:%d ", x.first, x.second);
    }
    eprintf("\n");
  }

  vector<int> ps(10);
  for (int i = 0; i < 10; i++) {
    ps[i] = i;
  }

  auto our = teams.back();
  teams.pop_back();

  vector<vector<int>> team_results;
  for (const auto &x : teams) {
    team_results.push_back(get_result(x));
  }
  sort(team_results.begin(), team_results.end());

  vector<int> min_prob_time(10, 301);
  int global_min_prob_time = 301;
  int global_max_prob_time = -1;
  for (int i = 0; i < 10; i++) {
    for (const auto&x : teams) {
      if (x[i].first != -1) {
        min_prob_time[i] = min(min_prob_time[i], x[i].first);
        global_min_prob_time = min(global_min_prob_time, x[i].first);
        global_max_prob_time = max(global_max_prob_time, x[i].first);
      }
    }
  }

  int ans = 0;

  do {
    int res = 0;
    int curt = 0;
    vector<pair<int, int>> team(10, {-1, -1});
    bool f = false;
    bool any = false;
    for (int x : ps) {
      if (our[x].first == -1) continue;
      if (curt + our[x].first > 300) break;
      curt += our[x].first;
      team[x] = {curt, our[x].second};
      if (!f && curt <= global_min_prob_time) {
        res += 700;
        f = true;
      }
      if (curt <= min_prob_time[x]) {
        res += 800;
      }
      any = true;
    }
    if (any && curt >= global_max_prob_time) {
      res += 500;
    }

    auto team_res = get_result(team);
    int id = lower_bound(team_results.begin(), team_results.end(), team_res) - team_results.begin();
    res += 5000 / (id + 1);
    if (id < n / 10) {
      res += 1200;
    } else if (id < 3 * n / 10) {
      res += 800;
    } else if (id < 6 * n / 10) {
      res += 400;
    }

    ans = max(ans, res);
  } while (next_permutation(ps.begin(), ps.end()));

  printf("%d\n", ans);

  return 0;
}
