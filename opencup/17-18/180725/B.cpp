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

char str[100002];

void solve_test() {
  int n;
  scanf("%d", &n);
  vector<pair<int, int>> pos(n);
  vector<pair<int, int>> neg(n);
  int s = 0;
  for (int i = 0; i < n; i++) {
    scanf("%s", str);
    int bal = 0;
    int a = 0;
    int b = 0;
    for (int j = 0; str[j]; j++) {
      if (str[j] == '(') {
        s++;
        bal++;
        b++;
      } else {
        if (bal > 0) {
          bal--;
          b--;
        } else {
          a++;
        }
      }
    }
    //cout << a << " " << b << "\n";

    if (b >= a) {
      pos.push_back({a, b});
    } else {
      neg.push_back({-b, a});
    }
  }

  sort(pos.begin(), pos.end());
  sort(neg.begin(), neg.end());
  int x = 0;
  for (auto p : pos) {
    x = max(x - p.first, 0) + p.second;
  }
  for (auto p : neg) {
    x = max(x - p.second, 0) - p.first;
  }
  cout << (s - x) * 2 << "\n";
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    solve_test();
  }

  return 0;
}
