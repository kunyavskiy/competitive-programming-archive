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


class SwapTheString {
public:
    ll findNumberOfSwaps(string s, int A0, int X, int Y, int n, int k) {
      vector<int> a;
      a.push_back(A0);
      while ((int)a.size() < n) {
        a.push_back((a.back() * 1LL * X + Y) % 1812447359);
      }
      while ((int)s.size() < n) {
        s += (a[s.size()] % 26 + 'a');
      }

//      printf("%s\n", s.c_str());

      ll ans = 0;
      for (int i = 0; i < k; i++) {
        vector<int> cnt(26);
        for (int j = i; j < n; j += k) {
          int p = s[j] - 'a';
          for (int t = 0; t < p; t++) {
            ans += cnt[t];
          }
          cnt[p]++;
        }
      }
      return ans;
    }
};










