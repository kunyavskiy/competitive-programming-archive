#include "message.h"
#include "towels.h"

#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

struct item {
  int v;
  int cnt;
  int ccnt;
  int stack;
  int pos;
};

void run_bin_search() {
  int p = GetNumberOfStacks();
  int k = GetNumberOfTowelsInStack();
  int nodes = NumberOfNodes() - 1;

  const int MAGIC = 1000;

  int need = GetNumberOfGymUsersBeforeYou();

  int lf = 0;
  int rg = p * k + 1;
  int lfv = 0;

  while (rg - lf > 1) {
    vector<int> splits;
    for (int i = 0; i <= MAGIC; i++) {
      splits.push_back(lf + (rg - lf) * 1LL * i / MAGIC);
    }
    sort(splits.begin(), splits.end());
    splits.erase(unique(splits.begin(), splits.end()), splits.end());

//    fprintf(stderr, "split %d..%d for:", lf, rg);
//    for (int i : splits) {
//      fprintf(stderr, " %d", i);
//    }
//    fprintf(stderr,"\n");

    for (int i = 0; i < nodes; i++) {
      PutInt(i, 1);
      PutInt(i, splits.size());
      for (int x : splits) {
        PutInt(i, x);
      }
      Send(i);
    }

    vector<int> values(splits.size());

    for (int i = 0; i < nodes; i++) {
      Receive(i);
      for (int j = 0; j < (int)splits.size(); j++) {
        values[j] += GetInt(i);
      }
    }

//    fprintf(stderr, "values %d..%d are:", lf, rg);
//    for (int i : values) {
//      fprintf(stderr, " %d", i);
//    }
//    fprintf(stderr,"\n");

    assert(values[0] <= need);
    assert(values.back() > need);

    for (int i = 0; i < splits.size(); i++) {
      if (values[i] <= need && values[i + 1] > need) {
        lf = splits[i];
        rg = splits[i + 1];
        lfv = values[i];
        break;
      }
    }
  }

  for (int i = 0; i < nodes; i++) {
    PutInt(i, 2);
    PutInt(i, lf);
    PutInt(i, lfv);
    Send(i);
  }
}

int main() {
  int nodes = NumberOfNodes();
  int id = MyNodeId();

  int master = nodes - 1;
  if (id == master) {
    run_bin_search();
    return 0;
  }

  int p = GetNumberOfStacks();
  int k = GetNumberOfTowelsInStack();

  int l = (p * id) / master;
  int r = (p * (id + 1)) / master;

  vector<item> v;

  for (int i = l; i < r; i++) {
    for (int j = k - 1; j >= 0; j--) {
      int x = GetTowelCleanlinessRank(i, j);
      if (j == k - 1 || v.back().v < x) {
        v.push_back({x, 1, 0, i, j});
      } else {
        v.back().cnt++;
      }
    }
  }

  sort(v.begin(), v.end(), [](const item &a, const item &b) {
    return a.v < b.v;
  });
  v.push_back({p * k + 1, 0, 0, -1, -1});
  int t = 0;
  for (auto& x : v) {
    x.ccnt = t;
    t += x.cnt;
  }

//  for (auto &x : v) {
//    fprintf(stderr, "v = %d, cnt = %d, ccnt = %d, i = %d, j = %d\n", x.v, x.cnt, x.ccnt, x.stack, x.pos);
//  }

  while (true) {
    Receive(master);
    int type = GetInt(master);
    if (type == 1) {
      int num = GetInt(master);
      for (int i = 0; i < num; i++) {
        int x = GetInt(master);
        if (x == 0) {
          PutInt(master, -1);
        } else {
          int t = lower_bound(v.begin(), v.end(), x, [](const item &a, int b) { return a.v < b; }) - v.begin();
          PutInt(master, v[t].ccnt);
        }
      }
      Send(master);
    } else {
      int x = GetInt(master);
//      fprintf(stderr, "x = %d\n", x);
      int t = lower_bound(v.begin(), v.end(), x, [](const item& a, int b) { return a.v < b;}) - v.begin();
      if (t != v.size() && v[t].v == x) {
        int after = GetNumberOfGymUsersBeforeYou() - GetInt(master);
//        fprintf(stderr, "after = %d\n", after);
        assert(after >= 0 && after < v[t].cnt);
        printf("%lld\n", GetTowelCleanlinessRank(v[t].stack, v[t].pos - after));
      }
      break;
    }
  }

}
