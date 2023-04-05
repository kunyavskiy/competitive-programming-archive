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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

vector<string> inp;
vector<vector<int>> vs;
vector<int> vlast;

string readLine() {
  static char buf[200000];
  scanf("%s", buf);
  return buf;
}

const int MAXN = 510000;

int new_vertex() {
  static int ptr = 0;
  assert(ptr < MAXN);
  return ptr++;
}

struct edge {
  int to, w;
  char c;
};

vector<edge> v[MAXN];

void add_edge(int from, int to, int w, char c) {
  v[from].push_back({to, w, c});
}

void gen_simple(const vector<int>& v, const vector<char> &c) {
  int line_start, word_start;
  line_start = v[0];
  word_start = -1;
  for (int i = 0; i < (int)v.size(); i++) {
    if (v[i] == -1) {
      if (i + 1 < (int)v.size()) {
        line_start = v[i + 1];
      }
      continue;
    }
    if (i + 1 < (int)v.size() && c[i + 1] != '\n') {
      add_edge(v[i], v[i + 1], 1, 'l');
    }
    if (i && c[i - 1] != '\n') {
      add_edge(v[i], v[i - 1], 1, 'h');
    }
    if (word_start != -1) {
      add_edge(v[i], word_start, 1, 'b');
    }
    if (i && (c[i - 1] == '.' || c[i - 1] == '\n') && (c[i] != '.' && c[i] != '\n')) {
      word_start = v[i];
    }
    add_edge(v[i], line_start, 1, '0');
  }

  int line_end = -1;
  int last_word_begin = -1;
  for (int i = (int)v.size() - 1; i >= 0; i--) {
    if (v[i] == -1) {
      if (i) {
        line_end = v[i - 1];
      }
      continue;
    }
    if (line_end != -1) {
      add_edge(v[i], line_end, 1, '$');
    }
    if (last_word_begin != -1) {
      add_edge(v[i], last_word_begin, 1, 'w');
    }
    if (i && (c[i - 1] == '.' || c[i - 1] == '\n') && (c[i] != '.' && c[i] != '\n')) {
      last_word_begin = v[i];
    }
  }
}

vector<int> build_tree(vector<int> v, char c) {
  int n = (int)v.size();
  int lst = 1;
  while (lst < n) lst *= 2;
  vector<int> tree = vector<int> (2 * lst, -1);
  vector<int> size = vector<int> (2 * lst, 1);
  for (int i = 0; i < (int)v.size(); i++) {
    tree[lst + i] = v[i];
    size[lst + i] = 1;
  }
  for (int i = lst - 1; i > 0; i--) {
    tree[i] = new_vertex();
    size[i] = size[2 * i] + size[2 * i + 1];
    add_edge(tree[i], tree[2 * i], (c == 'j') ? 0 : size[2 * i], c);
    add_edge(tree[i], tree[2 * i + 1], (c == 'j') ? size[2 * i + 1] : 0, c);
  }
  return tree;
}

void add_tree_edge(const vector<int>& tree, int v, int l, int r, int L, int R, int from, int w) {
  if (r <= L || R <= l) return;
  if (L <= l && r <= R) {
    add_edge(from, tree[v], w, 'k');
    return;
  }

}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  scanf("%d", &n);
  inp.resize(n);
  vs.resize(n);
  vlast.resize(n);
  for (int i = 0; i < n; i++) {
    inp[i] = readLine();
    vs[i] = vector<int>(inp[i].size());
    for (int j = 0; j < (int)vs[i].size(); j++) {
      vs[i][j] = new_vertex();
    }
    vlast[i] = vs[i].back();
    vs[i].back() = new_vertex();
    add_edge(vlast[i], vs[i].back(), 0, 0);
  }

  vector<int> allv;
  vector<char> allc;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int)inp[i].size(); j++) {
      allv.push_back(vs[i][j]);
      allc.push_back(inp[i][j]);
    }
    allv.push_back(-1);
    allc.push_back('\n');
  }

  gen_simple(allv, allc);

  {
    vector<int> v;
    for (int i = 0; i < n; i++) {
      v.push_back(vs[i].back());
    }
    vector<int> tree = build_tree(v, 'k');
    vector<int> last(MAXN, -1);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < (int)vs[i].size(); j++) {
        int v = vs[i][j];
        if (j == (int)vs[i].size() - 1) {
          v = vlast[i];
        }
        if (last[j] != -1) {
          add_edge(v, last[j], i - last[j], 'k');
          add_tree_edge(tree, 1, 0, tree.size() / 2, last[j] + 1, i, v, 0);
        }
        last[j] = i;
      }
    }
  }


  return 0;
}
