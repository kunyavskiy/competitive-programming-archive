#include <cstdio>
#include "message.h"
#include "johnny.h"
#include <algorithm>

using namespace std;

const int MAXN = 20000;

int wait_msg;
int done_vts;
int parent = -1;
int nodes, node_id;
int n;
vector<int> used;
vector<int> send;

void Terminate(){
  for (int i = 0; i < nodes; i++) {
    if (i != node_id) {
      PutInt(i, -3);
      Send(i);
    }
  }
  for (int i = 0; i < nodes - 1; i++) {
    int id = Receive(-1);
    done_vts += GetInt(id);
  }
  if (done_vts == n) 
    printf("IMPOSSIBLE\n");
  else
    printf("%d\n", n - done_vts);
  exit(0);
}


void visit(int v) {
  assert(v % nodes == node_id);
  if (used[v]) return;
  //printf("visiting %d\n", v);
  fflush(stdout);
  used[v] = true;
  vector<int> to_use;
  done_vts++;
  for (int i = 0; i < n; i++) {
    if (!send[i] && IsBetter(v, i)) {
      to_use.push_back(i);
      send[i] = true;
    }
  }
  sort(to_use.begin(), to_use.end(), [](int x, int y) { return (x + nodes - node_id - 1) % nodes < (y + nodes - node_id - 1) % nodes;});
  for (int i = 0; i < (int)to_use.size(); ) {
    int j = i;
    while (j < (int)to_use.size() && to_use[i] % nodes == to_use[j] % nodes) j++;
    if (to_use[i] % nodes != node_id) {
      int to = to_use[i] % nodes;
      PutInt(to, j - i);
      while (i < j) {
	//printf("sending %d to %d\n", to_use[i], to);
	fflush(stdout);
	PutInt(to, to_use[i]);
	i++;
      }
      Send(to);
      wait_msg++;
    } else {
      while (i < j) {
	visit(to_use[i++]);
      }
      assert(i == (int)to_use.size());
    }
  }
}

int main(){
  node_id = MyNodeId();
  nodes = NumberOfNodes();
  n = NumberOfCards();

  bool master = 0;
  int start = 0;
  for (int i = 1; i < n; i++)
    if (IsBetter(start, i))
      start = i;
  used = vector<int>(n);
  send = vector<int>(n);
  if (start % nodes == node_id) {
    master = true;
    //printf("I am master, start = %d\n", start);
    visit(start);
  } else {
    master = false;
  }


  if (master && wait_msg == 0) {
    Terminate();
  }

  while (true) {
    int id = Receive(-1);
    int type = GetInt(id);
    if (type == -3) {
      PutInt(id, done_vts);
      Send(id);
      return 0;
    } if (type == -2) {
      wait_msg--;
    } else {
      if (parent == -1 && !master) {
	parent = id;
      } else {
	PutInt(id, -2);
	Send(id);
      }
      for (int i = 0; i < type; i++) {
	visit(GetInt(id));  
      }
    }
    
    if (wait_msg == 0) {
      if (master) {
        Terminate();
      } else {
        assert(parent != -1);
        PutInt(parent, -2);
        Send(parent);
        parent = -1;
      }
    }
  }
}
