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

char buf[5010];

string divide(string s, int b, int *rem) {
  string r;
  int cur = 0;
  for (char c : s) {
    cur *= 10;
    cur += c - '0';
    if (cur / b || r.size()) {
      r += char('0' + cur / b);
    }
    cur %= b;
  }
  if (rem) {
    *rem = cur;
  } else {
    assert(!rem);
  }
  return r;
}

void norm(string& s) {
  while (s.size() > 1 && s.front() == '0') {
    s = s.substr(1);
  }
}

void out(string s) {
  norm(s);
  if (s.empty()) s = "-";
  printf("%s\n", s.c_str());
}

void solve() {
  scanf("%s", buf);
  string c = buf;
  if (c == "0") {
    printf("0\n0\n0\n");
    return;
  }
  if ((c.back() - '0') % 2 == 0) {
    string a = divide(c, 2, nullptr);
    out(a); out(a); out(a);
    return;
  }
  int pos = c.size() - 1;
  while (pos >= 0 && c[pos] == '9') pos--;
  if (pos == -1) {
    string s;
    for (int i = 0; i < (int) c.size(); i++) {
      s += '4' + (i % 2);
    }
    out(s);
    out(s.substr(1) + char('0' + '9' - s.back()));
    out(s.substr(1));
    return;
  }
  char A = c[pos];
  char B = '0';
  string cc = c;
  if (pos != 0 && (c[pos - 1] - '0') % 2 != 0) {
    c[pos - 1]--;
    assert(A != '9');
    A++;
    B = '9';
  }
  string a = divide(c.substr(0, pos), 2, nullptr);
  string b = a;
  string r = a;
  a += A;
  b += B;
  for (int i = pos + 1; i < (int) c.size(); i++) {
    if (i % 2 == pos % 2) {
      a += A;
      b += '0' + ('9' - A);
      r += '0' + ('9' - A);
    } else {
      b += A;
      a += '0' + ('9' - A);
      r += A;
    }
  }
  int rem = 0;
  string s = divide(cc, 11, &rem);
  if (rem != 10 && s.size() > r.size()) {
    a = s + char('0' + rem);
    b = s;
    r = s;
  }
  out(a);
  out(b);
  out(r);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
