#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


static const int INF = 1 << 30;

class MaxFlow {

  typedef long long flow_type;
  const flow_type FLOW_INF = 1LL << 60;

  struct Edge {
    int to, next;
    flow_type f, c;
  };

  vector<Edge> es;
  int n;
  vector<int> head;
  vector<int> d;
  vector<int> ptr;

  flow_type dfs(int s, int t, flow_type have, flow_type min_edge) {
    if (s == t) {
      return have;
    }
    flow_type res = 0;
    for (int &i = ptr[s]; i != -1; i = es[i].next) {
      int to = es[i].to;
      if (d[to] != d[s] + 1) continue;
      if (es[i].c < min_edge) continue;
      flow_type done = dfs(to, t, min(have, es[i].c), min_edge);
      pushFlow(i, done);
      have -= done;
      res += done;
      if (have == 0) break;
    }
    return res;
  }

  bool bfs(int s, int t, flow_type min_edge) {
    queue<int> q;
    d = vector<int>(n, -1);
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      int e = head[v];
      while (e != -1) {
        if (es[e].c >= min_edge) {
          int to = es[e].to;
          if (d[to] == -1) {
            d[to] = d[v] + 1;
            q.push(to);
          }
        }
        e = es[e].next;
      }
    }
    return d[t] != -1;
  }

public:
  explicit MaxFlow(int n) : n(n), head(n, -1) {}

  int addVertex() {
    int id = n++;
    head.push_back(-1);
    return id;
  }

  int addEdge(int from, int to, flow_type c, flow_type rc = 0) {
//    printf("%d %d %lld\n", from, to, c);
    int id = (int) es.size();
    es.push_back({to, head[from], 0, c});
    head[from] = id;
    es.push_back({from, head[to], 0, rc});
    head[to] = id ^ 1;
    return id;
  }

  void pushFlow(int eid, flow_type val) {
    es[eid].f += val, es[eid].c -= val;
    es[eid ^ 1].f -= val, es[eid ^ 1].c += val;
  }

  flow_type getFlow(int s, int t) {
    flow_type res = 0;
    for (flow_type i = FLOW_INF; i >= 1; i /= 2) {
      while (bfs(s, t, i)) {
        ptr = head;
        res += dfs(s, t, FLOW_INF, i);
      }
    }
    return res;
  }
};


class DayAndNight {
public:
    int minimalCost(vector <int> a, vector <int> b, vector <int> day, vector <int> night, int dayToNight, int nightToDay) {
      ll ans = INF;
      int n = (int)day.size();

      for (int first = 0; first < 2; first++) {
        vector<int> ty;
        ty.push_back(first);
        int add = 0;

//        printf("\n\n\n\n\n\n");
        while ((int)ty.size() <= n) {
          int s = n * (ty.size() + 1);
          int t = s + 1;
          MaxFlow flow (t + 2);
          for (int i = 0; i < (int)ty.size(); i++) {
            for (int j = 0; j < n; j++) {
              flow.addEdge(i * n + j, (i + 1) * n + j, ty[i] ? night[j] : day[j]);
            }
            for (int j = 0; j < (int)a.size(); j++) {
              flow.addEdge(i * n + a[j], i * n + b[j], INF);
            }
          }
          for (int i = 0; i < n; i++) {
            flow.addEdge(s, i, INF);
            flow.addEdge(n * ty.size() + i, t, INF);
          }
          long long res = add + flow.getFlow(s, t);
//          printf("%d %d %lld\n", first, (int)ty.size(), res);
          ans = min(ans, res);
          if (ty.back() == 0) {
            ty.push_back(1);
            add += dayToNight;
          } else {
            ty.push_back(0);
            add += nightToDay;
          }
        }
      }
      return (int)ans;
    }
};










