#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "E"

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
//  assert(freopen(TASKNAME".in", "r", stdin));
//  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  vector<int> a, b, c;
  int x;
  scanf("%d", &x);
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < x; j++) {
      for (int k = 0; k < x; k++) {
        if ((i * i + j * j + k * k) % x == 1) {
          a.push_back(i);
          b.push_back(j);
          c.push_back(k);
        }
      }
    }
  }

  int it = 0;

  for (int aq = 0; ; aq++) {
    for (int bq = 0; bq <= aq; bq++) {
      for (int cq = 0; cq <= bq; cq++) {
        for (int i = 0; i < (int)a.size(); i++) {
          int A = a[i] + aq * x;
          int B = b[i] + bq * x;
          int C = c[i] + cq * x;
          if (A * A + B * B + C * C == x * (A * B + A * C + B * C) + 1) {
            printf("%d: %d %d %d\n", it++, A, B, C);
          }
        }
      }
    }
  }

  return 0;
}
