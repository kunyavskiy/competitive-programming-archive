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

#undef assert
#define assert(x) x

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

template <typename CostType, typename TotalCostType=int64_t>
class MaximumWeightedMatching {
  /*
    Maximum Weighted Matching in General Graphs.
    - O(nm \log(n)) time
    - O(n + m) space
    Note: each vertex is 1-indexed.
    Ref:
      Harold N. Gabow,
      "Data Structures for Weighted Matching and
       Extensions to b-matching and f-factors" (2016)
      (https://arxiv.org/abs/1611.07541)
  */
public:
  using cost_t = CostType;
  using tcost_t = TotalCostType;

  enum Label { kSeparated = -2, kInner = -1, kFree = 0, kOuter = 1 };
  static constexpr cost_t Inf = cost_t(1) << (sizeof(cost_t) * 8 - 2);

  template <typename T>
  class BinaryHeap {
  public:
    struct Node {
      bool operator < (const Node& rhs) const { return value < rhs.value; }
      T value; int id;
    };
    BinaryHeap() {}
    BinaryHeap(int N) : size_(0), node(N + 1), index(N, 0) {}
    int size() const { return size_; }
    bool empty() const { return size_ == 0; }
    void clear() { while (size_ > 0) index[node[size_--].id] = 0; }
    T min() const { return node[1].value; }
    int argmin() const { return node[1].id; } // argmin ?
    T get_val(int id) const { return node[index[id]].value; }
    void pop() { if (size_ > 0) pop(1); }
    void erase(int id) { if (index[id]) pop(index[id]); }
    bool has(int id) const { return index[id] != 0; }
    void update(int id, T v) {
      if (!has(id)) return push(id, v);
      bool up = (v < node[index[id]].value);
      node[index[id]].value = v;
      if (up) up_heap(index[id]);
      else down_heap(index[id]);
    }
    void decrease_key(int id, T v) {
      if (!has(id)) return push(id, v);
      if (v < node[index[id]].value) node[index[id]].value = v, up_heap(index[id]);
    }
    void push(int id, T v) {
      // assert(!has(id));
      index[id] = ++size_; node[size_] = {v, id};
      up_heap(size_);
    }
    void pop(int pos) {
      index[node[pos].id] = 0;
      if (pos == size_) { --size_; return; }
      bool up = (node[size_].value < node[pos].value);
      node[pos] = node[size_--]; index[node[pos].id] = pos;
      if (up) up_heap(pos);
      else down_heap(pos);
    }
    void swap_node(int a, int b) {
      swap(node[a], node[b]); index[node[a].id] = a; index[node[b].id] = b;
    }
    void down_heap(int pos) {
      for (int k = pos, nk = k; 2 * k <= size_; k = nk) {
        if (node[2 * k] < node[nk]) nk = 2 * k;
        if (2 * k + 1 <= size_ && node[2 * k + 1] < node[nk]) nk = 2 * k + 1;
        if (nk == k) break;
        swap_node(k, nk);
      }
    }
    void up_heap(int pos) {
      for (int k = pos; k > 1 && node[k] < node[k >> 1]; k >>= 1) swap_node(k, k >> 1);
    }
    int size_;
    vector<Node> node;
    vector<int> index;
  };

  template <typename Key>
  class PairingHeaps {
    struct Node {
      Node() : prev(-1) {} // "prev < 0" means the node is unused.
      Node(Key v) : key(v), child(0), next(0), prev(0) {}
      Key key; int child, next, prev;
    };
  public:
    PairingHeaps(int H, int N) : heap(H), node(N) {
      // It consists of `H` Pairing heaps.
      // Each heap-node ID can appear at most 1 time(s) among heaps
      // and should be in [1, N).
    }

    void clear(int h) { if (heap[h]) clear_rec(heap[h]), heap[h] = 0; }
    void clear_all() {
      for (size_t i = 0; i < heap.size(); ++i) heap[i] = 0;
      for (size_t i = 0; i < node.size(); ++i) node[i] = Node();
    }
    bool empty(int h) const { return !heap[h]; }
    bool used(int v) const { return node[v].prev >= 0; }
    Key min(int h) const { return node[heap[h]].key; }
    int argmin(int h) const { return heap[h]; }

    void pop(int h) {
      // assert(!empty(h));
      erase(h, heap[h]);
    }
    void push(int h, int v, Key key) {
      // assert(!used(v));
      node[v] = Node(key);
      heap[h] = merge(heap[h], v);
    }
    void erase(int h, int v) {
      if (!used(v)) return;
      int w = two_pass_pairing(node[v].child);
      if (!node[v].prev) heap[h] = w;
      else {
        cut(v);
        heap[h] = merge(heap[h], w);
      }
      node[v].prev = -1;
    }
    void decrease_key(int h, int v, Key key) {
      if (!used(v)) return push(h, v, key);
      if (!node[v].prev) node[v].key = key;
      else {
        cut(v); node[v].key = key;
        heap[h] = merge(heap[h], v);
      }
    }

    void clear_rec(int v) {
      for (; v; v = node[v].next) {
        if (node[v].child) clear_rec(node[v].child);
        node[v].prev = -1;
      }
    }

    inline void cut(int v) {
      auto& n = node[v]; int pv = n.prev, nv = n.next;
      auto& pn = node[pv];
      if (pn.child == v) pn.child = nv;
      else pn.next = nv;
      node[nv].prev = pv;
      n.next = n.prev = 0;
    }

    int merge(int l, int r) {
      if (!l) return r;
      if (!r) return l;
      if (node[l].key > node[r].key) swap(l, r);
      int lc = node[r].next = node[l].child;
      node[l].child = node[lc].prev = r;
      return node[r].prev = l;
    }

    int two_pass_pairing(int root) {
      if (!root) return 0;
      int a = root; root = 0;
      while (a) {
        int b = node[a].next, na = 0;
        node[a].prev = node[a].next = 0;
        if (b) na = node[b].next, node[b].prev = node[b].next = 0;
        a = merge(a, b);
        node[a].next = root; root = a; a = na;
      }
      int s = node[root].next; node[root].next = 0;
      while (s) {
        int t = node[s].next; node[s].next = 0;
        root = merge(root, s);
        s = t;
      }
      return root;
    }

    vector<int> heap;
    vector<Node> node;
  };

  template <typename T>
  struct PriorityQueue : public priority_queue< T, vector<T>, greater<T> > {
    PriorityQueue() {}
    PriorityQueue(int N) { this->c.reserve(N);}
    T min() const { return this->top(); }
    void clear() { this->c.clear(); }
  };

  template <typename T>
  struct Queue {
    Queue() {}
    Queue(int N) : qh(0), qt(0), data(N) {}
    T operator [] (int i) const { return data[i]; }
    void enqueue(int u) { data[qt++] = u; }
    int dequeue() { return data[qh++]; }
    bool empty() const { return qh == qt; }
    void clear() { qh = qt = 0; }
    int size() const { return qt; }
    int qh, qt;
    vector<T> data;
  };

public:
  struct InputEdge { int from, to; cost_t cost; };

  template <typename T> using ModifiableHeap = BinaryHeap<T>;
  template <typename T> using ModifiableHeaps = PairingHeaps<T>;
  template <typename T> using FastHeap = PriorityQueue<T>;

  struct Edge { int to; cost_t cost; };
  struct Link { int from, to; };
  struct Node {
    struct NodeLink { int b, v; };
    Node() {}
    Node(int u) : parent(0), size(1) { link[0] = link[1] = {u, u}; }
    int next_v() const { return link[0].v; }
    int next_b() const { return link[0].b; }
    int prev_v() const { return link[1].v; }
    int prev_b() const { return link[1].b; }
    int parent, size;
    NodeLink link[2];
  };
  struct Event {
    Event() {}
    Event(cost_t time, int id) : time(time), id(id) {}
    bool operator < (const Event& rhs) const { return time < rhs.time; }
    bool operator > (const Event& rhs) const { return time > rhs.time; }
    cost_t time; int id;
  };
  struct EdgeEvent {
    EdgeEvent() {}
    EdgeEvent(cost_t time, int from, int to) : time(time), from(from), to(to) {}
    bool operator > (const EdgeEvent& rhs) const { return time > rhs.time; }
    bool operator < (const EdgeEvent& rhs) const { return time < rhs.time; }
    cost_t time; int from, to;
  };

public:
  MaximumWeightedMatching(int N, const vector<InputEdge>& in)
    : N(N), B((N - 1) / 2), S(N + B + 1), ofs(N + 2), edges(in.size() * 2),
      heap2(S), heap2s(S, S), heap3(edges.size()), heap4(S) {

    for (auto& e : in) ofs[e.from + 1]++, ofs[e.to + 1]++;
    for (int i = 1; i <= N + 1; ++i) ofs[i] += ofs[i - 1];
    for (auto& e : in) {
      edges[ofs[e.from]++] = {e.to, e.cost * 2};
      edges[ofs[e.to]++] = {e.from, e.cost * 2};
    }
    for (int i = N + 1; i > 0; --i) ofs[i] = ofs[i - 1];
    ofs[0] = 0;
  }

  tcost_t maximum_weighted_matching(bool init_matching=false) {
    initialize();
    set_potential();
    if (init_matching) find_maximal_matching();
    for (int u = 1; u <= N; ++u) if (!mate[u]) do_edmonds_search(u);
    tcost_t ret = compute_optimal_value();
    return ret;
  }

  tcost_t compute_optimal_value() const {
    tcost_t ret = 0;
    for (int u = 1; u <= N; ++u) if (mate[u] > u) {
        cost_t max_c = 0;
        for (int eid = ofs[u]; eid < ofs[u + 1]; ++eid) {
          if (edges[eid].to == mate[u]) max_c = max(max_c, edges[eid].cost);
        }
        ret += max_c;
      }
    return ret >> 1;
  }

  inline tcost_t reduced_cost(int u, int v, const Edge& e) const {
    return tcost_t(potential[u]) + potential[v] - e.cost;
  }

  void rematch(int v, int w) {
    int t = mate[v]; mate[v] = w;
    if (mate[t] != v) return;
    if (link[v].to == surface[link[v].to]) {
      mate[t] = link[v].from;
      rematch(mate[t], t);
    } else {
      int x = link[v].from, y = link[v].to;
      rematch(x, y); rematch(y, x);
    }
  }

  void fix_mate_and_base(int b) {
    if (b <= N) return;
    int bv = base[b], mv = node[bv].link[0].v, bmv = node[bv].link[0].b;
    int d = (node[bmv].link[1].v == mate[mv]) ? 0 : 1;
    while (1) {
      int mv = node[bv].link[d].v, bmv = node[bv].link[d].b;
      if (node[bmv].link[1 ^ d].v != mate[mv]) break;
      fix_mate_and_base(bv); fix_mate_and_base(bmv);
      bv = node[bmv].link[d].b;
    }
    fix_mate_and_base(base[b] = bv);
    mate[b] = mate[bv];
  }

  void reset_time() {
    time_current_ = 0; event1 = {Inf, 0};
  }

  void reset_blossom(int b) {
    label[b] = kFree; link[b].from = 0; slack[b] = Inf; lazy[b] = 0;
  }

  void reset_all() {
    label[0] = kFree; link[0].from = 0;
    for (int v = 1; v <= N; ++v) { // should be optimized for sparse graphs.
      if (label[v] == kOuter) potential[v] -= time_current_;
      else {
        int bv = surface[v];
        potential[v] += lazy[bv];
        if (label[bv] == kInner) potential[v] += time_current_ - time_created[bv];
      }
      reset_blossom(v);
    }
    for (int b = N + 1, r = B - unused_bid_idx_; r > 0 && b < S; ++b) if (base[b] != b) {
        if (surface[b] == b) {
          fix_mate_and_base(b);
          if (label[b] == kOuter) potential[b] += (time_current_ - time_created[b]) << 1;
          else if (label[b] == kInner) fix_blossom_potential<kInner>(b);
          else fix_blossom_potential<kFree>(b);
        }
        heap2s.clear(b);
        reset_blossom(b); --r;
      }

    que.clear();
    reset_time(); heap2.clear();
    heap3.clear(); heap4.clear();
  }

  void do_edmonds_search(int root) {
    if (potential[root] == 0) return;
    link_blossom(surface[root], {0, 0});
    push_outer_and_fix_potentials(surface[root], 0);
    for (bool augmented = false; !augmented; ) {
      augmented = augment(root);
      if (augmented) break;
      augmented = adjust_dual_variables(root);
    }
    reset_all();
  }

  template <Label Lab>
  inline cost_t fix_blossom_potential(int b) {
    // Return the amount.
    // (If v is an atom, the potential[v] will not be changed.)
    cost_t d = lazy[b]; lazy[b] = 0;
    if (Lab == kInner) {
      cost_t dt = time_current_ - time_created[b];
      if (b > N) potential[b] -= dt << 1;
      d += dt;
    }
    return d;
  }

  template <Label Lab>
  inline void update_heap2(int x, int y, int by, cost_t t) {
    if (t >= slack[y]) return;
    slack[y] = t; best_from[y] = x;
    if (y == by) {
      if (Lab != kInner) heap2.decrease_key(y, EdgeEvent(t + lazy[y], x, y));
    } else {
      int gy = group[y];
      if (gy != y) {
        if (t >= slack[gy]) return;
        slack[gy] = t;
      }
      heap2s.decrease_key(by, gy, EdgeEvent(t, x, y));
      if (Lab == kInner) return;
      EdgeEvent m = heap2s.min(by);
      heap2.decrease_key(by, EdgeEvent(m.time + lazy[by], m.from, m.to));
    }
  }

  void activate_heap2_node(int b) {
    if (b <= N) {
      if (slack[b] < Inf) heap2.push(b, EdgeEvent(slack[b] + lazy[b], best_from[b], b));
    } else {
      if (heap2s.empty(b)) return;
      EdgeEvent m = heap2s.min(b);
      heap2.push(b, EdgeEvent(m.time + lazy[b], m.from, m.to));
    }
  }

  void swap_blossom(int a, int b) {
    // Assume that `b` is a maximal blossom.
    swap(base[a], base[b]); if (base[a] == a) base[a] = b;
    swap(heavy[a], heavy[b]); if (heavy[a] == a) heavy[a] = b;
    swap(link[a], link[b]);
    swap(mate[a], mate[b]);
    swap(potential[a], potential[b]); swap(lazy[a], lazy[b]);
    swap(time_created[a], time_created[b]);
    for (int d = 0; d < 2; ++d) node[node[a].link[d].b].link[1 ^ d].b = b;
    swap(node[a], node[b]);
  }

  void set_surface_and_group(int b, int sf, int g) {
    surface[b] = sf, group[b] = g;
    if (b <= N) return;
    for (int bb = base[b]; surface[bb] != sf; bb = node[bb].next_b()) {
      set_surface_and_group(bb, sf, g);
    }
  }

  void merge_smaller_blossoms(int bid) {
    int lb = bid, largest_size = 1;
    for (int beta = base[bid], b = beta; ;) {
      if (node[b].size > largest_size) largest_size = node[b].size, lb = b;
      if ((b = node[b].next_b()) == beta) break;
    }
    for (int beta = base[bid], b = beta; ;) {
      if (b != lb) set_surface_and_group(b, lb, b);
      if ((b = node[b].next_b()) == beta) break;
    }
    group[lb] = lb;
    if (largest_size > 1) {
      surface[bid] = heavy[bid] = lb;
      swap_blossom(lb, bid);
    } else heavy[bid] = 0;
  }

  void contract(int x, int y, int eid) {
    int bx = surface[x], by = surface[y]; assert(bx != by);
    const int h = -(eid + 1);
    link[surface[mate[bx]]].from = link[surface[mate[by]]].from = h;

    int lca = -1;
    while (1) {
      if (mate[by] != 0) swap(bx, by);
      bx = lca = surface[link[bx].from];
      if (link[surface[mate[bx]]].from == h) break;
      link[surface[mate[bx]]].from = h;
    }

    const int bid = unused_bid[--unused_bid_idx_]; assert(unused_bid_idx_ >= 0);
    int tree_size = 0;
    for (int d = 0; d < 2; ++d) {
      for (int bv = surface[x]; bv != lca; ) {
        int mv = mate[bv], bmv = surface[mv], v = mate[mv];
        int f = link[v].from, t = link[v].to;
        tree_size += node[bv].size + node[bmv].size;
        link[mv] = {x, y};

        if (bv > N) potential[bv] += (time_current_ - time_created[bv]) << 1;
        if (bmv > N) heap4.erase(bmv);
        push_outer_and_fix_potentials(bmv, fix_blossom_potential<kInner>(bmv));

        node[bv].link[d] = {bmv, mv};
        node[bmv].link[1 ^ d] = {bv, v}; node[bmv].link[d] = {bv = surface[f], f};
        node[bv].link[1 ^ d] = {bmv, t};
      }
      node[surface[x]].link[1 ^ d] = {surface[y], y};
      swap(x, y);
    }
    if (lca > N) potential[lca] += (time_current_ - time_created[lca]) << 1;
    node[bid].size = tree_size + node[lca].size;
    base[bid] = lca; link[bid] = link[lca]; mate[bid] = mate[lca];
    label[bid] = kOuter;
    surface[bid] = bid; time_created[bid] = time_current_;
    potential[bid] = 0; lazy[bid] = 0;

    merge_smaller_blossoms(bid); // O(n log n) time / Edmonds search
  }

  void link_blossom(int v, Link l) {
    link[v] = {l.from, l.to};
    if (v <= N) return;
    int b = base[v]; link_blossom(b, l);
    int pb = node[b].prev_b();
    l = {node[pb].next_v(), node[b].prev_v()};
    for (int bv = b; ; ) {
      int bw = node[bv].next_b();
      if (bw == b) break;
      link_blossom(bw, l);
      Link nl = {node[bw].prev_v(), node[bv].next_v()};
      bv = node[bw].next_b();
      link_blossom(bv, nl);
    }
  }

  void push_outer_and_fix_potentials(int v, cost_t d) {
    label[v] = kOuter;
    if (v > N) {
      for (int b = base[v]; label[b] != kOuter; b = node[b].next_b()) {
        push_outer_and_fix_potentials(b, d);
      }
    } else {
      potential[v] += time_current_ + d;
      if (potential[v] < event1.time) event1 = {potential[v], v};
      que.enqueue(v);
    }
  }

  bool grow(int x, int y) {
    int by = surface[y];
    bool visited = (label[by] != kFree);
    if (!visited) link_blossom(by, {0, 0});
    label[by] = kInner; time_created[by] = time_current_; heap2.erase(by);
    if (y != by) heap4.update(by, time_current_ + (potential[by] >> 1));
    int z = mate[by];
    if (z == 0) {
      rematch(x, y); rematch(y, x);
      return true;
    }
    int bz = surface[z];
    if (!visited) link_blossom(bz, {x, y});
    else link[bz] = link[z] = {x, y};
    push_outer_and_fix_potentials(bz, fix_blossom_potential<kFree>(bz));
    time_created[bz] = time_current_; heap2.erase(bz);
    return false;
  }

  void free_blossom(int bid) {
    unused_bid[unused_bid_idx_++] = bid;
    base[bid] = bid;
  }

  int recalculate_minimum_slack(int b, int g) {
    // Return the destination of the best edge of blossom `g`.
    if (b <= N) {
      if (slack[b] >= slack[g]) return 0;
      slack[g] = slack[b]; best_from[g] = best_from[b];
      return b;
    }
    int v = 0;
    for (int beta = base[b], bb = beta; ; ) {
      int w = recalculate_minimum_slack(bb, g);
      if (w != 0) v = w;
      if ((bb = node[bb].next_b()) == beta) break;
    }
    return v;
  }

  void construct_smaller_components(int b, int sf, int g) {
    surface[b] = sf, group[b] = g; // `group[b] = g` is unneeded.
    if (b <= N) return;
    for (int bb = base[b]; surface[bb] != sf; bb = node[bb].next_b()) {
      if (bb == heavy[b]) {
        construct_smaller_components(bb, sf, g);
      } else {
        set_surface_and_group(bb, sf, bb);
        int to = 0;
        if (bb > N) slack[bb] = Inf, to = recalculate_minimum_slack(bb, bb);
        else if (slack[bb] < Inf) to = bb;
        if (to > 0) heap2s.push(sf, bb, EdgeEvent(slack[bb], best_from[bb], to));
      }
    }
  }

  void move_to_largest_blossom(int bid) {
    const int h = heavy[bid];
    cost_t d = (time_current_ - time_created[bid]) + lazy[bid]; lazy[bid] = 0;
    for (int beta = base[bid], b = beta; ;) {
      time_created[b] = time_current_;
      lazy[b] = d;
      if (b != h) construct_smaller_components(b, b, b), heap2s.erase(bid, b);
      if ((b = node[b].next_b()) == beta) break;
    }
    if (h > 0) swap_blossom(h, bid), bid = h;
    free_blossom(bid);
  }

  void expand(int bid) {
    int mv = mate[base[bid]];
    move_to_largest_blossom(bid); // O(n log n) time / Edmonds search
    Link old_link = link[mv];
    int old_base = surface[mate[mv]], root = surface[old_link.to];
    int d = (mate[root] == node[root].link[0].v) ? 1 : 0;
    for (int b = node[old_base].link[d ^ 1].b; b != root; ) {
      label[b] = kSeparated; activate_heap2_node(b); b = node[b].link[d ^ 1].b;
      label[b] = kSeparated; activate_heap2_node(b); b = node[b].link[d ^ 1].b;
    }
    for (int b = old_base; ; b = node[b].link[d].b) {
      label[b] = kInner;
      int nb = node[b].link[d].b;
      if (b == root) link[mate[b]] = old_link;
      else link[mate[b]] = {node[b].link[d].v, node[nb].link[d ^ 1].v};
      link[surface[mate[b]]] = link[mate[b]]; // fix tree links
      if (b > N) {
        if (potential[b] == 0) expand(b);
        else heap4.push(b, time_current_ + (potential[b] >> 1));
      }
      if (b == root) break;
      push_outer_and_fix_potentials(nb, fix_blossom_potential<kInner>(b = nb));
    }
  }

  bool augment(int root) {
    // Return true if an augmenting path is found.
    while (!que.empty()) {
      int x = que.dequeue(), bx = surface[x];
      if (potential[x] == time_current_) {
        if (x != root) rematch(x, 0);
        return true;
      }
      for (int eid = ofs[x]; eid < ofs[x + 1]; ++eid) {
        auto& e = edges[eid]; int y = e.to, by = surface[y];
        if (bx == by) continue;
        Label l = label[by];
        if (l == kOuter) {
          cost_t t = reduced_cost(x, y, e) >> 1; // < 2 * Inf
          if (t == time_current_) {
            contract(x, y, eid); bx = surface[x];
          } else if (t < event1.time) {
            heap3.emplace(t, x, eid);
          }
        } else {
          tcost_t t = reduced_cost(x, y, e); // < 3 * Inf
          if (t >= Inf) continue;
          if (l != kInner) {
            if (cost_t(t) + lazy[by] == time_current_) {
              if (grow(x, y)) return true;
            } else update_heap2<kFree>(x, y, by, t);
          } else {
            if (mate[x] != y) update_heap2<kInner>(x, y, by, t);
          }
        }
      }
    }
    return false;
  }

  bool adjust_dual_variables(int root) {
    // delta1 : rematch
    cost_t time1 = event1.time;

    // delta2 : grow
    cost_t time2 = Inf;
    if (!heap2.empty()) time2 = heap2.min().time;

    // delta3 : contract : O(m log n) time / Edmonds search [ bottleneck (?) ]
    cost_t time3 = Inf;
    while (!heap3.empty()) {
      EdgeEvent e = heap3.min();
      int x = e.from, y = edges[e.to].to; // e.to is some edge id.
      if (surface[x] != surface[y]) {
        time3 = e.time;
        break;
      } else heap3.pop();
    }

    // delta4 : expand
    cost_t time4 = Inf;
    if (!heap4.empty()) time4 = heap4.min();

    // -- events --
    cost_t time_next = min(min(time1, time2), min(time3, time4));
    assert(time_current_ <= time_next && time_next < Inf);
    time_current_ = time_next;

    if (time_current_ == event1.time) {
      int x = event1.id;
      if (x != root) rematch(x, 0);
      return true;
    }
    while (!heap2.empty() && heap2.min().time == time_current_) {
      int x = heap2.min().from, y = heap2.min().to;
      if (grow(x, y)) return true; // `grow` function will call `heap2.erase(by)`.
    }
    while (!heap3.empty() && heap3.min().time == time_current_) {
      int x = heap3.min().from, eid = heap3.min().to;
      int y = edges[eid].to; heap3.pop();
      if (surface[x] == surface[y]) continue;
      contract(x, y, eid);
    }
    while (!heap4.empty() && heap4.min() == time_current_) {
      int b = heap4.argmin(); heap4.pop();
      expand(b);
    }
    return false;
  }

  void initialize() {
    que = Queue<int>(N);
    mate.assign(S, 0);
    link.assign(S, {0, 0});
    label.assign(S, kFree);
    base.resize(S); for (int u = 1; u < S; ++u) base[u] = u;
    surface.resize(S); for (int u = 1; u < S; ++u) surface[u] = u;

    potential.resize(S);
    node.resize(S); for (int b = 1; b < S; ++b) node[b] = Node(b);

    unused_bid.resize(B); for (int i = 0; i < B; ++i) unused_bid[i] = N + B - i;
    unused_bid_idx_ = B;

    // for O(nm log n) implementation
    reset_time();
    time_created.resize(S);
    slack.resize(S); for (int i = 0; i < S; ++i) slack[i] = Inf;
    best_from.assign(S, 0);
    heavy.assign(S, 0);
    lazy.assign(S, 0);
    group.resize(S); for (int i = 0; i < S; ++i) group[i] = i;
  }

  void set_potential() {
    for (int u = 1; u <= N; ++u) {
      cost_t max_c = 0;
      for (int eid = ofs[u]; eid < ofs[u + 1]; ++eid) {
        max_c = max(max_c, edges[eid].cost);
      }
      potential[u] = max_c >> 1;
    }
  }

  void find_maximal_matching() {
    // Find a maximal matching naively.
    for (int u = 1; u <= N; ++u) if (!mate[u]) {
        for (int eid = ofs[u]; eid < ofs[u + 1]; ++eid) {
          auto& e = edges[eid]; int v = e.to;
          if (mate[v] > 0 || reduced_cost(u, v, e) > 0) continue;
          mate[u] = v; mate[v] = u;
          break;
        }
      }
  }

  const int N, B, S; // N = |V|, B = (|V| - 1) / 2, S = N + B + 1
  vector<int> ofs;
  vector<Edge> edges;

  Queue<int> que;
  vector<int> mate, surface, base;
  vector<Link> link;
  vector<Label> label;
  vector<cost_t> potential;

  vector<int> unused_bid; int unused_bid_idx_;
  vector<Node> node;

  // for O(nm log n) implementation
  vector<int> heavy, group;
  vector<cost_t> time_created, lazy, slack;
  vector<int> best_from;

  cost_t time_current_;
  Event event1;
  ModifiableHeap<EdgeEvent> heap2;
  ModifiableHeaps<EdgeEvent> heap2s;
  FastHeap<EdgeEvent> heap3;
  ModifiableHeap<cost_t> heap4;
};

using MWM = MaximumWeightedMatching<int>;
using Edge = MWM::InputEdge;



namespace dbl_utils {
  typedef double dbl;

  const dbl EPS = 1e-9;

  bool eq(dbl a, dbl b) {
    return fabs(a - b) < EPS;
  }

  bool ne(dbl a, dbl b) {
    return !eq(a, b);
  }

  bool lt(dbl a, dbl b) {
    return a < b && !eq(a, b);
  }

  bool le(dbl a, dbl b) {
    return !lt(b, a);
  }

  bool ge(dbl a, dbl b) {
    return !lt(b, a);
  }

  bool gt(dbl a, dbl b) {
    return lt(b, a);
  }

  int sign(dbl x) {
    if (eq(x, 0)) return 0;
    if (x > 0) return 1;
    return -1;
  }
}
using namespace dbl_utils;

template <typename T>
struct _pt {
  T x, y;

  _pt<T>() {}
  _pt<T>(T _x, T _y) : x(_x), y(_y) {}

  _pt<T> operator+ (const _pt<T> &p) const {
    return _pt<T>(x + p.x, y + p.y);
  }

  _pt<T>& operator+= (const _pt<T> &p) {
    return *this = *this + p;
  }

  _pt<T> operator- (const _pt<T> &p) const {
    return _pt<T>(x - p.x, y - p.y);
  }

  _pt<T>& operator-= (const _pt<T> &p) {
    return *this = *this - p;
  }

  _pt<T> operator* (T d) const {
    return _pt<T>(x * d, y * d);
  }

  _pt<T>& operator*= (T d) {
    return *this = *this * d;
  }

  T operator* (const _pt<T> &p) const {
    return x * p.y - y * p.x;
  }

  T operator% (const _pt<T> &p) const {
    return x * p.x + y * p.y;
  }

  T d2() const {
    return *this % *this;
  }

  dbl d() const {
    return sqrt((dbl)d2());
  }

  dbl ang() const {
    return atan2((dbl)y, (dbl)x);
  }

  _pt<T> rotate90() const {
    return _pt<T>(-y, x);
  }

  _pt<T> rotate(dbl ang) {
    return _pt<T>(x * cos(ang) - y * sin(ang),
                  x * sin(ang) + y * cos(ang));
  }

  int turn(const _pt<T> &p) const {
    return sign((*this) * p);
  }

  int up() const {
    if (y > 0 || (y == 0 && x > 0)) return 1;
    if (y < 0 || (y == 0 && x < 0)) return -1;
    return 0;
  }

  bool operator< (const _pt<T> &p) const {
    if (up() != p.up()) return up() > p.up();
    return *this * p > 0;
  }

  bool operator== (const _pt<T> &p) const {
    return eq(x, p.x) && eq(y, p.y);
  }

  void read() {
    cin >> x >> y;
  }
};
typedef _pt<long long> pt;

struct edge {
  int u, v;
  int cost;
  int id;

  int go(int from) {
    return from ^ u ^ v;
  }
};

void print(pair<int, vector<int>> o) {
  cout << o.first << endl;
  for (int x : o.second) cout << x << " ";
  cout << endl;
}

const int INF = (1 << 30) - 1;

pair<int, vector<int>> subsolve(vector<pt> a, vector<edge> ed) {
  int n = a.size();
  int m = ed.size();

  vector<vector<pair<int, int>>> e(n);
  for (int i = 0; i < m; i++) {
    e[ed[i].u].push_back({ed[i].v, i});
    e[ed[i].v].push_back({ed[i].u, i});
  }

  map<pair<int, int>, pair<int, int>> nxt;
  map<pair<int, int>, int> eid;
  for (int i = 0; i < n; i++) {
    sort(e[i].begin(), e[i].end(), [&](pair<int, int> x, pair<int, int> y) {
      return a[x.first] - a[i] < a[y.first] - a[i];
    });
    for (int j = 0; j < (int)e[i].size(); j++) {
      int y = i;
      int x = e[i][j].first;
      int z = e[i][(j + 1) % e[i].size()].first;

      nxt[{x, y}] = {y, z};
      eid[{x, y}] = e[i][j].second;

    }
  }

  map<pair<int, int>, int> face;

  vector<vector<pair<int, int>>> faces;

  auto go = [&](int x, int y) {
    if (face.count({x, y})) return;

    int cur = faces.size();
    faces.push_back({});
    int ox = x, oy = y;
    while (1) {
      faces.back().push_back({x, y});
      face[{x, y}] = cur;
      auto o = nxt[{x, y}];
      x = o.first;
      y = o.second;
      if (x == ox && y == oy) break;
    }
  };
  for (int i = 0; i < n; i++) {
    for (auto o : e[i]) {
      go(i, o.first);
    }
  }

  map<pair<int, int>, int> common;
  for (int i = 0; i < n; i++) {
    for (auto o : e[i]) {
      int x = o.first;
      int y = i;

      int f1 = face[{x, y}];
      int f2 = face[{y, x}];
      if (!common.count({f1, f2}) || ed[common[{f1, f2}]].cost > ed[o.second].cost) {
        common[{f1, f2}] = o.second;
      }
      //common[make_pair(face[{x, y}], face[{y, x}])] = o.second;
    }
  }

  int k = faces.size();
  vector<vector<int>> g(k, vector<int>(k, INF));
  for (int i = 0; i < k; i++) g[i][i] = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < (int)e[i].size(); j++) {
      int x = i, y = e[i][j].first;
      int f1 = face[{x, y}];
      int f2 = face[{y, x}];
      g[f1][f2] = min(g[f1][f2], ed[e[i][j].second].cost);
      g[f2][f1] = min(g[f1][f2], ed[e[i][j].second].cost);
    }
  }
  vector<vector<int>> pr(k, vector<int>(k, -1));
  for (int z = 0; z < k; z++) {
    for (int i = 0; i < k; i++) {
      for (int j = 0; j < k; j++) {
        //g[i][j] = min(g[i][j], g[i][z] + g[z][j]);
        if (g[i][j] > g[i][z] + g[z][j]) {
          pr[i][j] = z;
          g[i][j] = g[i][z] + g[z][j];
        }
      }
    }
  }
  for (int i = 0; i < k; i++) {
  }

  int odd = 0;
  vector<int> vodd;
  for (int i = 0; i < k; i++) {
    odd += faces[i].size() % 2;
    if (faces[i].size() % 2) {
      vodd.push_back(i);
    }
  }
//  db(odd);


  auto run = [] (int N, const vector<Edge>& edges) {
    //clock_t beg = clock();
    auto mwm = MWM(N, edges);
    auto ans = mwm.maximum_weighted_matching();

    vector<pair<int, int>> res;
    for (int i = 1; i <= N; i++) {
      if (mwm.mate[i] > i) {
        res.push_back({i - 1, mwm.mate[i] - 1});
      }
    }
    //clock_t end = clock();
    //fprintf(stderr, "|V| = %6d, |E| = %7d: %lld %.3f sec\n", N, (int) edges.size(), (ll)ans, double(end - beg) / CLOCKS_PER_SEC);
    return make_pair(ans, res);
  };

  vector<Edge> edges;
  for (int i = 0; i < odd; i++) {
    for (int j = 0; j < odd; j++) if (i < j) {
      edges.push_back({i + 1, j + 1, INF - g[vodd[i]][vodd[j]]});
    }
  }

  pair<int, vector<int>> res;
  auto o = run(odd, edges);
  res.first += o.first - (odd / 2 * INF);

  function<void(int, int)> rec = [&](int u, int v) {
    if (pr[u][v] == -1) {
      res.second.push_back(ed[common[{u, v}]].id);
    } else {
      rec(u, pr[u][v]);
      rec(pr[u][v], v);
    }
  };
  for (auto oo : o.second) {
    rec(vodd[oo.first], vodd[oo.second]);
  }

  return res;
}

pair<int, vector<int>> solve(vector<pt> a, vector<edge> ed) {
  int n = a.size();
  int m = ed.size();

  vector<vector<int>> e(n);
  for (int i = 0; i < m; i++) {
    e[ed[i].u].push_back(i);
    e[ed[i].v].push_back(i);
  }

  pair<int, vector<int>> ans = make_pair(0, vector<int>(m, 1));
  for (auto o : ed) ans.first += o.cost;
  vector<char> vis(n);
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;

    vector<int> eid;
    vector<int> q;
    q.push_back(i);
    for (int qq = 0; qq < n; qq++) {
      int v = q[qq];
      for (int id : e[v]) {
        eid.push_back(id);
        int to = ed[id].go(v);
        if (!vis[to]) {
          vis[to] = 1;
          q.push_back(to);
        }
      }
    }
    sort(q.begin(), q.end());
    sort(eid.begin(), eid.end());
    eid.resize(unique(eid.begin(), eid.end()) - eid.begin());
    vector<edge> ned;
    for (auto id : eid) {
      auto cur = ed[id];
      cur.u = lower_bound(q.begin(), q.end(), cur.u) - q.begin();
      cur.v = lower_bound(q.begin(), q.end(), cur.v) - q.begin();
      ned.push_back(cur);
    }
    vector<pt> na;
    for (int id : q) na.push_back(a[id]);

    auto o = subsolve(na, ned);
    ans.first += o.first;
    for (int id : o.second) {
      ans.second[id] = 0;
    }
  }
//db(ans.first);
  //return ans;
  {
    vector<vector<int>> e0(n, vector<int>(n));
    for (int i = 0; i < m; i++ ){
      if (ans.second[i]) {
        e0[ed[i].u][ed[i].v] = 1;
        e0[ed[i].v][ed[i].u] = 1;
      }
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
      if (ans.second[i]) {
        g[ed[i].u].push_back(ed[i].v);
        g[ed[i].v].push_back(ed[i].u);
      }
    }
    /*for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (!e0[i][j]) {
          g[i].push_back(j);
        }
      }
    }*/
    vector<int> col(n, -1);
    function<void(int, int)> dfs = [&](int v, int c) {
      if (col[v] != -1) {
        //assert(col[v] == c);
        return;
      }
      col[v] = c;
      for (int to : g[v]) {
        dfs(to, c ^ 1);
      }
    };
    for (int i = 0; i < n; i++) {
      if (col[i] == -1) {
        dfs(i, 0);
      }
    }
    ans.second = col;
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  //freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<pt> a(n);
    for (int i = 0; i < n; i++ ){
      scanf("%lld%lld", &a[i].x, &a[i].y);
    }
    vector<edge> ed;
    for (int i = 0; i < m; i++) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      u--; v--;
      ed.push_back({u, v, c, i});
    }

    print(solve(a, ed));
  }

  return 0;
}
