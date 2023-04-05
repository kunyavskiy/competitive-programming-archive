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

class SegmentTree {

  vector<ll> tree;
  int lst;

  ll get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return 0;
    }
    if (L <= l && r <= R) {
      return tree[v];
    }
    return max(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
  }

  void update(int v, int l, int r, int x, ll u) {
    if (r == l + 1) {
      tree[v] = max(tree[v], u);
    } else {
      int m = (l + r) / 2;
      if (x < m) {
        update(2 * v, l, (l + r) / 2, x, u);
      } else {
        update(2 * v + 1, (l + r) / 2, r, x, u);
      }
      tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }
  }

public:

  void init(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<ll>((size_t) (2 * lst), 0);
  }

  ll get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  void update(int x, ll u) {
    return update(1, 0, lst, x, u);
  }
};


int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> c(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &c[i]);
  }
  vector<ll> d(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &d[i]);
  }

  SegmentTree st;
  st.init(n + 1);

  vector<int> l(2 * n);
  vector<int> r(2 * n);

  for (int i = 0; i < n; i++) {
    l[2 * i] = i - c[i] + 1;
    r[2 * i] = i + 1;
    l[2 * i + 1] = i;
    r[2 * i + 1] = i + c[i];
  }

//  for (int i = 0; i < 2 * n; i++) {
//    cout << l[i] << " " << r[i] << "\n";
//  }

  vector<pair<pair<int, int>, int>> p(2 * n);
  for (int i = 0; i < 2 * n; i++) {
    p[i] = {{l[i], -r[i]}, i};
  }
  sort(p.begin(), p.end());
  int j = 0;

  vector<ll> dd(2 * n);
  vector<ll> res(n);

  while (j < n && p[j].first.first < 0) j++;

  for (int i = 0; i < n; i++) {
    int jj = j;
    while (j < (int)p.size() && p[j].first.first == i) {
      int x = p[j].second;
      j++;
      dd[x] = d[x / 2] + st.get(r[x], n + 1);
//      cout << x << " " << l[x] << " " << r[x] << " " << dd[x] << "\n";
      if (x % 2 == 0 && r[x] <= n) {
        st.update(r[x] - 1, dd[x]);
      }
    }

    res[i] = st.get(i + 1, n + 1);

    j = jj;
    while (j < (int)p.size() && p[j].first.first == i) {
      int x = p[j].second;
      j++;
      if (x % 2 == 1 && r[x] <= n) {
        st.update(r[x], dd[x]);
      }
    }
  }

  for (int i = 0; i < n; i++) {
    if (c[i] == 1) {
      res[i] += d[i];
    }
    cout << res[i] << " ";
  }

  return 0;
}
