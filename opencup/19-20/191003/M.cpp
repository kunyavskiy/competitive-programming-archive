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
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  int n;
  cin >> n;
  int b = 1;
  vector<pair<vector<int>, vector<int>>> res;
  while (b < n) {
    for (int i = 0; i < 4; i++) {
      vector<int> xx;
      vector<int> yy;
      for (int x = i; x * b < n; x += 4) {
        for (int j = 0; j < b; j++) {
          if (x * b + j < n) xx.push_back(x * b + j);
        }
      }
      for (int y = (2 + i) % 4; y * b < n; y += 4) {
        for (int j = 0; j < b; j++) {
          if (y * b + j < n) yy.push_back(y * b + j);
        }
      }
      for (int y = (3 + i) % 4; y * b < n; y += 4) {
        for (int j = 0; j < b; j++) {
          if (y * b + j < n) yy.push_back(y * b + j);
        }
      }
      if (xx.size() > 0 && yy.size() > 0) {
        res.push_back({yy, xx});
      }
    }
    b *= 2;
  }
  cout << res.size() << "\n";
  for (auto p : res) {
    cout << p.first.size();
    for (int x : p.first) {
      cout << " " << x + 1;
    }
    cout << "\n";
    cout << p.second.size();
    for (int x : p.second) {
      cout << " " << x + 1;
    }
    cout << "\n";
  }

  return 0;
}
