#include <cstdio>
#include "message.h"
#include "almost_sorted.h"
#include <algorithm>

using namespace std;

int main(){
  int node_id = MyNodeId();
  int nodes = NumberOfNodes();
  int n = NumberOfFiles();
  
  int l = (n * 1LL * node_id) / nodes;
  int r = (n * 1LL * (node_id+1)) / nodes;

  int ll = max(0LL, l - MaxDistance());
  int rr = min(n * 1LL, r + MaxDistance());

  vector<long long> v(rr-ll);
  for (int i = ll; i < rr; i++) {
    v[i - ll] = Identifier(i);
  }
  sort(v.begin(), v.end());

  int ans = 0;
  for (int i = l; i < r; i++) {
    ans = (ans + v[i - ll] * i) & 0xfffff;
  }

  if (node_id == 0) {
    for (int i = 0; i < nodes - 1; i++) {
      int id = Receive(-1);
      ans = (ans + GetInt(id)) & 0xfffff;
    }
    printf("%d\n", ans);
  } else {
    PutInt(0, ans);
    Send(0);
  }
}
