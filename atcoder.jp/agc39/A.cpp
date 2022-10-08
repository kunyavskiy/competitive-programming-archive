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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  char _s[200]; int k;
  while (scanf("%s%d", _s, &k) == 2) {
    string s = _s;
    int n = s.size();
    long long cnt_odd = 0;
    vector<int> cnts;
    for (int i = 0; i < n; ) {
      int j = i;
      while (j < n && s[i] == s[j]) j++;
      cnts.push_back((j - i) % 2);
      cnt_odd += cnts.back();
      i = j;
    }
    cnt_odd *= k;
    if (s[0] == s[n - 1]) {
      if (cnts.size() == 1) {
        cnt_odd = (n * 1LL * k) % 2;
      } else {
        cnt_odd -= cnts[0] * (k - 1);
        cnt_odd -= cnts.back() * (k - 1);
        cnt_odd += ((cnts[0] + cnts.back()) % 2) * (k - 1);
      }
    }
    printf("%lld\n", (n * 1LL * k - cnt_odd) / 2);
  }

  return 0;
}
