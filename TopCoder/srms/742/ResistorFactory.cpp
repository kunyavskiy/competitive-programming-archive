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


class ResistorFactory {
public:
  vector<int> construct(ll x) {
      ll y = (ll) ((ld(x) / 1e9) * (1LL << 31));
      vector<int> v;
      for (int i = 0; i < 31; i++) {
          v.push_back(i);
          v.push_back(i);
          v.push_back(1);
      }

      int id = v.size() / 3;
      vector<int> to_join;

      while (y) {
          if (y & 1) {
              to_join.push_back(id);
          }
          y /= 2;
          if (y) {
              v.push_back(id);
              v.push_back(id);
              v.push_back(0);
              id++;
          }
      }
      assert(id == to_join.back());
      to_join.pop_back();
      for (int x: to_join) {
          v.push_back(id);
          v.push_back(x);
          v.push_back(0);
          id++;
      }

      return v;
  }
};










