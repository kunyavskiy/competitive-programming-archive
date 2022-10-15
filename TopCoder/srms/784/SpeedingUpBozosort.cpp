#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

using matrix = vector<vector<double>>;

matrix operator*(const matrix &a, const matrix&b) {
  matrix c(a.size(), vector<double>(b[0].size()));
  for (int i = 0; i < (int)a.size(); i++) {
    for (int j = 0; j < (int)b.size(); j++) {
      for (int k = 0; k < (int)b[0].size(); k++){
        c[i][k] += a[i][j] * b[j][k];
      }
    }
  }
  return c;
}

class SpeedingUpBozosort {
  map<vector<int>, int> ids;
  vector<vector<int>> perms;

  vector<vector<double>> get_probs(vector<int> a, int cnt) {
    sort(a.begin(), a.end());
    do {
      ids[a] = perms.size();
      perms.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    matrix r(perms.size(), vector<double>(perms.size()));
    for (int i = 0; i < (int) perms.size(); i++) {
      for (int j = 0; j < (int) a.size(); j++) {
        for (int k = 0; k < (int) a.size(); k++) {
          vector<int> p = perms[i];
          swap(p[j], p[k]);
          int nid = ids[p];
          r[i][nid] += 1.0 / a.size() / a.size();
        }
      }
    }

    matrix res = r;
    cnt--;
    while (cnt) {
      if (cnt & 1) res = res * r;
      r = r * r;
      cnt /= 2;
    }
    return res;
  }

public:
  double expectedComparisons(vector<int> a, int num) {
    vector<vector<double>> m = get_probs(a, num);

    for (int i = 0; i < (int) perms.size(); i++) {
      int pos = 0;
      while (pos < (int) perms[i].size() - 1 && perms[i][pos] <= perms[i][pos + 1]) pos++;
      if (pos == (int) perms[i].size() - 1) {
        assert(i == 0);
        m[i] = vector<double>(perms.size());
      } else {
        for (auto& x : m[i]) {
          x *= -1;
        }
        pos++;
      }
      m[i][i] += 1;
      m[i].push_back(pos);
    }

    int n = perms.size();
    for (int i = 0; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (abs(m[j][i]) > abs(m[i][i])) {
          m[i].swap(m[j]);
        }
      }
      for (int j = n; j >= i; j--) {
        m[i][j] /= m[i][i];
      }
      for (int j = 0; j < n; j++) {
        if (j == i) continue;
        for (int k = n; k >= i; k--) {
          m[j][k] -= m[i][k] * m[j][i];
        }
      }
    }

    return m[ids[a]][n];
  }
};










