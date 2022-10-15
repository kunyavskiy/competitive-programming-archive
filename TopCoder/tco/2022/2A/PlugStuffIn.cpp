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


class PlugStuffIn {
public:
  vector<int> plug(vector<int> g) {
    multiset<int> s;
    s.insert(g.size());
    vector<int> ans(g.size());
    for (int i = 0; i < (int)g.size(); i++) {
      if (g[i] != 0) {
        ans[i] = *s.begin();
        s.erase(s.begin());
        for (int j = 0; j < g[i]; j++) s.insert(i);
      }
    }
    for (int i = 0; i < (int)g.size(); i++) {
      if (g[i] == 0) {
        if (s.empty()) return {};
        ans[i] = *s.begin();
        s.erase(s.begin());
      }
    }
    return ans;
  }
};










