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

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n);
    for (int& x : a) scanf("%d", &x);
    for (int& x : b) scanf("%d", &x);

    set<pair<int, int>> s;

    ll res = 0;
    vector<int> answer;

    vector<int> stack;

    for (int i = 0; i < n; i++) {
      res += abs(a[i] - b[i]);
      if (b[i] < a[i]) {
        assert(stack.empty() || (a[i] - b[i] < b[i] - a[stack.back()]));
        answer.push_back(i);
      } else {
        stack.push_back(i);
      }
      while (!stack.empty()) {
        int t = stack.back();
        if (i == n - 1 || (b[t] - a[t] <= abs(a[i + 1] - b[t]))) {
          answer.push_back(t);
          stack.pop_back();
        } else {
          break;
        }
      }
    }

    printf("%lld\n", res);
    for (int x : answer) {
      printf("%d ", x + 1);
    }
    printf("\n");



  }

  return 0;
}
