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
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  while (t-->0) {
    double a, psi;
    scanf("%lf %lf", &a, &psi);
    int h, m, s;
    scanf("%d:%d:%d", &h, &m, &s);
    const int DAY = 60 * 60 * 24;
    double cur_t = (s + 60 * m + 60 * 60 * h) * (2 * M_PI) / DAY;

    double sphi = tan(psi / 180.0 * M_PI) / tan(a / 180.0 * M_PI);
    sphi = min(sphi, 1.0);
    sphi = max(sphi, -1.0);

    double res = asin(sphi);

    if (res < 0) {
      res = M_PI - res;
    }
    
    cur_t += res;
    
    int ans = (int)(cur_t / (2 * M_PI) * DAY);
    ans = (ans % DAY + DAY) % DAY;

    printf("%02d:%02d:%02d\n", ans / 60 / 60, ans / 60 % 60, ans % 60);
  }


  return 0;
}
