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
#include <numeric>

#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class ArithmeticSequenceDiv1 {
public:
  int findMinCost(vector<int> v) {
    ll res = accumulate(v.begin(), v.end(), 0);
    for (int d = -10000; d <= 10000; d++) {
      vector<int> vv(v.size());
      for (int i = 0; i < (int)v.size(); i++) {
        vv[i] = v[i] - i * d;
      }
      nth_element(vv.begin(), vv.begin() + vv.size() / 2, vv.end());

      int val = vv[vv.size() / 2];
      ll ans = 0;
      for (int i = 0; i < (int)v.size(); i++) {
        ans += abs(vv[i] - val);
      }
      res = min(res, ans);
    }
    return (int)res;
  }
};



class ArithmeticSequenceDiv1Wrong {
public:
  int findMinCost(vector<int> v) {
    ll res = accumulate(v.begin(), v.end(), 0);
    for (int d = -200; d <= 200; d++) {
      vector<int> vv(v.size());
      for (int i = 0; i < (int)v.size(); i++) {
        vv[i] = v[i] - i * d;
      }
      nth_element(vv.begin(), vv.begin() + vv.size() / 2, vv.end());

      int val = vv[vv.size() / 2];
      ll ans = 0;
      for (int i = 0; i < (int)v.size(); i++) {
        ans += abs(vv[i] - val);
      }
      res = min(res, ans);
    }
    return (int)res;
  }
};

















