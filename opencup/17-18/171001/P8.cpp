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

#define MAX 1000005L

int main() {

  int n;
  cin >> n;
  vector<pair<int, int>> res(n);
  for (int i = 0; i < n; i++) {
    long l = 0;
    long r = 2 * MAX;
    while (r > l + 1) {
      long m = (l + r) >> 1;
      cout << "? " << m - MAX << " " << MAX << endl;
      int k;
      cin >> k;
      if (k >= i + 1) {
        r = m;
      } else {
        l = m;
      }
    }
    long x = r - MAX;
    l = 0;
    r = 2 * MAX;
    while (r > l + 1) {
      long m = (l + r) >> 1;
      cout << "? " << x << " " << m - MAX << endl;
      int k;
      cin >> k;
      for (int j = 0; j < i; j++) {
        if (res[j].first <= x && res[j].second <= m - MAX) k--;
      }
      if (k >= 1) {
        r = m;
      } else {
        l = m;
      }
    }
    long y = r - MAX;
    res[i] = {x, y};
  }
  cout << "!";
  for (int i = 0; i < n; i++) {
    cout << " " << res[i].first << " " << res[i].second;
  }
  cout << endl;

  return 0;
}
