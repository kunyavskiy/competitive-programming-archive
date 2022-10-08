#include <cstdio>
#include <message.h>
#include "majority.h"

int main(){
  int node_id = MyNodeId();
  int nodes = NumberOfNodes();
  int n = GetN();
  int best = 0;
  int count = 0;
  for (int i = node_id; i < n; i += nodes) {
    int id = GetVote(i);
    if (best == id || count == 0) {
      best = id, count++;
    } else {
      count--;
    }
  }

  if (node_id != 0) {
    Receive(node_id-1);
    int pbest = GetInt(node_id - 1);
    int pcount = GetInt(node_id - 1);
    if (pbest == best) {
      count += pcount;
    } else if (count > pcount) {
      count -= pcount;
    } else {
      best = pbest;
      count = pcount - count;
    }
  }

  if (node_id != nodes - 1) {
    PutInt(node_id + 1, best);
    PutInt(node_id + 1, count);
    Send(node_id + 1);
    Receive(nodes - 1);
    best = GetInt(nodes - 1);
  } else {
    for (int i = 0; i < nodes - 1; i++) {
      PutInt(i, best);
      Send(i);
    }
  }
  count = 0;
  for (int i = node_id; i < n; i += nodes) {
    int id = GetVote(i);
    if (best == id) {
      count++;
    }
  }
  
  if (node_id != nodes - 1) {
    PutInt(nodes - 1, count);
    Send(nodes - 1);
    return 0;
  }

  for (int i = 0; i < nodes - 1; i++) {
    int got = Receive(-1);
    count += GetInt(got);
  }

  if (count > n / 2) {
    printf("%d\n", best);
  } else {
    printf("NO WINNER\n");
  }

  return 0;
}
