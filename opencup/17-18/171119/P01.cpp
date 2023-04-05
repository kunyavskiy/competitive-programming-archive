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

bool inside(int a, int b, int c, int d) {
  return a >= c && b <= d;
}

bool intersect(int a, int b, int c, int d) {
  return max(a, c) <= min(b, d);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int ax1, ay1, ax2, ay2;
    cin >> ax1 >> ay1 >> ax2 >> ay2;
    int bx1, by1, bx2, by2;
    cin >> bx1 >> by1 >> bx2 >> by2;
    if (inside(ax1, ax2, bx1, bx2) && inside(ay1, ay2, by1, by2)) {
      cout << "A in B\n";
      continue;
    }
    if (inside(bx1, bx2, ax1, ax2) && inside(by1, by2, ay1, ay2)) {
      cout << "B in A\n";
      continue;
    }
    if (intersect(bx1, bx2, ax1, ax2) && intersect(by1, by2, ay1, ay2)) {
      cout << "Intersect\n";
      continue;
    }
    cout << "Separate\n";
  }


  return 0;
}
