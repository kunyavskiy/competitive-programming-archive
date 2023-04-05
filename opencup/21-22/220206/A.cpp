#include <bits/stdc++.h>

using namespace std;

struct AntSet {
  vector<int> ants;
  map<int, list<int>::iterator> edges;
};

struct DSU {
  vector<int> p;
  explicit DSU(int n) : p(n){
    std::iota(p.begin(), p.end(), 0);
  }

  void join(int a, int b) {
    p[b] = a;
  }
  int get(int a) {
    if (p[a] == a) return a;
    return p[a] = get(p[a]);
  }
};

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  vector<int> u(n - 1), v(n - 1);
  vector<set<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    cin >> u[i] >> v[i];
    --u[i];
    --v[i];
    g[u[i]].insert(i);
    g[v[i]].insert(i);
  }
  vector<AntSet> sets(n);
  DSU where(n);
  for (int i = 0; i < n; i++) {
    sets[i].ants.push_back(i);
  }
  vector<list<int>> lists(n - 1);

  auto addToList = [&](int setId, int listId, bool toEnd) {
    if (toEnd) {
      sets[setId].edges[listId] = lists[listId].insert(lists[listId].end(), setId);
    } else {
      sets[setId].edges[listId] = lists[listId].insert(lists[listId].begin(), setId);
    }
  };
  auto removeFromList = [&](int setId, int listId) {
    auto it = sets[setId].edges.find(listId);
    assert(it != sets[setId].edges.end());
    lists[listId].erase(it->second);
    sets[setId].edges.erase(it);
  };

  for (int i = 0; i < n - 1; i++) {
    addToList(u[i], i, false);
    addToList(v[i], i, true);
  }

  int tt;
  cin >> tt;
  long long ans = 0;
  while (tt--) {
    int to;
    cin >> to;
    --to;
    to = where.get(to);

    auto merge = [&](int a, int b) {
//      printf("%d and %d are merged\n", a, b);
      assert(sets[b].edges.size() == 1);
      removeFromList(b, sets[b].edges.begin()->first);
      ans += ((long long)sets[a].ants.size()) * ((long long)sets[b].ants.size());
      if (sets[a].ants.size() < sets[b].ants.size()) {
        sets[a].ants.swap(sets[b].ants);
      }
      sets[a].ants.insert(sets[a].ants.end(), sets[b].ants.begin(), sets[b].ants.end());
      where.join(a, b);
    };
    auto mergeLists = [&](int a, int b, bool aRev, bool bRev) {
      vector<int> ids;
      if (aRev != bRev) {
        ids.insert(ids.begin(), lists[b].begin(), lists[b].end());
      } else {
        ids.insert(ids.begin(), lists[b].rbegin(), lists[b].rend());
      }
      for (int x: ids) {
        addToList(x, a, !aRev);
        removeFromList(x, b);
      }
    };

    std::function<int(int, int)> dfs = [&](int v, int fromList) {
      int mergedTo = -1;
      for (auto edgesIter = sets[v].edges.begin(); edgesIter != sets[v].edges.end();) {
        auto [listId, iter] = *edgesIter;
        edgesIter = next(edgesIter);
        auto &list = lists[listId];
        assert(list.size() >= 2);
        if (listId == fromList) {
          continue;
        }
        int mergedId = dfs(list.back() + list.front() - v, listId);
        if (mergedId != -1) {
          if (sets[mergedId].edges.size() == 1) {
            int otherListId = sets[mergedId].edges.begin()->first;
            mergeLists(listId, otherListId, list.back() == v, lists[otherListId].back() == mergedId);
          } else {
            addToList(mergedId, listId, list.front() == v);
          }
        }
        if (v == list.front()) {
          removeFromList(v, listId);
          int next = list.front();
          if (mergedTo == -1) {
            mergedTo = next;
          } else {
            merge(mergedTo, next);
            addToList(mergedTo, listId, false);
          }
        } else {
          removeFromList(v, listId);
          int next = list.back();
          if (mergedTo == -1) {
            mergedTo = next;
          } else {
            merge(mergedTo, next);
            addToList(mergedTo, listId, true);
          }
        }
        if (list.size() == 1) {
          removeFromList(mergedTo, listId);
        }
      }
      return mergedTo;
    };

    for (auto [listId, iter]: sets[to].edges) {
      if (to != lists[listId].front()) {
        int mergedId = dfs(lists[listId].front(), listId);
        if (mergedId != -1) {
          addToList(mergedId, listId, false);
        }
      }
      if (to != lists[listId].back()) {
        int mergedId = dfs(lists[listId].back(), listId);
        if (mergedId != -1) {
          addToList(mergedId, listId, true);
        }
      }
    }
    for (auto edgesIter = sets[to].edges.begin(); edgesIter != sets[to].edges.end();) {
      auto [listId, iter] = *edgesIter;
      edgesIter++;
      if (iter != lists[listId].begin()) {
        merge(to, *prev(iter));
      }
      if (next(iter) != lists[listId].end()) {
        merge(to, *next(iter));
      }
      if (lists[listId].size() == 1) {
        removeFromList(to, listId);
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
