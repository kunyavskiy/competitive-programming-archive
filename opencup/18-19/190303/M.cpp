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


int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}


void uniq(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

int solve(vector<int> v) {
  if (v.size() == 1) {
    return 1;
  }
  int m = v.size() / 2;
  vector<int> lf(v.begin(), v.begin() + m);
  vector<int> rg(v.begin() + m, v.end());
  if (lf == rg) {
    return mul(solve(lf), 2);
  }
  int ans = solve(lf);
  ans = mul(ans, solve(rg));
  uniq(lf);
  uniq(rg);
  vector<int> t;
  set_intersection(lf.begin(), lf.end(), rg.begin(), rg.end(), back_inserter(t));
  if (!t.empty()) {
    ans = 0;
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int m, n;
  while (scanf("%d%d", &m, &n) == 2) {
    vector<int> v(1 << m);
    for (int &x : v) {
      scanf("%d", &x);
    }
    {
      vector<int> vv = v;
      uniq(vv);
      if ((int)vv.size() != n) {
        printf("0\n");
        continue;
      }
    }

    printf("%d\n", solve(v));
  }

  return 0;
}
