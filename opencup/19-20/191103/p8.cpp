#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

typedef long long ll;
typedef long double ld;

using namespace std;

int main() {
  int n;
  scanf("%d", &n);

  int s = 1;
  while (s < n) s *= 2;
  vector<int> a(2 * s);
  for (int i = 0; i < s; i++) {
    a[s + i] = i;
  }
  int ops = 0;
  auto query = [&](int x, int y) {
    if (x == y) return true;
    if (++ops >= n + 20) {
      assert(false);
    }
    printf("? %d %d\n", x, y);
    fflush(stdout);
    char c;
    scanf(" %c", &c);
    return c == '<';
  };
  for (int i = s - 1; i >= 1; i--) {
    int x = a[i * 2];
    int y = a[i * 2 + 1];

    if (y >= n) {
      a[i] = x;
    } else {
      if (query(x, y)) {
        a[i] = x;
      } else {
        a[i] = y;
      }
    }
  }
//  for (int i = 1; i < s + n; i++) {
//    cout << a[i] << " ";
//  }
//  cout << endl;
  int mn = a[1];
  int cur = -1;
  for (int i = 2; i < s + n; i++) {
    if (a[i / 2] == mn && a[i] != mn && a[i] < n) {
      if (cur == -1) {
        cur = a[i];
      } else {
        if (!query(cur, a[i])) {
          cur = a[i];
        }
      }
    }
  }
  printf("! %d\n", cur);
  fflush(stdout);

  return 0;
}
