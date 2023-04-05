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
#include <iomanip>

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

vector<pair<int, int>> p;
vector<pair<int, int>> q;

ll calc_s_2() {
  vector<pair<int, int>> st;
  for (auto v : q) {
    while (st.size() >= 2) {
      auto a = st[st.size() - 1];
      auto b = st[st.size() - 2];
//      long vp = calc_vp(a, b, pp);
      ll x1 = a.first - b.first;
      ll y1 = a.second - b.second;
      ll x2 = v.first - a.first;
      ll y2 = v.second - a.second;
      ll vp = x1 * y2 - x2 * y1;
      if (vp <= 0) {
        st.pop_back();
      } else {
        break;
      }
    }
    st.push_back(v);
  }
  ll res = 0;
  for (int i = 0; i < st.size(); i++) {
    if (i + 1 >= st.size()) break;
    auto a = st[i];
    auto b = st[i + 1];
    res += a.first * b.second - a.second * b.first;
  }
  return res;
}

ll calc_s() {
  ll res = calc_s_2();
  reverse(q.begin(), q.end());
  res += calc_s_2();
  return res;
}

ll s;
ll best_s;
ll best_ds;

ll calc_ds(int x) {
  q.clear();
  for (auto pp : p) {
    if (pp.first <= x) {
      q.push_back(pp);
    }
  }
  ll s1 = calc_s();
  q.clear();
  for (auto pp : p) {
    if (pp.first > x) {
      q.push_back(pp);
    }
  }
  ll s2 = calc_s();
  ll ss = abs(s1 - s2);
  ll ds = abs(ss - s);
  if (best_s == -1 || ds < best_ds || (ds == best_ds) && (ss < best_s)) {
    best_s = ss;
    best_ds = ds;
  }
  return s1 - s2;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  best_s = -1;
  scanf("%d%lld", &n, &s);
  s *= 2;
  p.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &p[i].first, &p[i].second);
  }
  sort(p.begin(), p.end());

  for (int ttt = 0; ttt < 2; ttt++) {
    int L = -10001;
    int R = 10001;
    while (R > L + 1) {
      int M = (L + R) / 2;
      ll ds = calc_ds(M);
      if (ds > s) {
        R = M;
      } else {
        L = M;
      }
    }
    calc_ds(L);
    calc_ds(R);
    reverse(p.begin(), p.end());
    for (auto &pp : p) {
      pp.first = -pp.first;
    }
  }

  cout.precision(20);
  cout << fixed << best_s * .5 << "\n";

  return 0;
}
