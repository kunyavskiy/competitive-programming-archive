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


class CanidsSeesaw {

  int old_val;

  int eval(const vector<int> &a, const vector<int> &b, const vector<int> &order) {
    int val = 0;
    int score = 0;
    for (int i = 0; i < (int) a.size(); i++) {
      val -= a[i];
      val += b[order[i]];
      if (val > 0) score++;
    }
#ifdef LOCAL
    for (int i = 0; i < (int)a.size(); i++) {
      eprintf("%d ", b[order[i]]);
    }
    eprintf("= %d\n", score);
    assert(old_val == -1 || abs(old_val - score) <= 1);
#endif
    return old_val = score;
  }

public:

  vector<int> construct(vector<int> a, vector<int> b, int k) {
    old_val = -1;
    int n = a.size();
    vector<int> ord;
    for (int i = 0; i < n; i++) {
      ord.push_back(i);
    }
    sort(ord.begin(), ord.end(), [&b](int x, int y) { return b[x] < b[y];});

    if (eval(a, b, ord) == k) return ord;

    for (int i = 0; i < n; i++) {
      for (int j = 1; j < n; j++) {
        if (b[ord[j]] > b[ord[j - 1]]) {
          swap(ord[j], ord[j-1]);
          if (eval(a, b, ord) == k) return ord;
        }
      }
    }
    return vector<int>();
  }
};










