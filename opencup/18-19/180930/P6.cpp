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

template <typename T>
struct myv {
  vector<T> data;
  int a, b, c, d;

  myv(int a, int b, int c, int d, T value) : data(a * b *c * d, value), a(a), b(b), c(c), d(d) {  }

  T& operator()(int A, int B, int C, int D) {
    return data[A * b * c * d + B * c * d + C * d + D];
  }
};

double expv(vector<int> s) {
  vector<int> cnt(4);
  for (int x : s) {
    cnt[__builtin_ctz(x)]++;
  }

  myv<double> dp(cnt[1] + 1, cnt[2] + 1, cnt[3] + 1, 8, 0);

  for (int i = 0; i <= cnt[0]; i++) {
    myv<double> ndp(cnt[1] + 1, cnt[2] + 1, cnt[3] + 1, 8, 0);
    for (int j = 0; j <= cnt[1]; j++) {
      for (int k = 0; k <= cnt[2]; k++) {
        for (int t = 0; t <= cnt[3]; t++) {
          for (int d = 0; d < 8; d++) {
            if (!i && !j && !k && !t) {
              ndp(j, k, t, d) = (-d) & (*max_element(s.begin(), s.end()) - 1);
            } else {
              double& ans = ndp(j, k, t, d);

              int sum = i + j + k + t;
              if (i) {
                ans += i * 1.0 / sum * (dp(j, k, t, (d + 1) & 7) + 1);
              }
              if (j) {
                int pad = (-d) & 1;
                ans += j * 1.0 / sum * (ndp(j - 1, k, t, (d + pad + 2) & 7) + 2 + pad);
              }
              if (k) {
                int pad = (-d) & 3;
                ans += k * 1.0 / sum * (ndp(j, k - 1, t, (d + pad + 4) & 7) + 4 + pad);
              }
              if (t) {
                int pad = (-d) & 7;
                ans += t * 1.0 / sum * (ndp(j, k, t - 1, (d + pad + 8) & 7) + 8 + pad);
              }
            }
          }
        }
      }
    }
    dp = ndp;
  }

  return dp(cnt[1], cnt[2], cnt[3], 0);
}

int maxv(vector<int> s) {
  vector<int> cnt(4);
  for (int x : s) {
    cnt[__builtin_ctz(x)]++;
  }

  myv<int> dp(cnt[1] + 1, cnt[2] + 1, cnt[3] + 1, 8, 0);

  for (int i = 0; i <= cnt[0]; i++) {
    myv<int> ndp(cnt[1] + 1, cnt[2] + 1, cnt[3] + 1, 8, 0);
    for (int j = 0; j <= cnt[1]; j++) {
      for (int k = 0; k <= cnt[2]; k++) {
        for (int t = 0; t <= cnt[3]; t++) {
          for (int d = 0; d < 8; d++) {
            if (!i && !j && !k && !t) {
              ndp(j, k, t, d) = (-d) & (*max_element(s.begin(), s.end()) - 1);
            } else {
              int& ans = ndp(j, k, t, d);

              if (i) {
                ans = max(ans, (dp(j, k, t, (d + 1) & 7) + 1));
              }
              if (j) {
                int pad = (-d) & 1;
                ans = max(ans, (ndp(j - 1, k, t, (d + pad + 2) & 7) + 2 + pad));
              }
              if (k) {
                int pad = (-d) & 3;
                ans = max(ans, (ndp(j, k - 1, t, (d + pad + 4) & 7) + 4 + pad));
              }
              if (t) {
                int pad = (-d) & 7;
                ans = max(ans, (ndp(j, k, t - 1, (d + pad + 8) & 7) + 8 + pad));
              }
            }
          }
        }
      }
    }
    dp = ndp;
  }

  return dp(cnt[1], cnt[2], cnt[3], 0);
}


int curv(vector<int> s) {
  int ans = 0;
  for (int x : s) {
    ans += (-ans) & (x - 1);
    ans += x;
  }
  ans += (-ans) & (*max_element(s.begin(), s.end()) - 1);
  return ans;
}

double expv_slow(vector<int> s) {
  vector<int> order(s.size());
  for (int i = 0; i < (int)s.size(); i++) {
    order[i] = i;
  }
  int cnt = 0;
  int ans = 0;
  do {
    cnt++;
    vector<int> os(s.size());
    for (int i = 0; i < (int)s.size(); i++) {
      os[i] = s[order[i]];
    }
    ans += curv(os);
  } while (next_permutation(order.begin(), order.end()));
  return ans * 1.0 / cnt;
}


int minv(vector<int> s) {
  sort(s.rbegin(), s.rend());
  return curv(s);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t = 0;
  while (false) {
    eprintf("%d\n", t++);
    int cnt = rand() % 8 + 1;
    vector<int> s(cnt);
    for (int i = 0; i < cnt; i++) {
      const int types[] = {1, 2, 4, 8};
      s[i] = types[rand() % 4];
    }
    double a1 = expv(s);
    double a2 = expv_slow(s);

    if (fabs(a1 - a2) > 1e-9) {
      eprintf("fail");
      for (int i : s) {
        eprintf("%d ", i);
      }
      eprintf("\n");
      eprintf("%lf %lf\n", a1, a2);
      break;
    }
  }

  scanf(" struct {");
  vector<int> s;
  while (true) {
    static char buf[1000000];
    scanf(" %[^ \r\n\t*;]", buf);
    eprintf("|%s|\n", buf);
    if (buf[0] == '}') {
      break;
    }
    if (strlen(buf) == 0) { continue; }

    pair<string, int> types[] = {
        {"char", 1},
        {"short", 2},
        {"int", 4},
        {"float", 4},
        {"int64_t", 8},
        {"double", 8},
    };

    int sz = 0;
    for (auto x : types) {
      if (x.first == buf) {
        sz = x.second;
      }
    }
    if (sz == 0) {
      printf("Wtf is %s\n", buf);
      exit(0);
    }
    scanf("%[^;];", buf);
    eprintf("|%s|\n", buf);
    for (int i = 0; buf[i]; i++) {
      if (buf[i] == '*') {
        sz = 8;
      }
    }
    eprintf("sz = %d\n", sz);
    s.push_back(sz);
  }

  printf("%d %d %.18lf\n", minv(s), maxv(s), expv(s));

  return 0;
}
