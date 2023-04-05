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

using namespace std;

int main() {
  int n, k, m;
  cin >> n >> k >> m;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      cout << j + 1 << " ";
    }
    cout << endl;
    for (int j = 0; j < n - k; j++) {
      int x;
      cin >> x;
    }
  }

  return 0;
}
