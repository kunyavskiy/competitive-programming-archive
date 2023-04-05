#include <bits/stdc++.h>
using namespace std;

int main() {
  freopen("j.in", "w", stdout);
  int n = 3e5;
  cout << n << endl;
  for (int i = 0; i < n; i++) cout << rand() % (int)1e9 + 1 << " ";
  cout << endl;
  //ll L = rand() % (int)1e9 + 1;
  long long L = 1e10;
  long long R = L + 3e5;
  cout << L << " " << R << endl;
}
