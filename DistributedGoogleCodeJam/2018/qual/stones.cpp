#include "message.h"
#include "stones.h"

#include <vector>
#include <cstdio>

using namespace std;

typedef long long ll;

int main() {
  int nodes = NumberOfNodes();
  int id = MyNodeId();

  int n = GetNumberOfStones() + 1;

  if (id >= n) {
    return 0;
  }

  nodes = min(nodes, n);

  int l = (n * id) / nodes;
  int r = (n * (id + 1)) / nodes;

  vector<int> to(r - l);

  for (int i = l; i < r; i++) {
    to[i - l] = GetJumpLength(i) + i;
  }

  for (int i = 1; i < r - l; i++) {
    to[i] = max(to[i], to[i - 1]);
  }

  assert(to.back() >= r);
  {
    int lmx = 0;

    if (id != 0) {
      Receive(id - 1);
      lmx = GetInt(id - 1);
    }
    if (id != nodes - 1) {
      PutInt(id + 1, max(lmx, to.back()));
      Send(id + 1);
    }

    for (int &i: to) {
      i = max(i, lmx);
    }
  }

//  fprintf(stderr, "to is done\n");


  vector<pair<int, int>> jumps(r - l);

  for (int i = r - 1; i >= l; i--) {
    if (to[i - l] >= r) {
      jumps[i - l] = {1, to[i - l]};
    } else {
      jumps[i - l] = jumps[to[i - l] - l];
      jumps[i - l].first += 1;
    }
//    fprintf(stderr, "%d %d %d [%d]\n", i, jumps[i - l].first, jumps[i - l].second, to[i-l]);
  }

  int requested = 0;
  if (id != 0) {
    Receive(id - 1);
    requested = GetInt(id - 1);
  }
//  fprintf(stderr, "requested = %d\n", requested);

  int to_request;
  if (requested >= r) {
    to_request = requested;
  } else {
    to_request = jumps[requested - l].second;
  }
//  fprintf(stderr, "to_requeste = %d\n", to_request);

  int to_request_result = 0;
  if (id == nodes - 1) {
    assert(to_request >= n);
  } else {
    PutInt(id + 1, to_request);
    Send(id + 1);
    Receive(id + 1);
    to_request_result = GetInt(id + 1);
  }

  int result = 0;
  if (requested >= r) {
    result = to_request_result;
  } else {
    result = to_request_result + jumps[requested - l].first;
  }
//  fprintf(stderr, "result = %d\n", result);

  if (id != 0) {
    PutInt(id - 1, result);
    Send(id - 1);
  } else {
    printf("%d\n", result);
  }
}
