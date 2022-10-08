#include <iostream>
#include <fstream>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

void solve() {
  for (int i = 1; i <= 100; i++) {
    int day = 0;
    scanf("%d", &day);
    if (day == -1) exit(0);
    if (i >= 81) {
      printf("%d 100\n", i - 80);
      fflush(stdout);
    } else {
      printf("1 0\n");
      fflush(stdout);
      int n;
      scanf("%d", &n);
      for (int j = 0; j < n; j++) scanf("%*d");
    }
  }
}


int main() {

  PreCalc();
  TIMESTAMP(PreCalc);

  int t = 0;
  scanf("%d", &t);


  while (t --> 0) {
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
