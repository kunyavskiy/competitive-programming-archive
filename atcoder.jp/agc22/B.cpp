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

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  if (n == 3) {
    printf("2 5 63\n");
    return 0;
  }

  vector<int> val;
  val.push_back(2);
  val.push_back(5);
  val.push_back(63);
  for (int i = 70; i <= 30000; i++) {
    if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0) {
      val.push_back(i);
    }
  }

  vector<int> any(30, -1);
  for (int i : val) {
    if (i > 70 && any[i % 30] == -1) {
      eprintf("%d %d\n", i % 30, i);
      any[i % 30] = i;
    }
  }

  while (true) {
    random_shuffle(val.begin() + 3,  val.end());
    int res = 0;
    vector<int> ans;
    for (int i : val) {
      if (find(any.begin(), any.end(), i) == any.end()) {
        ans.push_back(i);
        res = (res + i) % 30;
      }
      if ((int)ans.size() == n - 1) break;
    }
    assert((int)ans.size() == n - 1);
    int rem = (30 - res) % 30;
    if (any[rem] != -1) {
      ans.push_back(any[rem]);
      for (int i : ans) {
        printf("%d ", i);
      }
      printf("\n");
      break;
    }
  }

  return 0;
}
