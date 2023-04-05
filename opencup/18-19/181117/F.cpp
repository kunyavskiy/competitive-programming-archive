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
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    int n = s.size();
    string ansa, ansb;
    string anss;
    for (int i = 1; i <= n; i++) {
      if (n % i == 0) {
        string b = "";
        for (int j = 0; j < n; j += i) {
          b += s[j];
        }
        string a = "";
        for (int j = 0; j < i; j++) {
          a += (s[j] - s[0] + 26) % 26 + 'a';
        }
        bool fail = false;
        for (int j = 0; j < (int) b.size() && !fail; j++) {
          for (int k = 0; k < (int) a.size(); k++) {
            if ((a[k] - 'a' + b[j] - 'a') % 26 != s[j * a.size() + k] - 'a') {
              fail = true;
              break;
            }
          }
        }
        if (!fail) {
          string ab = a + b;
          if (ansa.empty() || anss > ab || (anss == ab && ansa.size() > a.size())) {
            ansa = a;
            ansb = b;
            anss = a + b;
          }
        }
      }
    }
    printf("%s %s\n", ansa.c_str(), ansb.c_str());
  }

  return 0;
}
