#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("f.in", "w", stdout);
  int T = 2000;
  int n = T, m = T * 2;
  cout << n << " " << m << endl;
  for (int i = 0; i < m; i++) {
    cout << rand() % n + 1 << " " << rand() % n + 1 << " " << rand() % 100000 << endl;
  }
}
