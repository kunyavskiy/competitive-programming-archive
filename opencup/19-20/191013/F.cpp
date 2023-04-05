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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

struct linear {
  int a, b;

  int apply(int x) {
    x = mul(x, a);
    add(x, b);
    return x;
  }

  linear inverse() {
    // ax + b = y -> ax = y - b -> x = a^-1*y - b * a^-1
    linear res;
    res.a = minv(a);
    res.b = mul(MOD - b, res.a);
#ifdef LOCAL
    assert(combine(res).a == 1);
    assert(combine(res).b == 0);
#endif
    return res;
  }

  linear combine(linear other) {
    linear res;
    res.a = mul(a, other.a);
    res.b = b;
    add(res.b, mul(a, other.b));
    return res;
  }
};

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int q;
  while (scanf("%d", &q) == 1) {
    vector<vector<ll>> psum;
    vector<int> first;
    first.push_back(0);
    psum.push_back({0});
    vector<linear> f;
    linear gf{1, 0};
    f.push_back(gf);
    int curg = 0;
    int cur_first = 0;
    for (int _ = 0; _ < q; _++) {
      int ty;
      scanf("%d", &ty);
      if (ty == 1) {
        int k;
        scanf("%d",&k);
        curg++;
        if (k == 0) {
          psum.push_back({0});
          gf = linear{2, 0}.combine(gf);
          f.push_back(gf.inverse().combine(linear{2,1}));
#ifdef LOCAL
          assert(gf.combine(f.back()).a == 2);
          assert(gf.combine(f.back()).b == 1);
#endif
          first.push_back(cur_first);
        } else {
          psum.back().push_back(psum.back().back() + k);
          gf = linear{1, k}.combine(gf);
          f.push_back(gf.inverse());
          cur_first = curg;
        }
      } else if (ty == 2) {
        int g, x;
        scanf("%d%d", &g, &x);
        --x;
        printf("%d\n", gf.combine(f[g]).apply(x));
      } else if (ty == 3){
        int x;
        scanf("%d", &x);
        int ans = curg;
        for (int i = (int)psum.size() - 1;; i--) {
          if (x >= psum[i].back()) {
            x -= psum[i].back();
            ans -= (int)psum[i].size() - 1;
            if (x % 2 == 1 || i == 0) {
              printf("%d\n", ans);
              break;
            }
            ans--;
            x /= 2;
            if (x == 0) {
              printf("%d\n", first[i]);
              break;
            }
          } else {
            int id = lower_bound(psum[i].begin(), psum[i].end(), psum[i].back() - x) - psum[i].begin();
            ans -= (int)psum[i].size() - id - 1;
            printf("%d\n", ans);
            break;
          }
        }
      }
    }
  }


  return 0;
}
