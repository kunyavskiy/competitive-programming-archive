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

constexpr int muls[] = {2, 1, 2, 3, 1, 3, 3, 2, 2};
constexpr int STATES = 2 * 1 * 2 * 3 * 1 * 3 * 3 *  2 * 2;

struct go {
  int next_state;
  int cost_mul;
  int cost_add;

  go(int nextState, int costMul, int costAdd) : next_state(nextState), cost_mul(costMul), cost_add(costAdd) {
  }
  go() = default;
};

vector<go> bs[STATES];
vector<go> cs[STATES];

vector<int> decode(int state) {
  vector<int> r;
  for (int i : muls) {
    r.push_back(state % i);
    state /= i;
  }
  assert(state == 0);
  return r;
}

int encode(const vector<int>&state) {
  assert(state.size() == sizeof(muls) / sizeof(muls[0]));
  int res = 0;
  for (int i = state.size() - 1; i >= 0; i--) {
    res = res * muls[i] + state[i];
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  for (int i = 0; i < STATES; i++) {
    vector<int> state = decode(i);

    auto shift = [&](int pos) {
      state[pos] = (state[pos] + 1) % muls[pos];
      int res = encode(state);
      state[pos] = (state[pos] + muls[pos] - 1) % muls[pos];
      return res;
    };

    if (state[0] == 0) {
      bs[i].emplace_back(shift(0), 0, 1);
      cs[i].emplace_back(shift(0), 1, 0);
    }
    if (state[0] == 1) bs[i].emplace_back(shift(0), 1, 1);


    if (state[2] == 0) {
      bs[i].emplace_back(shift(2), 0, 0);
      cs[i].emplace_back(shift(2), 0, 0);
    }
    if (state[2] == 1) {
      cs[i].emplace_back(shift(2), 2, 1);
    }

    if (state[3] == 0) {
      bs[i].emplace_back(shift(3), 0, 1);
      cs[i].emplace_back(shift(3), 1, 0);
    }
    if (state[3] == 1) {
      bs[i].emplace_back(shift(3), 0, 0);
    }

    if (state[3] == 2) {
      state[7] ^= 1;
      bs[i].emplace_back(shift(3), 1, 1 + 3 * state[7]);
      state[7] ^= 1;
    }


    if (state[5] == 0) {
      bs[i].emplace_back(shift(5), 0, 0);
      cs[i].emplace_back(shift(5), 0, 0);
    }
    if (state[5] == 1) {
      cs[i].emplace_back(shift(5), 1, 0);
    }
    if (state[5] == 2) {
      state[7] ^= 1;
      bs[i].emplace_back(shift(5), 1, 1 + 3 * state[7]);
      state[7] ^= 1;
    }

    if (state[6] == 0 || state[6] == 1) {
      bs[i].emplace_back(shift(6), 0, 0);
      cs[i].emplace_back(shift(6), 0, 0);
    }
    if (state[6] == 2) {
      state[7] ^= 1;
      cs[i].emplace_back(shift(6), 2, 1 + 3 * state[7]);
      state[7] ^= 1;
    }

    if (state[8] == 0) {
      bs[i].emplace_back(shift(8), 1, 2);
      cs[i].emplace_back(shift(8), 2, 1);
    }
  }

  int ts;
  scanf("%d", &ts);
  for (int t = 1; t <= ts; t++) {
    printf("Case #%d: ", t);

    int n;
    scanf("%d", &n);
    vector<pair<int, int>> p(n);
    for (auto &x : p) {
      scanf("%d%d", &x.second, &x.first);
    }
    sort(p.begin(), p.end());

    const int INF = 1e9;

    vector<int> dp(STATES, INF);
    vector<int> ndp(STATES, INF);
    dp[encode({0, 0, 0, 0, 0, 0, 0, 0, 1})] = 0;
    dp[encode({0, 0, 0, 0, 0, 0, 0, 1, 0})] = 0;

    for (auto &x : p) {
      const auto &moves = x.second == 2 ? cs : bs;
      fill(ndp.begin(), ndp.end(), INF);
      for (int i = 0; i < STATES; i++) {
        if (dp[i] < INF) {
          for (auto &j : moves[i]) {
            ndp[j.next_state] = min(ndp[j.next_state], dp[i] + x.first * j.cost_mul + j.cost_add);
          }
        }
      }
      dp.swap(ndp);
    }

    int ans = dp[encode({0, 0, 0, 0, 0, 0, 0, 0, 1})];
    ans = min(ans, dp[encode({0, 0, 0, 0, 0, 0, 0, 1, 1})]);
    printf("%d\n", ans);
  }

  return 0;
}
