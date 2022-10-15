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

const int MOD = 1000000007;

int sum(int a, int b) {
  if ((a += b) >= MOD) a -= MOD;
  return a;
}

struct item {
  int value, ways;
};

item operator+(const item& a, const item &b) {
  if (a.value > b.value) {
    return a;
  } else if (a.value < b.value) {
    return b;
  } else {

    return {a.value, sum(a.ways, b.ways)};
  }
}

struct Fenvik {
  vector<vector<item>> v;
  int n;
public:
  Fenvik(int n) : v(n, vector<item>(n)), n(n) {}

  item get(int x, int y) {
    item res{-1, 0};
    for (int i = x; i != -1; i = (i & (i + 1)) - 1) {
      for (int j = y; j != -1; j = (j & (j + 1)) - 1) {
        res = res + v[i][j];
      }
    }
    return res;
  }

  void set(int x, int y, item r) {
    for (int i = x; i < n; i = (i | (i + 1))) {
      for (int j = y; j < n; j = (j | (j + 1))) {
        v[i][j] = v[i][j] + r;
      }
    }
  }
};


class RochesterSequence {
  struct truple {
    int a, b, c;

    truple(int a, int b, int c) : a(a), b(b), c(c) {}

    bool operator<(const truple &rhs) const {
      return std::tie(a, b, c) < std::tie(rhs.a, rhs.b, rhs.c);
    }
  };

public:
  vector<int> solve(vector <int> s, int n, int a, int b, int m) {
    while ((int)s.size() < n) {
      s.push_back((s.back() * 1LL * a + b) % m);
    }

    vector<truple> v;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        v.emplace_back(s[i] + s[j], i, n - j - 1);
      }
    }
    sort(v.begin(), v.end());

    Fenvik f(n);
    for (const truple& t : v) {
      item r = f.get(t.b - 1, t.c - 1);
      item nr = r + item{0, 1};
      nr.value += 1;
      f.set(t.b, t.c, nr);
    }
    item res = f.get(n - 1, n - 1);
    return {res.value * 2, res.ways};
  }
};










