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


class DengklekGaneshAndDetention {
public:
  double getExpected(int n, int valInit, int valMul, int valAdd, int valMod) {
    vector<int> lamp(n);
    vector<double> prob(n);

    for (int i = 0; i < n; i++) {
      lamp[i] = valInit % 2;
      prob[i] = (valInit % 101) / 100.0;
      valInit = (int) ((valInit * 1LL * valMul + valAdd) % valMod);
    }

    double ans = 0;
    for (int i = 0; i < n; i++) {
      if (lamp[i]) ans -= 1;
    }

    double p[2];
    double e[2];

    p[0] = 1; p[1] = 0;
    e[0] = e[1] = 0;

    for (int i = 0; i < n; i++) {
      double np[2], ne[2];
      memset(np, 0, sizeof(np));
      memset(ne, 0, sizeof(ne));

      for (int j = 0; j < 2; j++) {
        if (lamp[i] ^ j) {
          ans += p[j] * (prob[i] * i + (1.0 - prob[i]) * (n - i - 1));
          for (int r = 0; r < 2; r++) {
            double P = (r == 0) ? prob[i] : (1.0 - prob[i]);
            np[j ^ r] += p[j] * P;
            if (r == 0) {
              ne[j] += ((i + 1) * p[j] - e[j]) * P;
            } else {
              ne[j ^ 1] += (e[j] + p[j]) * P;
            }
          }
        } else {
          np[j] += p[j];
          ne[j] += e[j];
        }
      }

      memcpy(p, np, sizeof(np));
      memcpy(e, ne, sizeof(ne));
    }


    return (ans + e[0] + e[1]) / 2;
  }
};










