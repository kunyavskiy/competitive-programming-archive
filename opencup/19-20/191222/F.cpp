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
#include <random>

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

mt19937 rnd;

bool beats(vector<int> &a, vector<int> &b) {
  int i = 0;
  int j = 0;
  int n = 24;
  while (i < n && j < n) {
    int x = a[i];
    int y = b[j];
    if (x == y || x == 30 || y == 30) {
      i++; j++;
    } else if (x == 31 && y == 32) {
      i++;
    } else if (x == 32 && y == 31) {
      j++;
    } else if (x == 31) {
      j++;
    } else if (y == 31) {
      i++;
    } else if (x > y) {
      j++;
    } else {
      i++;
    }
  }
  return i < n;
}

int fitness(vector<int> &a, vector<int> &b) {
  int n = 24;
  int res = 0;
  if (beats(a, b)) res++;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      swap(a[i], a[j]);
      if (beats(a, b)) res++;
      swap(a[i], a[j]);
    }
  }
  return res;
}

void shuffle(vector<int> &a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int j = rnd() % (i + 1);
    swap(a[i], a[j]);
  }
}

void solve_test() {
  int n = 24;
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }
  vector<int> a = b;
  shuffle(a);
  int s = fitness(a, b);
  while (s < 24 * 23 / 2 + 1) {
//    cerr << s << "\n";
    int i = rnd() % n;
    int j = rnd() % n;
    swap(a[i], a[j]);
    int ss = fitness(a, b);
    if (ss >= s) {
      s = ss;
    } else {
      swap(a[i], a[j]);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i< n; i++) solve_test();

//  cout << 100 << "\n";
//  for (int i = 0; i < 100; i++) {
//    vector<int> a = {40, 39, 38, 38, 37, 37, 36, 36, 35, 35, 34, 34, 34, 33, 33, 33, 32, 32, 32, 31,
//                     31, 31, 30, 30};
//    shuffle(a);
//    for (int x : a) {
//      cout << x << " ";
//    }
//    cout << "\n";
//  }


  return 0;
}
