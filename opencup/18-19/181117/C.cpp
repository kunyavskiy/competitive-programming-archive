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

const int MAXN = 100100;

unsigned int value[MAXN / 32 + 10];

unsigned int get32(int shift) {
  if (shift % 32 == 0) {
    return value[shift / 32];
  }
  return (value[shift / 32] >> (shift & 31)) | (value[shift / 32 + 1] << (32 - (shift & 31)));
}

unsigned int get1(int shift) {
  return (value[shift / 32] >> (shift & 31)) & 1;
}

unsigned int set1(int shift) {
  return value[shift / 32] |= 1 << (shift & 31);
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  sort(a.begin(), a.end());
  if (a[1] != a[0]) {
    cout << a[0] << "\n";
  } else {
    a.erase(unique(a.begin(), a.end()), a.end());
    reverse(a.begin(), a.end());
    for (int x : a) {
      set1(x);
      int i;
      for (i = 0; i + 32 <= x; i += 32) {
        for (int j = i + x; j < MAXN; j += x) {
          value[i / 32] |= get32(j);
        }
      }
      for (; i < x; i++) {
        for (int j = i + x; j < MAXN; j += x) {
          if (get1(j)) {
            eprintf("%d %d\n", i, j);
            set1(i);
            break;
          }
        }
      }
    }
    for (int i = a.back() - 1;;i--) {
      if (get1(i)) {
        printf("%d\n", i);
        break;
      }
    }
  }

  return 0;
}
