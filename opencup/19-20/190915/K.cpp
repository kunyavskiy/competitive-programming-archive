#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

// @author: pashka

struct Node;

vector<Node> nodes;

struct Node {
  int id, left, right, parent, size;

  void recalc() {
    size = 1;
    if (left >= 0) {
      nodes[left].parent = id;
      size += nodes[left].size;
    }
    if (right >= 0) {
      nodes[right].parent = id;
      size += nodes[right].size;
    }
  }
};

void init(int n) {
  nodes.resize(n);
  for (int i = 0; i < n; i++) {
    nodes[i].id = i;
    nodes[i].left = nodes[i].right = nodes[i].parent = -1;
    nodes[i].recalc();
  }
}

void rotate(int x) {
  int p = nodes[x].parent;
  int g = nodes[p].parent;
  if (nodes[p].left == x) {
    nodes[p].left = nodes[x].right;
    nodes[x].right = p;
  } else {
    nodes[p].right = nodes[x].left;
    nodes[x].left = p;
  }
  nodes[p].recalc();
  nodes[x].recalc();
  if (g >= 0) {
    if (nodes[g].left == p) nodes[g].left = x; else nodes[g].right = x;
    nodes[g].recalc();
  } else {
    nodes[x].parent = -1;
  }
}

void splay(int x) {
  while (nodes[x].parent >= 0) {
    int p = nodes[x].parent;
    int g = nodes[p].parent;
    if (g == -1) {
      rotate(x);
      return;
    }
    if ((x == nodes[p].right && p == nodes[g].right) ||
      (x == nodes[p].left && p == nodes[g].left)) {
      rotate(p);
      rotate(x);
    } else {
      rotate(x);
      rotate(x);
    }
  }
}

int max(int x) {
  while (nodes[x].right >= 0) {
    x = nodes[x].right;
  }
  splay(x);
  return x;
}

int merge(int x, int y) {
  if (x == -1) {
    return y;
  }
  x = max(x);
  nodes[x].right = y;
  nodes[x].recalc();
  return x;
}

pair<int, int> split_after(int x) {
  splay(x);
  int y = nodes[x].right;
  if (y >= 0) {
    nodes[y].parent = -1;
    nodes[x].right = -1;
    nodes[x].recalc();
  }
  return {x, y};
}

pair<int, int> split_before(int x) {
  splay(x);
  int y = nodes[x].left;
  if (y >= 0) {
    nodes[y].parent = -1;
    nodes[x].left = -1;
    nodes[x].recalc();
  }
  return {y, x};
}

int get_size(int x) {
  if (x == -1) return 0;
  return nodes[x].size;
}

int find_k(int x, int k) {
  if (k >= get_size(x)) return -1;
  int l = get_size(nodes[x].left);
  if (k < l) {
    return find_k(nodes[x].left, k);
  } else if (k == l) {
    return x;
  } else return find_k(nodes[x].right, k - l - 1);
}

void print(int x) {
  if (x == -1) return;
  print(nodes[x].left);
  cout << x << " ";
  print(nodes[x].right);
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);

  int n;
  cin >> n;
  int last = 0;

  vector<int> a;
  vector<int> p;
  p.push_back(-1);

  for (int t = 0; t < 2; t++) {
    Node node;
    node.id = nodes.size();
    node.left = node.right = node.parent = -1;
    node.recalc();
    nodes.push_back(node);
  }
  {
    int bg = nodes.size() - 2;
    int en = nodes.size() - 1;
    merge(bg, en);
  }

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    if (s == "add") {
      cin >> s;
      int x = ((s[0] - 'a') + last) % 26;
      a.push_back(x);
      int k = p.back();
      while (k >= 0 && a[k] != a.back()) k = p[k];
      p.push_back(k + 1);

      for (int t = 0; t < 2; t++) {
        Node node;
        node.id = nodes.size();
        node.left = node.right = node.parent = -1;
        node.recalc();
        nodes.push_back(node);
      }

      int bg = nodes.size() - 2;
      int en = nodes.size() - 1;

      int rt = merge(bg, en);

      auto q = split_after(2 * p.back());
      rt = merge(q.first, rt);
      rt = merge(rt, q.second);

//      print(rt);
//      cout << "\n";

    } else {
      int k;
      cin >> k;
      k = ((k - 1) + last) % (a.size()) + 1;

      auto q = split_before(2 * k);
      auto w = split_after(2 * k + 1);

//      print(w.first);
//      cout << " <<< \n";

      last = nodes[w.first].size / 2;

      int rt = merge(w.first, w.second);
      rt = merge(q.first, rt);

      cout << last << "\n";
    }
  }


  return 0;
}
