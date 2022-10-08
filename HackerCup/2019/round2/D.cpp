#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

vector<int> read_gen(int n) {
  vector<int> v(n);
  scanf("%d%d",&v[0],&v[1]);
  int a, b, c, d;
  scanf("%d%d%d%d", &a, &b, &c, &d);
  for (int i = 2; i < n; i++) {
    v[i] = (a * 1LL * v[i - 2] + b * 1LL * v[i - 1] + c) % d + 1;
  }
  return v;
}

struct item {
  int pos;
  int h;
  int ty;

  bool operator<(const item &rhs) const {
    return std::tie(h, ty) < std::tie(rhs.h, rhs.ty);
  }

  bool operator>(const item &rhs) const {
    return rhs < *this;
  }

  bool operator<=(const item &rhs) const {
    return !(rhs < *this);
  }

  bool operator>=(const item &rhs) const {
    return !(*this < rhs);
  }
};


void solve() {
  int n;
  scanf("%d", &n);
  vector<item> v(n);
  {
    vector<int> p = read_gen(n);
    for (int i = 0; i < n; i++) {
      v[i].pos = p[i];
    }
  }
  {
    vector<int> p = read_gen(n);
    for (int i = 0; i < n; i++) {
      v[i].h = p[i];
    }
  }
  int totc = 0;
  {
    static char s[1000000];
    scanf("%s", s);
    for (int i = 0; i < n; i++) {
      v[i].ty = s[i] == 'C';
      totc += v[i].ty;
    }
  }
  sort(v.begin(), v.end(), [](const item& a, const item& b) { return a.pos < b.pos; });

  vector<item> st;
  ll left = 0;
  ll ans = numeric_limits<ll>::max();
  vector<int> rpos;
  for (const item& a : v) {
    while (!st.empty() && st.back() <= a) {
      if (st.size() >= 2 && st.back().ty == 1) {
        left -= 2 * (st[st.size() - 1].pos - st[st.size() - 2].pos);
      }
      if (st.back().ty == 0) {
        rpos.pop_back();
      }
      st.pop_back();
    }
    st.push_back(a);
    if (st.size() >= 2 && st.back().ty == 1) {
      left += 2 * (st[st.size() - 1].pos - st[st.size() - 2].pos);
    }
    if (st.back().ty == 0) {
      rpos.push_back(a.pos);
    }
    totc -= a.ty;
    if (!totc) {
      if (st[0].ty == 0) {
        ans = min(ans, left + rpos.back());
      }
    }
  }
  if (ans == numeric_limits<ll>::max()) {
    ans = -1;
  }
  printf("%lld\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
