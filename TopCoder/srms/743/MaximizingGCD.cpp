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


class MaximizingGCD {
public:
  int maximumGCDPairing(vector<int> v) {
      map<int, int, greater<int>> cnt;
      for (int i = 0; i < (int) v.size(); i++) {
          for (int j = i + 1; j < (int) v.size(); j++) {
              int s = v[i] + v[j];
              for (int k = 1; k * k <= s; k++) {
                  if (s % k == 0) {
                      cnt[k]++;
                      if (s / k != k) {
                          cnt[s / k]++;
                      }
                  }
              }
          }
      }

      for (auto x : cnt) {
          if (x.second < (int)v.size() / 2) {
              continue;
          }

          int g = x.first;
          vector<bool> used(v.size());
          bool fail = false;
          for (int i = 0; i < (int)v.size(); i++) {
              if (!used[i]) {
                  bool ok = false;
                  for (int j = i + 1; j < (int)v.size(); j++) {
                      if (!used[j] && (v[i] + v[j]) % g == 0) {
                          used[i] = used[j] = true;
                          ok = true;
                          break;
                      }
                  }
                  if (!ok) {
                      fail = true;
                      break;
                  }
              }
          }
          if (!fail) {
              return g;
          }
      }
      assert(false);
  }
};










