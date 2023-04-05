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
typedef pair<ll, double> pld;

struct State {
  ll mask;
  double prob;
};

static inline ll shiftMask(int n, ll mask, int shift) {
  if (shift < 0) {
    shift += n;
  }
  return ((mask & ((1LL << shift) - 1)) << (n - shift)) | (mask >> shift);
}

static inline ll normalizeMask(ll mask) {
  ll badMask = (mask & (mask>>1));
  int L = __builtin_ctzll(badMask);
  int R = 63 - __builtin_clzll(badMask);
  ll new_mask =  mask | (((1LL << (R - L + 1)) - 1) << L);
//  eprintf("%llx %llx L %d R %d\n", mask, new_mask, L, R);
  return new_mask ;
}

double solve(int n) {
  vector<State> q;
  q.push_back({0, 1.0});
  double ans = 0.0;
  int cnt = 0;
  while (!q.empty()) {
    ++cnt;
    vector <State> q2;
    for (auto it : q) {
      auto mask = it.mask;
      auto prob = it.prob;
      for (int i = -2; i <= 2; ++i) {
        if (i == 0) { continue; }
        ll new_mask = shiftMask(n, mask|1, i);
        if (new_mask & 1) {
          ans += prob * cnt / 4.0;
        } else {
          q2.push_back({normalizeMask(new_mask), prob / 4.0});
        }
      }
    }
    sort(q2.begin(), q2.end(), [](const State & st1, const State &st2) { return st1.mask < st2.mask; });
    q.clear();
    for (auto it : q2) {
      if (q.empty() || q.back().mask != it.mask) {
        q.push_back(it);
      } else {
        q.back().prob += it.prob;
      }
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  printf("%.15lf\n", solve(n));

  for (int i = 2; i <= 50; ++i) {
    printf("%d %.10lf\n", i, solve(i));
    fflush(stdout);
  }

  return 0;
}
