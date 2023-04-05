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
#include <iomanip>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

typedef pair<double, double> item;

item zeroSum = {1, 0};

item sum(item a, item b) {
  return {a.first * b.first + a.second * b.second, a.first * b.second + a.second * b.first};
}

vector<item> sums;

int size;

void put(int i, item x, int n, int L, int R) {
  if (R == L + 1) {
    sums[n] = x;
    return;
  }
  int M = (L + R) >> 1;
  if (i < M) {
    put(i, x, 2 * n + 1, L, M);
  } else {
    put(i, x, 2 * n + 2, M, R);
  }
  sums[n] = sum(sums[2 * n + 1], sums[2 * n + 2]);
}

item sum(int l, int r, int n, int L, int R) {
  if (l >= R || L >= r) return zeroSum;
  if (L >= l && R <= r) {
    return sums[n];
  }
  int M = (L + R) >> 1;
  return sum(sum(l, r, 2 * n + 1, L, M), sum(l, r, 2 * n + 2, M, R));
}

void init(int n) {
  size = 1;
  while (size < n) size *= 2;
  sums.assign(2 * size, zeroSum);
}

void init(vector<item> a) {
  int n = a.size();
  init(n);
  size = 1;
  while (size < n) size *= 2;
  sums.assign(2 * size, zeroSum);
  for (int i = 0; i < n; i++) {
    sums[size - 1 + i] = a[i];
  }
  for (int i = size - 2; i >= 0; i--) {
    sums[i] = sum(sums[2 * i + 1], sums[2 * i + 2]);
  }
}

void put(int i, item x) {
  put(i, x, 0, 0, size);
}

item sum(int l, int r) {
  return sum(l, r, 0, 0, size);
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  vector<int> l(n);
  vector<int> r(n);
  vector<double> p(n);

  for (int i = 0; i < n; i++) {
    scanf("%d%d%lf", &l[i], &r[i], &p[i]);
    p[i] /= 100;
  }

  vector<pair<int, pair<int, item>>> events(2 * n);
  for (int i = 0; i < n; i++) {
    events[2 * i] = {l[i], {i, {1 - p[i], p[i]}}};
    events[2 * i + 1] = {r[i], {i, {1, 0}}};
  }
  sort(events.begin(), events.end());

  double last = 0;
  double res = 0;
  init(n);
  for (auto e: events) {
    double len = e.first - last;
    last = e.first;
    res += len * sum(0, n).second;
//    cout << len << " " << sum(0, n).second << "\n";
    put(e.second.first, e.second.second);
  }
  cout << setprecision(20);
  cout << res << "\n";

  return 0;
}
