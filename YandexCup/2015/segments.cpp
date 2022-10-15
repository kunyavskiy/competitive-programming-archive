#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#define mp make_pair
using namespace std;

struct Line {
  int k, b;
  Line(int k, int b):k(k), b(b){}
  Line(){}
  double eval(double x) const {
    return k * x + b;  
  }
};

double intersect(const Line& a, const Line& b) {
  assert(a.k != b.k);
  return (b.b - a.b) *1.0 / (a.k - b.k);
}

vector<pair<double, Line>> norm(vector<pair<int, int>> l) {
  sort(l.rbegin(), l.rend());
  vector<pair<double, Line>> res;

  for (auto x : l) {
    Line nl(x.first, x.second);
    while (res.size() && res.back().second.eval(res.back().first) >= nl.eval(res.back().first))
	res.pop_back();
    if (res.empty()){
      res.push_back(mp(0, nl));
    } else {
      res.push_back(mp(intersect(res.back().second, nl), nl));
    }
  }

  return res;
}

int main(){
  int n;
  scanf("%d",&n);
  vector<pair<int, int>> st(n), en(n);
  for (int i = 0; i < n; i++) {
    int a, b, v;
    scanf("%d%d%d",&a,&b,&v);
    st[i] = mp(v, b);
    en[i] = mp(-v, -a);
  }

  auto up = norm(st);
  auto down = norm(en);

  int ptr1, ptr2;
  ptr1 = ptr2 = 1;
  double ans = up[0].second.eval(0) + down[0].second.eval(0);
  while (ptr1 < (int)up.size() || ptr2 < (int) down.size()) {
    double pos = 1e100;
    if (ptr1 != (int)up.size()) pos = min(pos, up[ptr1].first);
    if (ptr2 != (int)down.size()) pos = min(pos, down[ptr2].first);
    ans = max(ans, up[ptr1-1].second.eval(pos) + down[ptr2-1].second.eval(pos));
    if (ptr1 != (int)up.size() && (ptr2 == (int)down.size() || up[ptr1].first < down[ptr2].first))
	ptr1++;
    else
	ptr2++;
  }

  printf("%.10f\n", ans);

}
