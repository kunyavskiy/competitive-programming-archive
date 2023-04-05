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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

class segm_tree {
public:
  segm_tree(int n) {
    off = 1;
    while (off < n) off <<= 1;
    trv = vector<ll>(2 * off);
    tradd = vector<ll>(2 * off);
  }

  void add(int l, int r, ll v) {
    rl = l;
    rr = r;
    rv = v;
    add_(1, 0, off - 1);
  }

  ll getMax() const {
    return trv[1];
  }

private:
  int off;
  vector<ll> trv, tradd;

  void add(int v, ll k) {
    trv[v] += k;
    tradd[v] += k;
  }

  void push(int v) {
    if (v < off) {
      add(2 * v, tradd[v]);
      add(2 * v + 1, tradd[v]);
    }
    tradd[v] = 0;
  }

  void update(int v) {
    assert(!tradd[v]);
    assert(v < off);
    trv[v] = max(trv[2 * v], trv[2 * v + 1]);
  }

  int rl, rr;
  ll rv;

  void add_(int v, int tl, int tr) {
    if (tr < rl || rr < tl) return;
    if (rl <= tl && tr <= rr) {
      add(v, rv);
      return;
    }
    push(v);
    int tm = (tl + tr) / 2;
    add_(2 * v, tl, tm);
    add_(2 * v + 1, tm + 1, tr);
    update(v);
  }
};

struct Ev {
  ll x, y1, y2, s;
};

int solve_compressed(vector<Ev> evs, int h) {
  sort(evs.begin(), evs.end(), [](const Ev &a, const Ev &b) {
    if (a.x != b.x) return a.x < b.x;
    return a.s < b.s;
  });
  int ans = 0;
  segm_tree tr(h);
  for (const auto &e : evs) {
    tr.add(e.y1, e.y2, e.s);
    ll cans = tr.getMax();
    assert(cans <= int(2e9));
    ans = max(ans, (int)cans);
  }
  return ans;
}

int solve(vector<Ev> evs) {
  vector<ll> ys;
  for (const auto &e : evs) {
    ys.push_back(e.y1);
    ys.push_back(e.y2 + 1);
  }
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  for (auto &e : evs) {
    e.y1 = lower_bound(ys.begin(), ys.end(), e.y1) - ys.begin();
    e.y2 = upper_bound(ys.begin(), ys.end(), e.y2) - ys.begin() - 1;
  }
  return solve_compressed(evs, (int)ys.size());
}

struct Rect {
  ll x1, y1, x2, y2, s;
};

int solve(const vector<Rect> &rs) {
  vector<Ev> evs;
  for (const auto &re : rs) {
    evs.push_back({re.x1, re.y1, re.y2, +re.s});
    evs.push_back({re.x2 + 1, re.y1, re.y2, -re.s});
  }
  return solve(evs);
}

void printBaseRs(int r, const vector<Rect> &baseRs) {
  map<pair<int, int>, int> tmp;
  for (auto &re : baseRs) {
    for (int y = re.y1; y <= re.y2; y++)
      for (int x = re.x1; x <= re.x2; x++) {
        assert(-2 * r <= x && x <= 0);
        assert(-2 * r <= y && y <= 0);
        tmp[make_pair(x, y)]++;
      }
  }
  for (int y = 0; y >= -2 * r; y--) {
    for (int x = -2 * r; x <= 0; x++) {
      eprintf(" %d", tmp[make_pair(x, y)]);
    }
    eprintf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, l, r;
  while (scanf("%d%d%d", &n, &l, &r) == 3) {
    vector<Rect> baseRs = {
        { -r - r, -r + l, 0, 0, 0 },
        { -r - r, -r - r, 0, -r - l, 0 },
        { -r - r, -r - l + 1, -r - l, -r + l - 1, 0 },
        { -r + l, -r - l + 1, 0, -r + l - 1, 0 },
    };

    #ifdef LOCAL
    //printBaseRs(r, baseRs);
    #endif

    vector<Rect> rs;
    for (int i = 0; i < n; i++) {
      int x, y, s;
      scanf("%d%d%d", &x, &y, &s);
      for (const auto &re : baseRs) {
        Rect nre = re;
        nre.x1 += x;
        nre.y1 += y;
        nre.x2 += x;
        nre.y2 += y;
        nre.s = s;
        rs.push_back(nre);
      }
    }
    printf("%d\n", solve(rs));
  }

  return 0;
}
