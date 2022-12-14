// Sample input 3, in CPP.
#include <cassert>
#include <cstdio>
#include "message.h"

long long GetPieceLength(long long node_index __attribute__((unused))) {
  return 3;
}

static char __S[301] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
char GetSignalCharacter(long long position) {
  assert(MyNodeId() * 300 / NumberOfNodes() <= position);
  assert((MyNodeId() + 1) * 300 / NumberOfNodes() > position);
  return __S[position];
}
