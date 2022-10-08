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
#include <numeric>

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

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n);
    for (int &x : a) {
      scanf("%d", &x);
    }
    for (int &x : b) {
      scanf("%d", &x);
    }

    ll opsb, opsa;
    opsb = opsa = 0;

    for (int i = 0; i < n; i++) {
      if (a[i] > b[i]) {
        opsb += a[i] - b[i];
      } else {
        if (a[i] % 2 == b[i] % 2) {
          opsa += (b[i] - a[i]) / 2;
        } else {
          opsb++;
          b[i]++;
          opsa += (b[i] - a[i]) / 2;
        }
      }
    }

//    eprintf("%lld %lld\n", opsa, opsb);

    if (opsa < opsb) {
      printf("No\n");
    } else {
      printf("Yes\n");
    }
  }

  return 0;
}
