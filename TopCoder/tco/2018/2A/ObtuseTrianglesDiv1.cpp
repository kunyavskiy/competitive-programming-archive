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

const ll A = 1000;
const ll B = A * A;

class ObtuseTrianglesDiv1 {


  vector<ll> trybign(int a, int n) {
    vector<ll> ans;
    vector<bool> used(a + 3 * n);

    int shift = 0;
    int z = a + 3 * n - 1;

    for (int i = 0; i < n; i++) {
      int x = a + n - i - 1;
      while (used[z]) --z;
      int y = -1;
      for (int yy = z - x + 1; yy < z; yy++) {
        if (used[yy]) continue;
        if (x * x + yy * yy < z * z) {
          y = yy;
        }
      }
      if (y == -1) return {};
      if (x * x + y * y >= z * z) return {};
      if (x + y <= z) return {};
      assert(!used[x] && !used[y] && !used[y]);
      assert(x + y > z);
      assert(x * x + y * y < z * z);
      assert(a <= x && x < y && y < z && z <= a + 3 * n - 1);
      used[x] = used[y] = used[z] = 1;
      ans.push_back(x * A + y * B + z);
    }
    return ans;
  }
public:
  vector<ll> findObtuseTriangles(int a, int n) {
    if (a == 1) return {};
    if (n > 30) {
      auto r = trybign(a, n);
      if (r.empty()) {
        printf("Failed %d %d\n", a, n);
        exit(0);
      } else {
        printf("Ok %d %d\n", a, n);
      }
      return r;
    }
    return {};
  }
};










