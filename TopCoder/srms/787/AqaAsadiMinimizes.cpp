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

class SegmentTree {
  typedef double value_t;

  static constexpr value_t EMPTY_VALUE = -1e100;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return max(a, b);
  }

  vector<value_t> tree;
  int lst;

public:
  void init(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t)(2 * lst), -1e9);
  }

  value_t get(int l, int r) {
    double ans = EMPTY_VALUE;
    l += lst;
    r += lst;
    while (l < r) {
      if (l & 1) ans = merge_values(ans, tree[l++]);
      if (r & 1) ans = merge_values(ans, tree[--r]);
      l /= 2;
      r /= 2;
    }
    return ans;
  }

  void update(int pos, double val) {
    pos += lst;
    tree[pos] = val;
    while (pos > 1) {
      pos /= 2;
      tree[pos] = merge_values(tree[2 * pos], tree[2 * pos + 1]);
    }
  }
};


class AqaAsadiMinimizes {
public:
  double getMin(vector<int> P, int B0, int X, int Y, int N) {
    vector<pair<int, int>> A(N);
    for (int i = 0; i < N; i++) {
      if (i < (int)P.size()) {
        A[i].first = P[i];
      } else if (i == (int)P.size()) {
        A[i].first = B0;
      } else {
        A[i].first = (A[i - 1].first * 1LL * X + Y) % 1000000007;
      }
      A[i].second = i;
    }
    sort(A.begin(), A.end());
    auto check1 = [&](double l) {
      SegmentTree tree;
      tree.init(A.size());
      for (auto x : A) {
        double lim = x.first + l * x.second;
        double have = tree.get(x.second, A.size());
        if (have >= lim) {
          return true;
        }
        tree.update(x.second, lim);
      }
      return false;
    };

    auto check = [&](double l) {
      if (check1(l)) { return true; }
      for (auto &x : A) x.first *= -1;
      reverse(A.begin(), A.end());
      bool res = check1(l);
      for (auto &x : A) x.first *= -1;
      reverse(A.begin(), A.end());
      return res;
    };

    double l = 0;
    double r = 1e9;
    for (int i = 0; i < 60; i++) {
      double m = (l + r) / 2;
//      printf("%d %le %le\n", i, l, r);
      if (check(m)) {
        r = m;
      } else {
        l = m;
      }
    }
    return (l + r) / 2;
  }
};










