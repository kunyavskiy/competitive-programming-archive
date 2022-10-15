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


struct item {
  ll tota;
  int m1, m2;
};

bool operator<(const item& a, const item& b) { return a.tota < b.tota; }

class ThreeWaySplit {
  map<ll, item> gen_masks(vector<int> a) {
    int all = (1 << a.size()) - 1;
    vector<ll> sum(all + 1);
    for (int i = 0; i <= all; i++) {
      for (int j = 0; j < (int)a.size(); j++) {
        if (i & (1 << j)) sum[i] += a[j];
      }
    }
    map<ll, item> result;
    auto update = [&](ll d, ll s, int m1, int m2) {
      if (result.find(d) == result.end()) {
        result[d] = item{ s,m1,m2 };
      } else {
        result[d] = max(result[d], item{s, m1, m2});
      }
    };
    for (int i = 0; i <= all; i++) {
      int other = all ^ i;
      update(sum[i], sum[i], i, 0);
      for (int j = other; j; j = (j - 1) & other) {
        update(sum[i] - sum[j], sum[i], i, j);
      }
    }
    return result;
  }

public:
  string split(vector<int> a) {
    int n = a.size();
    int m = n / 2;
    auto lf = gen_masks(vector<int>(a.begin(), a.begin() + m));
    auto rg = gen_masks(vector<int>(a.begin() + m, a.end()));
    item ans{0, 0, 0};
    for (auto x: lf) {
      ll d = x.first;
      item aitem = x.second;
      if (rg.find(-d) == rg.end()) continue;
      item bitem = rg[-d];
      item res = {aitem.tota + bitem.tota, aitem.m1 | (bitem.m1 << m), aitem.m2 | (bitem.m2 << m)};
      ans = max(ans, res);
    }
    string result;
    for (int i = 0; i < n; i++) {
      if (ans.m1 & (1 << i)) {
        result += "A";
      } else if (ans.m2 & (1 << i)) {
        result += "B";
      } else {
        result += "C";
      }
    }
    return result;
  }
};










