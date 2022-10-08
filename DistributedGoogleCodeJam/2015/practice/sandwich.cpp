#include "sandwich.h"
#include "message.h"
#include <cstdio>
#include <algorithm>

using namespace std;

int main(){
  int node_id = MyNodeId();
  int nodes = NumberOfNodes();
  int n = GetN();

  int l = (n * 1LL * node_id) / nodes;
  int r = (n * 1LL * (node_id+1)) / nodes;

  long long sum = 0;
  long long maxpref = 0;
  long long minpref = 0;
  long long ans = 0;

  for (int i = l; i < r; i++){
    sum += GetTaste(i);
    ans = min(ans, sum - maxpref);
    maxpref = max(maxpref, sum);
    minpref = min(minpref, sum);
  }

  if (node_id != 0) {
    Receive(node_id - 1);
    long long psum = GetLL(node_id - 1);
    long long pmaxpref = GetLL(node_id - 1);
    long long pans = GetLL(node_id - 1);

    ans = min(ans, pans);
    ans = min(ans, psum + minpref - pmaxpref); 
    sum = sum + psum;
    maxpref = max(pmaxpref, psum + maxpref);
  }

  if (node_id != nodes - 1) {
    PutLL(node_id + 1, sum);
    PutLL(node_id + 1, maxpref);
    PutLL(node_id + 1, ans);
    Send(node_id + 1);
  } else {
    printf("%lld\n", sum - ans);
  }
}
