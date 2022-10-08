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

using namespace std;

typedef long long ll;
typedef long double ld;

double pw10[30];

void PreCalc() {
  pw10[0] = 1;
  for (size_t i = 1; i < size(pw10); i++) {
    pw10[i] = pw10[i - 1] * 10;
  }
}

int n, b;
constexpr double S = 19131995794056374.42;
double total_sum;

void solve() {
  vector<int> curw(n, 0);
  int done = 0;
  auto put = [&](int x) {
    curw[x]++;
    assert(curw[x] <= b);
    printf("%d\n", x + 1);
    fflush(stdout);
    ++done;
  };
  double my_sum = 0;
  while (done < n * b) {
    int d;
    scanf("%d", &d);
    int best;
    auto it = curw.begin();
    if (d == 9) {
      it = find(curw.begin(), curw.end(), b - 1);
      if (it == curw.end()) {
        it = find(curw.begin(), curw.end(), b - 2);
      }
    } else if (d >= 7) {
      it = find(curw.begin(), curw.end(), b - 2);
      if (it == curw.end()) {
        it = find_if(curw.begin(), curw.end(), [](int x) { return x < b - 2;});
      }
    } else {
      it = find_if(curw.begin(), curw.end(), [](int x) { return x < b - 2;});
    }
    if (it == curw.end()) {
      it = find_if(curw.begin(), curw.end(), [](int x) { return x != b; });
    }
    assert(it != curw.end());
    best = it - curw.begin();
    my_sum += pw10[curw[best]] * d;
    put(best);
  }
  total_sum += my_sum / S;
  eprintf("sum is %lf\n", my_sum / S);
}


int main() {
  int t;
  pw10[0] = 1;
  for (size_t i1 = 1; i1 < size(pw10); i1++) {
    pw10[i1] = pw10[i1 - 1] * 10;
  }
  scanf("%d%d%d%*d", &t, &n, &b);
  for (int i = 0; i < t; i++) {
    solve();
  }
  eprintf("avg = %lf\n", total_sum / t);

  return 0;
}
