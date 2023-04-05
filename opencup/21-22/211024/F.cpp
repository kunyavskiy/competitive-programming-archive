#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
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
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_set>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

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
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif


  vector<unordered_set<int>> s(1e6);
  vector<bool> v(1e6);
  int cur_bad = v.size() - 1;
  auto add = [&](ll x) {
    for (int i = 1; i < 1e6; i++) {
      if (!v[i]) {
        if (!s[i].insert((int)(x % i)).second) {
          v[i] = true;
          cur_bad--;
        }
      }
    }
  };

  vector<ll> x;
  mt19937_64 rnd;
  uniform_int_distribution<ll> dis(0, 5e18);
  for (int i = 0; i < 700; i++) {
    uniform_int_distribution<ll> dis2(0, 2e9);
    ll y = dis2(rnd);
    x.push_back(y * y);
    add(x.back());
  }

  while (x.size() < 900) {
    ll best = dis(rnd);
    int best_res = 0;
    for (int it = 0; it < 10; it++) {
      ll cand = dis(rnd);
      int res = 0;
      for (int i = 1; i < 1e6; i++) {
        if (!v[i] && s[i].count(cand % i)) {
          res++;
        }
      }
      if (res > best_res) {
        best_res = res;
        best = cand;
      }
    }
    x.push_back(best);
    add(x.back());
    TIMESTAMPf("i = %d, cur_count = %d", (int)x.size(), cur_bad);
    for (ll y : x) {
      eprintf("%lld ", y);
    }
    eprintf("\n");
  }

  /*int bad = 0;
  for (int i = 1; i < 1e6; i++) {
    std::unordered_set<int> s;
    bool found = false;
    for (auto a : x) {
      if (!s.insert(a % i).second) {
        found = true;
        break;
      }
    }
    if (!found) {
      bad++;
//      eprintf("%d is bad\n", i);
    }
    if (i % 10000 == 0) {
      eprintf("i = %d, bad = %d\n", i, bad);
    }
  }*/


  return 0;
}
