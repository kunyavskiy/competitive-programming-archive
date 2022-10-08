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

vector<int> ans;

void gen(int &cur, int mask) {
  if (mask == 0) return;
  int bit = mask & ~(mask - 1);
  gen(cur, mask ^ bit);
  ans.push_back(cur ^= bit);
  gen(cur, mask ^ bit);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, a, b;
  while (scanf("%d%d%d", &n, &a, &b) == 3) {
    ans.clear();
    {
      int x = a ^b;
      if (__builtin_popcount(x) % 2 != 1) {
        printf("NO\n");
        continue;
      }
    }
    int cur = a;
    int mask_all = (1 << n) - 1;
    ans.push_back(a);

    while (mask_all) {
      int x = cur ^ b;
      assert((x & ~mask_all) == 0);
      assert(__builtin_popcount(x) % 2 == 1);
      int bit = x & ~(x - 1);

      gen(cur, mask_all ^ bit);
      ans.push_back(cur ^= bit);
      mask_all ^= bit;
    }
    assert(cur == b);

    printf("YES\n");
    for (int x : ans) {
      printf("%d ", x);
    }
    printf("\n");
#ifdef LOCAL
    assert(ans[0] == a);
    assert(ans.back() == b);
    for (int i = 0; i < (1 << n) - 1; i++) {
      int x = ans[i] ^ ans[i+1];
      assert((x & (x - 1)) == 0);
    }
    assert((int)ans.size() == (1 << n));
    sort(ans.begin(), ans.end());
    assert(unique(ans.begin(), ans.end()) == ans.end());
#endif
  }

  return 0;
}
