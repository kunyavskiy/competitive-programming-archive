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
typedef pair<int, int> pii;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const char dirs[] = "UDLR";
int get_dir(char ch) {
//  eprintf("%c", ch);
  int i = 0;
  while (i < 4 && dirs[i] != ch) {
    i++;
  }
  assert(i < 4);
  return i;
}

bool check(int n, int m, int x, int y) {
  return (0 <= x && x < n) && (0 <= y && y < m);
}

struct my_bitset {
  using word = unsigned long long;
  const int K = sizeof(word) * 8;

  explicit my_bitset(int n) {
    this->n = (n + K - 1)  / K;
    this->v.resize(this->n);
  }

  bool operator[] (int index) const {
    return (v[index / K] >> (index % K)) & 1u;
  }

  void set(int index) {
    v[index / K] |= (word(1u) << (index % K));
  }

  my_bitset &operator |= (const my_bitset &other) {
    assert(n == other.n);
    for (int i = 0; i < n; ++i) {
      v[i] |= other.v[i];
    }
    return *this;
  }

  int n;
  vector<word> v;
};

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    static char s[1010];
    scanf("%s", s);
    eprintf("%s\n", s);
    for (int j = 0; j < m; ++j) {
      a[i][j] = get_dir(s[j]);
    }
  }

  vector<vector<bool>> used(n, vector<bool>(m, false));

  vector<pii> st;
  std::function<void(int, int)> dfs = [&](int x, int y) {
    if (used[x][y]) { return; }
    used[x][y] = true;
    for (int i = 0; i < 4; ++i) {
      if (i != a[x][y]) {
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        if (check(n, m, x1, y1)) {
          dfs(x1, y1);
        }
      }
    }
    st.emplace_back(x, y);
  };

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (!used[x][y]) {
        dfs(x, y);
      }
    }
  }

  vector<vector<int>> comp(n, vector<int>(m, -1));
  std::function<void(int, int, int)> dfs2 = [&](int x, int y, int color) {
    if (comp[x][y] != -1) { return; }
    comp[x][y] = color;
    for (int i = 0; i < 4; ++i) {
      int x1 = x + dx[i];
      int y1 = y + dy[i];
      if (check(n, m, x1, y1) && (i^1) != a[x1][y1]) {
        dfs2(x1, y1, color);
      }
    }
  };

  int cnt = 0;
  reverse(st.begin(), st.end());
  for (auto p : st) {
    int x = p.first;
    int y = p.second;
    if (comp[x][y] == -1) {
      dfs2(x, y, cnt++);
    }
  }
//  assert(cnt <= 2000);

//  for (int x = 0; x < n; ++x) {
//    for (int y = 0; y < n; ++y) {
//      eprintf("%d ", comp[x][y]);
//    }
//    eprintf("\n");
//  }

  vector<int> size(cnt);
  vector<vector<int>> ed(cnt);
  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      size[comp[x][y]] += 1;
      for (int i = 0; i < 4; ++i) {
        if (i == a[x][y]) { continue; }
        int x1 = x + dx[i];
        int y1 = y + dy[i];
        if (check(n, m, x1, y1)) {
          ed[comp[x][y]].push_back(comp[x1][y1]);
        }
      }
    }
  }
  for (auto & ee : ed) {
    sort(ee.begin(), ee.end());
    ee.erase(unique(ee.begin(), ee.end()), ee.end());
  }

  vector<vector<int>> sum_sizes(cnt / 8 + 16, vector<int>(256, 0));
  for (int i = 0; i * 8 < cnt; ++i) {
    for (int mask = 1; mask < 256; ++mask) {
      int last = __builtin_ctz(mask);
      sum_sizes[i][mask] = sum_sizes[i][mask ^ (1 << last)];
      int index = i * 8 + last;
      if (index < cnt) {
        sum_sizes[i][mask] += size[index];
      }
    }
  }

  vector<my_bitset> bb(cnt, my_bitset(cnt));
  for (int u = cnt - 1; u >= 0; --u) {
    bb[u].set(u);
    for (int v : ed[u]) {
      if (v == u) { continue; }
      bb[u] |= bb[v];
    }
  }
//  for (int i = 0; i < cnt; ++i) {
//    eprintf("%d: ", i);
//    for (int v = 0; v < cnt; ++v) {
//      if (bb[i][v]) {
//        eprintf(" %d", v);
//      }
//    }
//    eprintf("\n");
//  }

  vector<my_bitset> cc(cnt, my_bitset(cnt));
  for (int u = 0; u < cnt; ++u) {
    for (int v = 0; v < cnt; ++v) {
      if (bb[u][v]) {
        cc[v].set(u);
      }
    }
  }

  for (int i = 0; i < q; ++i) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
    --x1, --y1, --x2, --y2;
    int u = comp[x1][y1];
    int v = comp[x2][y2];
    int ans = 0;
    for (int ii = 0, kk = 0; ii < bb[u].n; ++ii) {
      auto mask = bb[u].v[ii] & cc[v].v[ii];
      for (int j = 0; j < bb[u].K; j += 8, ++kk) {
        ans += sum_sizes[kk][mask & 255];
        mask >>= 8;
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
