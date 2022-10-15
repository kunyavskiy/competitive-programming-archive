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


class DengklekGaneshAndChains {

  string get_max(string s, int k) {
      int l = s.size();
      s = s + s;
      string res = s.substr(0, k);
      for (int i = 1; i < l; i++) {
          string cur = s.substr(i, i + k);
          if (cur > res) {
              res = cur;
          }
      }
      return res;
  }

public:
  string getBestChains(vector<string> s, vector<int> l) {
    for (int i = 0; i < (int)s.size(); i++) {
      s[i] = get_max(s[i], s[i].size());
    }
    sort(s.rbegin(), s.rend());
    string res = "";
    vector<bool> used(s.size());
    for (int x : l) {
      int id = -1;
      for (int i = 0; i < (int)s.size(); i++) {
        if (used[i]) continue;
        if ((id == -1) || (s[i].substr(0, x) >= s[id].substr(0, x))) {
          id = i;
        }
      }
      assert(id != -1);
      used[id] = true;
      res += s[id].substr(0, x);
    }
    return res;
  }
};










