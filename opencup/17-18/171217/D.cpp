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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

typedef pair<int, ll> vertex;

vector<ll> size(36);
map<vertex, vector<vertex>> graph;
set<vertex> vert;

vertex go(vertex v, char d) {
  if (d == 'c') {
    return {v.first + 1, v.second * 3};
  } else if (d == 'g') {
    if (v.first > 0 && v.second % 3 == 0) {
      return {v.first - 1, v.second / 3};
    } else {
      return {-1, -1};
    }
  } else if (d == 's') {
    return {v.first, (v.second + 1) % size[v.first]};
  } else {
    return {v.first, (v.second + size[v.first] - 1) % size[v.first]};
  }
}

void build(vertex v) {
  ll l = v.second;
  ll r = v.second;
  for (int i = v.first; i >= 0; i--) {
    l = l / 3 * 3;
    r = (r + 2) / 3 * 3;
    for (long j = l; j <= r; j++) {
      vert.insert({i, j % size[i]});
    }
    l /= 3;
    r /= 3;
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  size[0] = 1;
  for (int i = 1; i < (int)size.size(); i++) {
    size[i] = size[i - 1] * 3;
  }

  string s;
  cin >> s;
  vertex start = {0, 0};
  for (char c : s) {
    start = go(start, c);
  }
  cin >> s;
  vertex finish = {0, 0};
  for (char c : s) {
    finish = go(finish, c);
  }


  build(start);
  build(finish);

  vector<vertex> q;
  set<vertex> done;
  map<vertex, pair<char, vertex>> prev;
  done.insert(start);
  q.push_back(start);
  int h = 0;
  while (h < (int)q.size()) {
    vertex v = q[h++];
    if (v == finish) {
      break;
    }
    for (char c : "gsca") {
      vertex u = go(v, c);
      if (vert.count(u) != 0 && done.count(u) == 0) {
        done.insert(u);
        prev[u] = {c, v};
        q.push_back(u);
      }
    }
  }

  string res;
  vertex v = finish;
  while (v != start) {
    res += prev[v].first;
    v = prev[v].second;
  }
  reverse(res.begin(), res.end());
  cout << res;

  return 0;
}
