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


class MagicTrickWithCards {
  vector<int> solve(string q) {
    vector<int> pos;
    int cnt = 0;
    for (int i = 0; i < (int)q.size(); i++) {
      if (q[i] == '-') {
        ++cnt;
        pos.push_back(i);
        pos.push_back(i + 52);
        pos.push_back(i + 52 * 2);
      }
    }
    sort(pos.begin(), pos.end());
    int max_diff = 0;
    for (int i = 1; i < (int)pos.size(); i++) {
      max_diff = max(max_diff, pos[i] - pos[i - 1]);
    }
    for (int i = 1; i < (int)pos.size(); i++) {
      if (pos[i] - pos[i-1] == max_diff) {
        vector<int> ans;
        for (int j = i; j < i + cnt; j++) {
          ans.push_back(pos[j] % 52);
        }
        return ans;
      }
    }
    assert(false);
  }
public:
  vector<int> findTheirCard(vector<string> q, vector<int> x) {
    vector<int> ans(q.size());
    for (int i = 0; i < (int)q.size(); i++) {
      auto res = solve(q[i]);
      ans[i] = res[res.size() - x[i] - 1];
    }
    return ans;
  }
};










