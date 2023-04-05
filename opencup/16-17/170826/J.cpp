#include <iostream>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

int main() {
  int res = 0;
  for (int qqq = 0; qqq < 2; qqq++) {
    int n;
    scanf("%d", &n);
    vector<int> p(n + 1, 2000000000);
    int s = 0;
    for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      int l = -1;
      int r = n + 1;
      while (r > l + 1) {
        int m = (l + r) / 2;
        if (p[m] > x) {
          r = m;
        } else {
          l = m;
        }
      }
      p[r] = x;
      if (r > s) {
        s = r;
      }
    }
    res += s + 1;
  }
  printf("%d\n", res);

  return 0;
}
