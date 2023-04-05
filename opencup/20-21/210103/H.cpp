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

struct slicer {
  const int BLOCK = 10000;
  vector<int> cur_slice;
  vector<int> c, x, y, z;
  vector<tuple<int, int, int>> saved;
  int cur_slice_offset = 0;
  explicit slicer(int start) {
    cur_slice.push_back(start);
    saved.emplace_back(start, 0, 0);
  }

  void add_seq(int cc, int xx, int yy, int zz) {
    int cur_size = cur_slice_offset + cur_slice.size();
    c.push_back(cc);
    x.push_back(xx);
    y.push_back(yy);
    z.push_back(zz);
    for (int i = cur_size; i < cur_size + c.back(); i++) {
      int nxt = (cur_slice.back() * 1LL * xx + yy) % zz;
      if (i % BLOCK == 0) {
        saved.emplace_back(nxt, x.size() - 1, i - cur_size + 1);
        cur_slice.clear();
        cur_slice_offset = i;
      }
      cur_slice.push_back(nxt);
    }
  }

  void reslice(int slice_id) {
    cur_slice_offset = slice_id * BLOCK;
    cur_slice.clear();
    auto [cur, gen_id, gen_pos] = saved[slice_id];
    cur_slice.push_back(cur);
    for (int i = 0; i < BLOCK; i++) {
      if (gen_pos == c[gen_id]) {
        gen_id++;
        gen_pos = 0;
        if (gen_id >= (int)c.size()) break;
      }
      cur = (cur * 1LL * x[gen_id] + y[gen_id]) % z[gen_id];
      cur_slice.push_back(cur);
      gen_pos++;
    }
  }

  int operator[](int pos) {
    if (!(cur_slice_offset <= pos && pos < cur_slice_offset + (int)cur_slice.size())) {
      reslice(pos / BLOCK);
    }
    return cur_slice[pos - cur_slice_offset];
  }
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    int cur, k;
    scanf("%d%d", &cur, &k);
    slicer a(cur);
    for (int i = 0; i < k; i++) {
      int c, x, y, z;
      scanf("%d%d%d%d", &c, &x, &y, &z);
      a.add_seq(c, x, y, z);
    }
#ifdef LOCAL
    for (int i = 0; i < n; i++) {
      eprintf("%d ", a[i]);
    }
    eprintf("\n");
#endif

    while (m && n > m) {
      if (a[n - 1] <= m - 1) {
        m--;
      }
      n--;
    }
    if (m == 0) {
      printf("0\n");
      continue;
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] > i) {
        ans++;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
