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

const string YES = "Possible";
const string NO = "Impossible";

class ReverseAndIncrease {
public:
  string isPossible(ll x, ll y) {
    if (x <= y) return YES;


    while (true) {
      ll oldx = x;

      vector<int> digs;
      ll xx = x;
      while (xx > 0) {
        digs.push_back((int) (xx % 10));
        xx /= 10;
      }

      bool non9 = false;
      for (int i = (int) digs.size() - 1; i >= 0; i--) {
        if (non9) {
          digs[i] = !i;
        } else if (digs[i] != 9) {
          non9 = true;
          digs[i]++;
        }
      }

      x = 0;
      for (int d : digs) {
        x = x * 10 + d;
      }
      if (x >= oldx) {
        x = oldx;
        break;
      }
    }

    if (x <= y) return YES;
    return NO;
  }
};










