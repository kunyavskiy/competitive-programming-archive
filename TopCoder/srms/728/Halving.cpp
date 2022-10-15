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


class Halving {
public:
  int minSteps(vector<int> _v) {
    vector<pair<int, int>> v;
    for (int x : _v) {
      v.push_back({x, x});
    }

    int cnt = 0;
    while (true) {
      int id = max_element(v.begin(), v.end()) - v.begin();
      bool ok = true;
      for (const auto& x : v) {
        if (x.second < v[id].first) {
          ok = false;
        }
      }
      if (ok) break;
      v[id].first = v[id].first / 2;
      v[id].second = (v[id].second + 1) / 2;
      cnt++;
    }
    return cnt;
  }
};










