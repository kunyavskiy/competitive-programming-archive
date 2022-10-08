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
unordered_map<long long, double> cache;

long long encode(const vector<int>& v) {
  long long res = 0;
  for (int x : v) {
    res = res * 239 + x;
  }
  return res;
}

double get(vector<int> v) {
  sort(v.begin(), v.end());
  auto [it, inserted] = cache.emplace(encode(v), 0);
  auto &res = it->second;
  if (*min_element(v.begin(), v.end()) == b) return res = 0;
  if (!inserted) { return res; }
  if (cache.size() % 100000 == 0) {
    eprintf("size = %d:", (int)cache.size());
    for (int x : v) eprintf(" %d", x);
    eprintf("\n");
  }
  vector<double> ans(n);
  for (int i = 0; i < n; i++) {
    if (v[i] != b) {
      v[i]++;
      ans[i] = get(v);
      v[i]--;
    } else {
      ans[i] = -1e100;
    }
  }
  for (int i = 0; i < 10; i++) {
    res += *max_element(ans.begin(), ans.end());
    for (int j = 0; j < n; j++) {
      ans[j] += pw10[v[j]];
    }
  }
  res /= 10;
  return res;
}

constexpr double S = 19131995794056374.42;
double total_sum = 0;

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
  constexpr int MAGIC[20] = {
    13, 13, 13, 13, 13,
    13, 13, 10, 10, 10,
     10,  10,  8,  8,  8,
     5,  5,  5,  5,  5
  };
  for (int i = 0; i < n; i++) {
    for (int it = 0; it < MAGIC[i]; it++) {
      scanf("%*d");
      put(i);
    }
  }
  for (int x : curw) { eprintf("%d ", x);}
  eprintf("\n");
  double my_sum = 0;
  eprintf("I think i can get %lf more (%lf%% of max), cache.size() = %d\n", get(curw), get(curw) / S * 100, (int)cache.size());
  while (done < n * b) {
    int d;
    scanf("%d", &d);
    int best = -1;
    double best_value = -1;
    for (int i = 0; i < n; i++) {
      if (curw[i] == b) continue;
      curw[i]++;
      double res = get(curw);
      curw[i]--;
      res += pw10[curw[i]] * d;
      if (res > best_value) {
        best_value = res;
        best = i;
      }
    }
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
