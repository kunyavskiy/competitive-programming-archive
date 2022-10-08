#include <cstdio>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

uint64_t rnd(int x) {
  static uint64_t a = 13345423067492364466LLU, b = 7560982648573018527LLU;
  uint64_t c = a ^ a << 23;
  a = b;
  b ^= b >> 5 ^ c ^ c >> 18;;
  return (a + b) % x;
}

int lrand(int l, int r) {
  return l + 1LL * rand() * rand() % (r - l + 1);
}

int main() {
  srand(19260817);
  int n = 50000;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = i;
  }
  random_shuffle(v.begin(), v.end()/*, rnd*/);
  /*vector<bool> used(n);
  for (int i = 0; i < n; i++) {
    int id = lrand(0, n - 1);
    if (!used[id]) {
      used[id] = true;
      v.push_back(id);
    }
  }
  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      v.push_back(i);
    }
  }*/
  vector<int> a(n);
  vector<int> next(n);
  for (int i = 0; i < n; i++) {
    a[v[i]] = i + 1;
    next[v[i]] = (i == n - 1) ? -2 : v[i + 1];
  }
  printf("%d %d %d\n", n, v[0] + 1, n + 100);
  for (int i = 0; i < n; i++) {
    printf("%d %d\n", a[i], next[i] + 1);
  }
}
