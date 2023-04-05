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
  freopen("10.in", "r", stdin);
  freopen("10.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    auto rotate = [&](vector<string> &a) {
      vector<string> na(n, string(n, ' '));
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          na[j][n - i - 1] = a[i][j];
        }
      }
      a = na;
    };
    auto reflect = [&](vector<string> &a) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - j - 1; j++) {
          swap(a[i][j], a[i][n-j-1]);
        }
      }
    };
    auto read = [&] {
      static char buf[5000];
      vector<string> res(n);
      for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        res[i] = buf;
      }
      vector<string> a = res;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
          rotate(a);
          res = min(res, a);
        }
        reflect(a);
      }
      return res;
    };
    vector<string> a = read();
    vector<string> b = read();
    if (a != b) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  }

  return 0;
}
