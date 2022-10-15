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


class TwoDimensionalSort {
public:
  vector<int> sortLetters(vector<string> a) {
    vector<int> ans1, ans2;
    int ptr = 0;
    for (int i = 0; i < (int) a.size(); i++) {
      vector<int> from, to;
      for (int j = 0; j < (int) a[i].size(); j++) {
        if (a[i][j] != '.') {
          from.push_back(j);
          to.push_back(ptr++);
          ans2.push_back(i);
          ans2.push_back(to.back());
          ans2.push_back(a[i][j] - 'A');
          ans2.push_back(to.back());
        }
      }
      while (from != to) {
        for (int id = 0; id < (int) from.size(); id++) {
          bool can_go;
          if (from[id] < to[id]) {
            can_go = id == (int) from.size() - 1 || from[id + 1] > to[id];
          } else {
            can_go = id == 0 || from[id - 1] < to[id];
          }
          if (can_go) {
            ans1.push_back(i);
            ans1.push_back(from[id]);
            ans1.push_back(i);
            ans1.push_back(to[id]);
            from[id] = to[id];
          }
        }
      }
    }

    ans1.insert(ans1.end(), ans2.begin(), ans2.end());
    return ans1;
  }
};










