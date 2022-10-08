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

ll T, L;

pair<int, int> get_dir0(vector<int> x, vector<int> w) {
  int n = (int) x.size();
  vector<int> same;
  vector<int> other;
  for (int i = 0; i < n; i++) {
    if (w[i] == 1) {
      same.push_back((int) ((x[i] - x[0] + L) % L));
    } else {
      other.push_back((int) ((x[0] - x[i] + L) % L));
    }
  }
  if (w[0] == 2) {
    same.swap(other);
  }

  sort(same.begin(), same.end());
  sort(other.begin(), other.end());

  int last = (int) L;
  for (int i = (int)same.size() - 1; i >= 0; i--) {
    int tmp = same[i];
    same[i] = last - same[i];
    last = tmp;
  }

  last = (int) L;
  for (int i = (int)other.size() - 1; i >= 0; i--) {
    int tmp = other[i];
    other[i] = last - other[i];
    last = tmp;
  }

  ll T = ::T;

  for (int i = 0;; i++) {
    if (i % 2 == 0) {
      T -= other[i % other.size()];
      if (T <= 0) {
        return {}
      }
    }
  }
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d%lld%lld", &n, &L, &T);
  vector<int> x(n);
  vector<int> w(n);

  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &w[i]);
    x[i] *= 2;
  }
  L *= 2;
  T *= 2;

  vector<pair<int, int>> nx(n);

  for (int i = 0; i < n; i++) {
    if (w[i] == 1) {
      nx[i] = {(int)(x[i] + T * 1LL ) % L, w[i]};
    } else {
      nx[i] = {(int)((x[i] - T * 1LL) % L + L) % L, w[i]};
    }
  }

  sort(nx.begin(), nx.end());

  pair<int, int> r = get_dir0(x, w);

  rotate(nx.begin(), lower_bound(nx.begin(), nx.end(), r), nx.end());

  for (int i = 0; i < n; i++) {
    printf("%d\n", nx[i].first / 2);
  }
  return 0;
}
