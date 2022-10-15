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


class PigeonholeNim {

  bool goodd(int a) { return a != 4 && a != 7; }
  bool isGood(int a) {
    return goodd(a % 10) && goodd(a / 10 % 10) && goodd(a / 100);
  }
  vector<int> grund(vector<int> x, bool emptyWins, int id) {
    reverse(x.begin(), x.end());
    x.push_back(0);
    vector<int> v;
    auto mex = [](vector<int> a) {
      sort(a.begin(), a.end());
      a.erase(unique(a.begin(), a.end()), a.end());
      a.push_back(1e9);
      for (int i = 0;; i++) {
        if (a[i] != i) return i;
      }
    };
    for (int i = 0; i < (int)x.size(); i++) {
      if (x[i] == 0) return v;
      vector<int> nv(x[i] + 1);
      if (i == 0) {
        if (!emptyWins) {
          nv[0] = 1 << id;
        } else {
          nv[0] = 0;
        }
      } else {
        nv[0] = v.back();
      }
      for (int j = 1; j <= x[i]; j++) {
        vector<int> a;
        for (int m = 1; m < j; m++) {
          if (isGood(m)) {
            a.push_back(nv[j - m]);
          }
        }
        if (isGood(j)) {
          if (i == 0) {
            if (!emptyWins) {
              a.push_back(1 << id);
            } else {
              a.push_back(0);
            }
          } else {
            a.push_back(v[v.size() - 1]);
            a.push_back(v[v.size() - 2]);
          }
        }
        assert(j < (int)nv.size());
        nv[j] = mex(a);
        if (i == 0 && emptyWins && isGood(j)) {
          nv[j] = 1 << id;
        }
      }
      if (x[i+1] == 0) {
        if (i > 0) {
          nv.insert(nv.begin(), v[v.size() - 2]);
        }
        reverse(nv.begin(), nv.end());
        return nv;
      }
      v = nv;
    }
    assert(false);
  }
public:
    int countWinningMoves(int R, int C, vector <int> v, int emptyWins) {
    vector<vector<int>> moves;
    vector<int> lsz;
    for (int i = 0; i < C; i++) {
      vector<int> x(R);
      for (int j = 0; j < R; j++) {
        x[j] = v[R * i + j];
      }
      while (x.back() == 0) x.pop_back();
      lsz.push_back(x.back());
      moves.push_back(grund(x, emptyWins, i + 10));
    }
    int totg = 0;
    for (auto &x : moves) {
      totg ^= x[0];
    }
    int ans = 0;
    for (int i = 0; i < C; i++) {
      for (int j = 1; j < (int)moves[i].size(); j++) {
        if (isGood(min(lsz[i], j))) {
          if ((totg ^ moves[i][0] ^ moves[i][j]) == 0) ans++;
        }
      }
    }
    return ans;
  }
};










