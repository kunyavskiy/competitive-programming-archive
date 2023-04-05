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

map<pair<int, int>, int> cache;

#ifdef LOCAL
#define TEST
#endif

#ifdef TEST
vector<int> place;
#endif

int convert(char c) {
  int res;
  if (c == '?') {
    res = 0;
  } else if (c == '+') {
    res = 1;
  } else if (c == '-') {
    res = -1;
  } else {
    assert(0);
  }
  return res;
}

char get_result(int pl1, int pl2) {
  if (pl1 <= 0 || pl1 == 3) {
    return  (pl2 > pl1) ? '+' : '?';
  } else if (pl1 == 1) {
    return  '?';
  } else if (pl1 == 2) {
    return (pl2 == 3) ? '+' : '?';
  } else if (pl1 > 3) {
    return (pl2 < pl1) ? '-' : '?';
  } else {
    assert(0);
  }
}

int ops = 0;

int ask(int x, int y) {
  assert(x != y);
  if (cache.find({x, y}) != cache.end()) {
    return cache[{x, y}];
  }
  ops++;
  char c;
#ifdef TEST
  c = get_result(place[x], place[y]);
#else
  printf("? %d %d\n", x + 1, y + 1);
  fflush(stdout);
  scanf(" %c", &c);
#endif
  return cache[{x, y}] = convert(c);
}

void answer(vector<int> v) {
#ifdef TEST
  if (v != place) {
    eprintf("expected:");
    for (int x : place) {
      eprintf(" %d", x);
    }
    eprintf("\n");
    eprintf("got:");
    for (int x : v) {
      eprintf(" %d", x);
    }
    eprintf("\n");
  } else {
    eprintf("ok with ops = %d:", ops);
    for (int x : v) {
      eprintf(" %d", x);
    }
    eprintf("\n");
    assert(ops <= 14000);
  }
#else
  printf("!");
  for (int i = 0; i < (int)v.size(); i++) {
    printf(" %d", v[i]);
  }
  printf("\n");
#endif
  exit(0);
}

void fix_firsts(vector<int> &firsts) {
  assert(firsts.size() == 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (i != j && ask(firsts[i], firsts[j]) == 1) {
        firsts = {firsts[3 - i - j], firsts[i], firsts[j]};
        return;
      }
    }
  }
}

void find_path(vector<int> &ids, int before_ans, int after_ans) {
  random_shuffle(ids.begin(), ids.end());
  vector<int> res;
  auto check = [&](int i, int j) {
    if (i == j) return false;
    int r = ask(i, j);
    assert(r == before_ans || r == after_ans);
    return r == before_ans;
  };
  for (int x : ids) {
    if (res.size() == 0) {
      res.push_back(x);
    } else {
      auto it = lower_bound(res.begin(), res.end(), x, check);
      res.insert(it, x);
    }
  }

  ids = res;
}

int main() {
#ifdef TEST
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
#ifdef TEST
  place = vector<int>(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &place[i]);
  }
#endif

  if (n <= 5) {
    for (int start = 4 - n; start <= 1; start++) {
      vector<int> order(n);
      for (int i = 0; i < n; i++) {
        order[i] = i + start;
      }
      do {
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
          for (int j = 0; j < n && ok; j++) {
            if (i != j) {
              ok &= ask(i, j) == convert(get_result(order[i], order[j]));
            }
          }
        }
        if (ok) {
          answer(order);
        }
      } while (next_permutation(order.begin(), order.end()));
    }
  }

  int cnt[3];
  memset(cnt, 0, sizeof(cnt));

  for (int i = 1; i < n; i++) {
    cnt[ask(0, i) + 1]++;
  }

  vector<int> firsts;

  if (cnt[1] == n - 1 || cnt[1] == n - 2) {
    firsts.push_back(0);
  } else if (cnt[2] == 0) {
    int tid = 0;

    for (int i = 1; i < n; i++) {
      if (ask(i, tid) == 1) continue;
      if (ask(tid, i) == -1) {
        tid = i;
      }
    }

    firsts.push_back(tid);
  } else {
    int tid = 0;

    for (int i = 1; i < n; i++) {
      if (ask(i, tid) == -1) continue;
      if (ask(tid, i) == 1) {
        tid = i;
      }
    }

    firsts.push_back(tid);
  }

  assert(firsts.size() == 1);
  for (int i = 0; i < n; i++) {
    if (i != firsts[0] && ask(i, firsts[0]) == 0) {
      firsts.push_back(i);
    }
  }

  assert(firsts.size() >= 2);
  if (firsts.size() == 2) {
    for (int i = 0; i < n; i++) {
      if (i != firsts[0] && i != firsts[1] && ask(i, firsts[0]) != ask(i, firsts[1])) {
        firsts.push_back(i);
        break;
      }
    }
  }

  assert(firsts.size() == 3);


  fix_firsts(firsts);

  vector<int> big, small;

  for (int i = 0; i < n; i++) {
    if (find(firsts.begin(), firsts.end(), i) != firsts.end()) {
      continue;
    }
    if (ask(i, firsts[2]) == -1) {
      small.push_back(i);
    } else {
      big.push_back(i);
    }
  }

  eprintf("ops = %d\n", ops);

  find_path(small, 0, -1);
  find_path(big, 1, 0);


  vector<int> ans(n);
  for (int i = 0; i < 3; i++) {
    ans[firsts[i]] = i + 1;
  }

  for (int i = 0; i < (int) small.size(); i++) {
    ans[small[i]] = i + 4;
  }

  for (int i = 0; i < (int) big.size(); i++) {
    ans[big[i]] = i - (int)big.size() + 1;
  }

  answer(ans);

  return 0;
}
