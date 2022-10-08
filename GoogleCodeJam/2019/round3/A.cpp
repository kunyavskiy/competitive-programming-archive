#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
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

const ll LEN = 1e10;

void solve() {
  vector<pair<ll, ll>> segs;
  segs.emplace_back(0, 1e12);
  auto do_move = [&](ll pos) {
    for (int i = 0; ; i++) {
      assert(i < (int)segs.size());
      if (segs[i].first <= pos && pos + LEN <= segs[i].second) {
        ll l1 = segs[i].first;
        ll r1 = pos;
        ll l2 = pos + LEN;
        ll r2 = segs[i].second;
        segs.erase(segs.begin() + i);
        if (r1 - l1 >= LEN) {
          segs.emplace_back(l1, r1);
        }
        if (r2 - l2 >= LEN) {
          segs.emplace_back(l2, r2);
        }
        break;
      }
    }
    /*
    sort(segs.begin(), segs.end());
    for (auto x : segs) {
      eprintf("[%lld..%lld) ", x.first, x.second);
    }
    eprintf("\n");
     */
  };
  while (true) {
    {
      ll p;
      scanf("%lld", &p);
      if (p == -2 || p == -3) {
        eprintf("%s\n", (p == -2) ? "WIN" : "LOOSE");
        return;
      }
      if (p == -1) exit(0);
      do_move(p - 1);
    }
    ll move = -1;
    for (auto x : segs) {
      if (x.second - x.first >= 3 * LEN) {
        move = x.first + 2 * LEN;
      }
    }
    if (move == -1) {
      for (auto x : segs) {
        if (x.second - x.first > 2 * LEN) {
          move = x.first + LEN - 1;
        }
      }
    }
    if (move == -1) {
      for (auto x : segs) {
        if (x.second - x.first < 2 * LEN) {
          move = x.first;
        }
      }
    }
    if (move == -1) {
      if (segs.size() != 2) {
        move = segs[0].first + 1;
      } else {
        move = segs[0].first;
      }
    }

    do_move(move);
    printf("%lld\n", move + 1);
    fflush(stdout);
  }
}


int main() {

  int t, w;
  scanf("%d%d", &t, &w);

  for (int i = 0; i < t; i++) {
    solve();
  }


  return 0;
}
