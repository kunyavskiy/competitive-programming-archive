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


class StringRings {
public:
    double expectedRings(int A, int B) {
      int n = 2 * A + B;
      vector<double> lf(n + 1);
      for (int i = 1; i <= n; i++) {
        lf[i] = lf[i - 1] + log(i);
      }

      auto cnk_log = [&](int n, int k) {
        return lf[n] - lf[n - k] - lf[k];
      };

      double ans = 0;
      for (int a = 0; a <= A; a++) {
        for (int b = 1; b <= B; b++) {
          double cur = 0;

          // choose
          cur += 2 * (lf[A] - lf[A - a]);
          cur += lf[B] - lf[B - b] - lf[b];

          // connect
          cur -= lf[n];
          cur += lf[n - (2 * a + b)];

          // cycles
          cur += lf[2 * a + b - 1];
          cur -= lf[2 * a];
          cur += 2 * a * lf[2];


          ans += exp(cur);
        }
      }

      for (int a = 1; a <= A; a++) {
        double cur = 0;
        cur += 2 * cnk_log(A, a);
        cur += lf[a];
        cur += lf[a];

        cur += 2 * a * lf[2];

        cur -= log(a);
        cur -= lf[2];

        cur -= lf[n];
        cur += lf[n - 2 * a];

        ans += exp(cur);
      }

      return ans;
    }
};










