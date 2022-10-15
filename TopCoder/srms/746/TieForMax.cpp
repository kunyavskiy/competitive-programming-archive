#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef long double ld;


class TieForMax {
  vector<int> cur;
  double ans;
  int d;
  vector<double> logf;
  int n;

  void go(int n) {
    if (cur.size() >= 2 && cur[0] != cur[1]) return;
    if ((int)cur.size() == d) {
      if (n != 0) {
        return;
      }
      double res = - this->n * log(d);
      res += logf[this->n];
      for (int x : cur) {
        res -= logf[x];
      }
      res += logf[d];
      for (int i = 0; i < d;) {
        int j = i;
        while (j < d && cur[j] == cur[i]) j++;
        res -= logf[j - i];
        i = j;
      }
      res = exp(res);

      ans += res;
      return;
    }
    int limit = cur.empty() ? n : min(n, cur.back());
    for (int i = limit; i >= 0; i--) {
      cur.push_back(i);
      go(n - i);
      cur.pop_back();
    }
  }

public:
  double getProbability(int n, int d) {
    if (d == 1) return 0;
    logf.resize(200);
    for (int i = 1; i < (int)logf.size(); i++) {
      logf[i] = logf[i - 1] + log(i);
    }
    this->d = d;
    this->n = n;
    cur.reserve(d);
    go(n);
    return ans;
  }
};










