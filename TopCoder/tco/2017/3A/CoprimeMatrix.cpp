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


static const char *NO = "Impossible";
static const char *YES = "Possible";

class CoprimeMatrix {
public:
  string isPossible(vector<string> v) {
    int n = (int) v.size();
    vector<int> eq(n, -1);
    vector<vector<int>> neq(n, vector<int>());
    
    vector<int> mind(n, -1);
    mind[1] = 1;
    for (int i = 2; i < n; i++) {
      for (int j = i; j < n; j+= i) {
        if (mind[j] == -1) {
          mind[j] = i;
        }
      }
    }

    if (v[0][0] == 'Y') {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          bool ok1 = v[i][j] == 'Y';
          bool ok2 = __gcd(i + 1, j + 1) == 1;
          if (ok1 != ok2) return NO;
        }
      }
      return YES;
    }
    
    for (int i = 0; i < n; i++) {
      if (v[i][i] == 'Y') return NO;
      for (int j = i + 1; j < n; j++) {
        if (v[i][j] != v[j][i]) {
          return NO;
        }
        int k = j - i;
        if (k == 1) {
          if (v[i][j] == 'N') {
            return NO;
          } else {
            continue;
          }
        }
        if (mind[k] == k) {
          int val = (k - i % k) % k;
          if (v[i][j] == 'N') {
            if (eq[k] == -1 || eq[k] == val) {
              eq[k] = val;
            } else {
              return NO;
            }
          } else {
            neq[k].push_back(val);
          }
        } else {
          bool p1 = v[i][j] == 'N';
          bool p2 = v[i][i + mind[k]] == 'N' || v[i][i + k / mind[k]] == 'N';
          if (p1 != p2) return NO;
        }
      }
    }

    for (int i = 1; i < n; i++) {
      for (int x : neq[i]) {
        if (eq[i] == x) {
          return NO;
        }
      }
      sort(neq[i].begin(), neq[i].end());
      neq[i].erase(unique(neq[i].begin(), neq[i].end()), neq[i].end());
      if ((int)neq[i].size() == i) {
        return NO;
      }
    }

    return YES;
  }
};










