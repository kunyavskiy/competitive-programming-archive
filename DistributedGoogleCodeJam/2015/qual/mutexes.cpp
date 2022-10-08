#include <cstdio>
#include "message.h"
#include "mutexes.h"
#include <algorithm>

using namespace std;

int node_id, nodes;
int nodessq, idx, idy;


int mysqrt(int y){
  int x = sqrt(y);
  while (x * x > y) x--;
  while ((x+1) * (x+1) <= y) x++;
  return x;
}

const int MAXN = 4000;
const int MAXM = 100010;

int ln, rn, lm, rm;
int n, m;
char can[MAXN][MAXN];
int used[2][MAXM];
int curused[MAXN];
int op[2][MAXN * 10 + 10];
int best;

int getop(int x, int y) {
  if (y >= (x ? m : n) - 1) return x + 100005;
  if (op[x][y] != 0) return op[x][y];
  return op[x][y] = GetOperation(x, y);
}

int getCurUsed(int x, int time){
  if (abs(curused[x]) == time)
      return curused[x] > 0;
  return used[1][x];
}

vector<pair<int, int>> send_down;
vector<pair<int, int>> send_right;

void dfs(int x, int y) {
  if (x == n - 1 || y == m - 1) return;
  if (x == rn) {
    send_down.push_back(make_pair(x, y));
    return;
  }
  if (y == rm) {
    send_right.push_back(make_pair(x, y));
    return;
  }
  if (can[x][y] & 4) return;
  can[x][y] |= 4;
  if (can[x][y] & 1) dfs(x + 1, y);
  if (can[x][y] & 2) dfs(x, y + 1);
  if (can[x][y] == 4) best = min(best, x + y + 2);
}

void send(){
  if (!send_down.empty()){
    int nid = node_id + nodessq;
    assert(0 <= nid && nid < nodes);
    PutInt(nid, send_down.size());
    for (auto x : send_down){
      PutInt(nid, x.first);
      PutInt(nid, x.second);
    }
    Send(nid);
    send_down.clear();
  }
  if (!send_right.empty()){
    int nid = node_id + 1;
    assert(0 <= nid && nid < nodes);
    PutInt(nid, send_right.size());
    for (auto x : send_right){
      PutInt(nid, x.first);
      PutInt(nid, x.second);
    }
    Send(nid);
    send_right.clear();
  }
}

void send_end(){
  if (idx != nodessq-1) {
    int nid = node_id + nodessq;
    assert(0 <= nid && nid < nodes);
    PutInt(nid, -1);
    Send(nid);
  }
  if (idy != nodessq-1) {
    int nid = node_id + 1;
    assert(0 <= nid && nid < nodes);
    PutInt(nid, -1);
    Send(nid);
  }
}

int main(){
  node_id = MyNodeId();
  nodes = NumberOfNodes();
  nodessq = mysqrt(nodes);
  nodes = nodessq * nodessq;
  n = NumberOfOperations(0) + 1;
  m = NumberOfOperations(1) + 1;
  if (n <= nodes || m <= nodes) nodes = 1;
  if (node_id > nodes) return 0;
  idx = node_id / nodessq;
  idy = node_id % nodessq;

  ln = (n * 1LL * idx) / nodessq;
  rn = (n * 1LL * (idx+1)) / nodessq;
  lm = (m * 1LL * idy) / nodessq;
  rm = (m * 1LL * (idy+1)) / nodessq;
  best = n + m + 10;
  for (int it = 0; it < 2; it++) {
    for (int i = 0; i < (it ? lm : ln); i++) {
      int id = getop(it, i);
      if (id > 0) used[it][id] = true;
      else used[it][-id] = false;
    }
  }
  {
  int cur_time = 0;
  for (int i = ln; i < rn; i++) {
    ++cur_time;
    int nop = getop(0, i);
    for (int j = lm; j < rm; j++) {
	int mop = getop(1, j);
	if (j != m - 1 && (mop < 0 || !used[0][mop]))
	    can[i][j] |= 2;
	if (i != n - 1 && (nop < 0 || !getCurUsed(nop, cur_time)))
	    can[i][j] |= 1;
	if (mop > 0)
	    curused[mop] = cur_time;
	else
	    curused[-mop] = -cur_time;
    }
    if (nop > 0) used[0][nop] = 1;
    else used[0][-nop] = 0;
  }
/*  for (int i = ln; i < rn; i++)
      for (int j = lm; j < rm; j++)
	  printf("%d%c", can[i][j], " \n"[j==rm-1]);
  fflush(stdout);*/
  }

  if (idx == 0 && idy == 0) {
    dfs(0, 0);
    send();
    send_end();
  } else {
     int count = !idx + !idy;
     while (true) {
        int id = Receive(-1);
	int type = GetInt(id);
	if (type == -1) {
	  count--;
	  if (count == 0) {
	    send_end();
	    break;
	  }
	} else {
	  for (int i = 0; i < type; i++) {
	    int x = GetInt(id);
	    int y = GetInt(id);
	    dfs(x, y);
	    send();
	  }
	}
     }
  }

  if (idx == nodessq - 1 && idy == nodessq - 1) {
     for (int i = 0; i < nodes - 1; i++) {
        int id = Receive(-1);
	printf("got from %d\n", id);
	fflush(stdout);
	best = min(best, GetInt(id));
     }
     if (best == n + m + 10) {
	 printf("OK\n");
     } else {
	 printf("%d\n", best);
     }
  } else {
    PutInt(nodes - 1, best);
    Send(nodes - 1);
  }
}
