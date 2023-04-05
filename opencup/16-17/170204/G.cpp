#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "G"

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

struct result {
  ll ops;
  vector<int> order;
};

map<vector<int>, result> cache;

result solve(vector<int> v) {
  if (v.size() == 0) {
    return {0, vector<int>()};
  }
  if (v.size() == 1) {
    return {1, v};
  }
  auto it = cache.find(v);
  if (it != cache.end()) {
    return it->second;
  }

  int first = -1;
  for (int i = 0; i < (int)v.size(); i++) {
    if (v[i] >= (int)v.size()) {
      first = i;
      break;
    }
  }
  assert(first != -1);

  result one = solve(vector<int>(v.begin(), v.begin() + first));
  vector<int> next(v.size(), -1);

  for (int i = first; i < (int)v.size(); i++) {
    next[i] = v[i];
  }
  for (int j : one.order) {
    for (int k = 1; k <= j; k++) {
      next[k - 1] = next[k];
    }
    next[j] = j;
  }
  assert(next[0] == v[first]);
  next.erase(next.begin(), next.begin() + 1);
  for (int i = 0; i < (int)next.size(); i++) {
    assert(next[i] != -1);
  }
  result other = solve(next);
  other.ops += one.ops + 1;
  other.order.insert(other.order.begin(), v[first]);
  return cache[v] = other;
}


int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  vector<int> x(n);
  int zero_pos = -1;
  for (int i = 0; i < n; i++) {
    scanf("%d", &x[i]);
    if (x[i] == 0) {
      zero_pos = i;
    }
  }
  assert(zero_pos != -1);
  if (zero_pos == 0) {
    printf("0\n");
  } else {
    result res = solve(vector<int>(x.begin(), x.begin() + zero_pos));
    printf("%lld\n", res.ops);
  }
  return 0;
}
