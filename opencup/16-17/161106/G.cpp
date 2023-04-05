#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "G"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;
typedef list<int> li;
typedef li::iterator liit;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

struct Tree {
  vector<pair<int, liit>> pars;
  vector<li> chi;

  Tree(int n) : pars(n, mp(-1, liit())), chi(n) {
  }

  Tree(const Tree &other) = delete;
  Tree& operator=(const Tree &other) = delete;

  void add(int a, int b) {
    assert(0 <= a && a < sz(pars));
    assert(0 <= b && b < sz(pars));
    assert(pars[b].first < 0);
    pars[b].first = a;
    chi[a].push_front(b);
    pars[b].second = chi[a].begin();
  }

  void remove(int a, int b) {
    assert(0 <= a && a < sz(pars));
    assert(0 <= b && b < sz(pars));
    assert(pars[b].first == a);
    assert(*pars[b].second == b);
    chi[a].erase(pars[b].second);
    pars[b].first = -1;
    pars[b].second = liit();
  }

  int get_root(int a) {
    while (pars[a].first >= 0)
      a = pars[a].first;
    return a;
  }
};

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n;
  while (scanf("%d", &n) == 1) {
    Tree cur_tree(n), prev_tree(n);

    vi ids(n);
    map<int, int> id2num;
    vvi chiid(n);
    forn (i, n) {
      int k;
      scanf("%d%d", &ids[i], &k);
      assert(!id2num.count(ids[i]));
      id2num[ids[i]] = i;
      chiid[i].resize(k);
      for (int &x : chiid[i])
        scanf("%d", &x);
    }

    forn (i, n)
      for (int id : chiid[i]) {
        cur_tree.add(i, id2num[id]);
        prev_tree.add(i, id2num[id]);
      }

    vector<pair<int, pii>> ops;
    int root = cur_tree.get_root(0);
    vb marked(n);
    vi mlist;
    vi probably_added;
    vi printed(n);
    int pver = 1;

    const function<void(int)> mark_prev_subtr = [&](int v) {
      if (marked[v]) {
        return;
      }
      //eprintf("  mark_prev(%d)\n", ids[v]);
      mlist.pb(v);
      marked[v] = true;
      for (int c : prev_tree.chi[v]) {
        mark_prev_subtr(c);
      }
    };
    const function<bool(int)> in_prev_root = [&](int v) {
      return prev_tree.get_root(v) == root;
    };
    const function<bool(int)> in_cur_root = [&](int v) {
      return cur_tree.get_root(v) == root;
    };

    int qcnt;
    scanf("%d", &qcnt);
    while (qcnt --> 0) {
      char opstr[10];
      scanf("%s", opstr);
      //eprintf("opstr=%s\n", opstr);
      if (opstr[0] == 'a') { // add
        int a, b;
        scanf("%d%d", &a, &b);
        a = id2num.at(a);
        b = id2num.at(b);
        cur_tree.add(a, b);
        ops.pb(mp(1, mp(a, b)));
        if (in_prev_root(b)) {
          mark_prev_subtr(b);
        }
        probably_added.pb(b);
      } else if (opstr[0] == 'm') { // modify
        int a;
        scanf("%d", &a);
        a = id2num.at(a);
        if (in_prev_root(a)) {
          mark_prev_subtr(a);
        }
      } else if (opstr[2] == 'm') { // remove
        int a, b;
        scanf("%d%d", &a, &b);
        a = id2num.at(a);
        b = id2num.at(b);
        cur_tree.remove(a, b);
        ops.pb(mp(-1, mp(a, b)));
        if (in_prev_root(b)) {
          mark_prev_subtr(b);
        }
      } else if (opstr[2] == 'n') { // render
        vi added, removed, modified;

        pver++;
        const function<void(int)> dfs_prev = [&](int v) {
          assert(marked[v]);
          if (printed[v] >= pver) {
            return;
          }
          printed[v] = pver;
          //eprintf("  dfs_prev(%d)\n", ids[v]);
          if (in_cur_root(v)) {
            modified.pb(v);
          } else {
            removed.pb(v);
          }
          for (int c : prev_tree.chi[v]) {
            dfs_prev(c);
          }
        };
        for (int x : mlist) {
          dfs_prev(x);
        }

        pver++;
        const function<void(int)> dfs_cur = [&](int v) {
          if (printed[v] >= pver) {
            return;
          }
          //eprintf("  dfs_cur(%d)\n", ids[v]);
          if (printed[v] < pver - 1) {
            added.pb(v);
          }
          printed[v] = pver;
          for (int c : cur_tree.chi[v]) {
            dfs_cur(c);
          }
        };
        for (int x : probably_added) {
          if (in_cur_root(x)) {
            dfs_cur(x);
          }
        }

        #define print(a) do { \
          for (int &num : a) { \
            num = ids.at(num); \
          } \
          sort(a.begin(), a.end()); \
          printf(#a " %d", sz(a)); \
          for (int id : a) printf(" %d", id); \
          printf("\n"); \
        } while (0)
        print(added);
        print(removed);
        print(modified);
        #undef print_arr

        for (auto op : ops) {
          int a, b;
          tie(a, b) = op.second;
          if (op.first > 0) prev_tree.add(a, b);
          else prev_tree.remove(a, b);
        }
        ops.clear();
        for (int x : mlist)
          marked[x] = false;
        mlist.clear();
        probably_added.clear();
      }
    }
    #ifdef DEBUG
    printf("\n");
    #endif
  }

  return 0;
}
