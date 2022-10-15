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


class MostFrequentLastDigit {
public:
  vector <int> generate(int n, int d) {
    if (d == 0) {
      vector<int> ans;
      for (int i = 1; i <= n; i++) {
        ans.push_back(i * 5);
      }
      return ans;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
      if (i & 1) {
        ans.push_back((10 * i + 9) * d);
      } else {
        ans.push_back((10 * i + 2) * d);
      }
    }
    return ans;
  }
};
