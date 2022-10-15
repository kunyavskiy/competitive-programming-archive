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


class BigJump {

public:
  vector<int> construct(int n) {
    if (n == 1) return {0};
    if (n % 2 == 1) return {};
    vector<int> nxt(n);
    for (int i = 0; i < n; i++) {
      nxt[i] = (2 * i - (i / (n / 2)) + n) % n;
    }
    while (true) {
      set<int> s;
      s.insert(0);
      for (int i = nxt[0]; i != 0; i = nxt[i]) {
        s.insert(i);
      }
      if (s.size() == n) {
        break;
      }
      for (int a : s) {
        if (!s.count((a + n / 2) % n)) {
          swap(nxt[a], nxt[(a + n / 2) % n]);
          break;
        }
      }
    }
    vector<int> p;
    p.push_back(0);
    for (int i = nxt[0]; i != 0; i = nxt[i]) {
      p.push_back(i);
    }
    return p;
  }
};










