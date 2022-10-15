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


class PreviousOccurrence {
public:
    int findValue2(int d, int q) {
        if (d == 1) {
          if (q == 0) return 0;
          if (q == 1) return 1;
          return -1;
        }
        map<int, int> m;
        int last = 0;
        int cnt = 0;
        int done = 0;
        while (done <= 7000) {
          int next;
          auto it = m.find(last);
          if (it != m.end()) {
            next = cnt - it->second;
            it->second = cnt++;
          } else {
            next = d;
            m[last] = cnt++;
          }
          while (m.find(done) != m.end()) done++;
          if (done > 7000) break;
          last = next;
        }
        printf("last = %d\n", last);
        return cnt;
    }

    int findValue(int, int) {
      return findValue2(500, -1);
      /*int ans = 0;
      for (int i = 500; i <= 1000; i++) {
        int cur = findValue2(i, -1);
        ans = max(ans, cur);
        printf("%d %d %d\n", i, ans, cur);
      }
      return ans;*/
    }
};










