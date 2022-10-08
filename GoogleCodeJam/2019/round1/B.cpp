#include <iostream>
#include <fstream>
#include <vector>

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
typedef unsigned long long ull;

void PreCalc() {
}



bool solve() {
  printf("%d\n%d\n", 50, 200);
  fflush(stdout);
  ull x, y;
  scanf("%llu", &x);
  vector<ull> result;
  result.push_back((x >> 50u) & 127u);
  result.push_back((x >> 25u) & 127u);
  scanf("%llu", &y);
  result.push_back(-1);
  result.push_back((y >> 50u) & 127u);
  result.push_back((y >> 40u) & 127u);
  result.push_back((y >> 33u) & 127u);

  for (int i = 1; i <= 6; i++) {
    if (i != 3) {
      x -= result[i - 1] << (50u / i);
    }
  }

  result[2] = x >> (50u / 3);

  for (int i = 0; i < 6; i++) {
    printf("%llu%c", result[i], " \n"[i == 5]);
  }
  fflush(stdout);
  int res;
  scanf("%d", &res);
  return res == 1;
}


int main() {

  int t;
  scanf("%d%*d", &t);

  while (t-->0) {
    if (!solve()) break;
  }
  return 0;
}
