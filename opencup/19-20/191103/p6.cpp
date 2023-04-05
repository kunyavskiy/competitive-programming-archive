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

int main() {
#ifdef LOCAL
  freopen("p6.in", "r", stdin);
  freopen("p6.out", "w", stdout);
#endif

  int n, k, S;
  ll P;
  while (scanf("%d%d%d%lld", &n, &k, &S, &P) == 4) {
    vector<ld> two(n), one(n);
    for (int i = 0; i < n; i++) {
      vector<double> x(3);
      scanf("%lf%lf%lf", &x[0], &x[1], &x[2]);
      sort(x.begin(), x.end());
      ld log3 = 0;
      ld log2 = log(x[1] + x[2]);
      ld log1 = log(x[2]);
      two[i] = log3 - log2;
      one[i] = log3 - log1;
    }
    auto get_cost = [&](int d, int t) {
      using pq = std::priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>>;
      pq to_second;
      pq to_first;
      pq second_to_first;
      for (int i = 0; i < n; i++) {
        to_second.emplace(two[i], i);
        to_first.emplace(one[i], i);
      }
      int o = n - d - t;
      vector<int> type(n);
      vector<int> cnt(3);
      cnt[0] = n;
      double tot_cost = 0;
      for (int i = 0; i < o + d; i++) {
        while (!to_second.empty() && type[to_second.top().second] != 0) {
          to_second.pop();
        }
        while (!to_first.empty() && type[to_first.top().second] != 0) {
          to_first.pop();
        }
        while (!second_to_first.empty() && type[second_to_first.top().second] != 1) {
          second_to_first.pop();
        }
        vector<double> costs(3, 1e100);
        if (!to_second.empty() && cnt[1] < d) {
          costs[0] = to_second.top().first;
        }
        if (!to_first.empty() && cnt[2] < o) {
          costs[1] = to_first.top().first;
        }
        if (!to_second.empty() && !second_to_first.empty() && cnt[2] < o) {
          costs[2] = to_second.top().first + second_to_first.top().first;
        }
        int op_id = min_element(costs.begin(), costs.end()) - costs.begin();
        tot_cost += costs[op_id];
        if (op_id == 0) {
          int id = to_second.top().second;
          type[id] = 1;
          second_to_first.emplace(one[id] - two[id], id);
          cnt[0]--;
          cnt[1]++;
        } else if (op_id == 1) {
          type[to_first.top().second] = 2;
          cnt[0]--;
          cnt[2]++;
        } else if (op_id == 2) {
          int id = to_second.top().second;
          type[id] = 1;
          type[second_to_first.top().second] = 2;
          second_to_first.emplace(one[id] - two[id], id);
          cnt[0]--;
          cnt[2]++;
        }
      }
      ld res = exp(-tot_cost);
      eprintf("%d %d %Lf\n", t, d, res);
      return res;
    };
    vector<pair<int, ld>> costs;
    for (int i = 0; i < k; i++) {
      int d, t, c;
      scanf("%d%d%d", &d, &t, &c);
      costs.emplace_back(c, get_cost(d, t));
    }
    vector<ld> best(S + 1);
    for (int i = 1; i <= S; i++) {
      for (auto [c, w] : costs) {
        if (c <= i) {
          best[i] = max(best[i], best[i - c] + w);
        }
      }
    }
    printf("%.18f\n", (double)*max_element(best.begin(), best.end()) * P);
  }

  return 0;
}
