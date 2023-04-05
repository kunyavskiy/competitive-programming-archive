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
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int students, chats, s;
  while (scanf("%d%d%d", &chats, &students, &s) == 3) {
    vector<int> ans(students);
    vector<int> curid(chats);
    vector<set<int>> mems(chats);
    for (int i = 0; i < s; i++) {
      int ty, x, y;
      scanf("%d%d%d", &ty, &x, &y);
      --x, --y;
      if (ty == 1) {
        ans[x] -= curid[y];
        mems[y].insert(x);
      } else if (ty == 2) {
        ans[x] += curid[y];
        mems[y].erase(x);
      } else {
        ans[x]--;
        curid[y]++;
      }
    }
    for (int i = 0; i < chats; i++) {
      for (int j : mems[i]) {
        ans[j] += curid[i];
      }
    }
    for (int i = 0; i < students; i++) {
      printf("%d\n", ans[i]);
    }
  }

  return 0;
}
