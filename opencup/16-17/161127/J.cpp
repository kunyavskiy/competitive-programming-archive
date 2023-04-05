#include <cstdio>
#include <vector>
#include <algorithm>
#include <string>
#include <cassert>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "J"

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
typedef std::pair<int,int> pii;

const ll INF = ll(3e9) + 100;

int getK(const vector <int> & v0, int L0, int R0,
         const vector <int> & v1, int L1, int R1) {
  int k = 0;
  while (L0 <= R0) {
    while (L1 <= R1 && v0[L0] > v1[L1]) {
      ++L1;
    }
    if (L1 <= R1) {
      ++k;
      ++L0, ++L1;
    } else {
      break;
    }
  }
  return k;
}


struct Ticket {
  int u, v;
  ll price[4];
  vector <int> seq;
  vector <int> pos[2];

  Ticket(int u, int v) : u(u), v(v) {
    for (int i = 0; i < 4; ++i) {
      price[i] = INF;
    }
  }

  void addSeq(int x) {
    pos[x].push_back(int(seq.size()));
    seq.push_back(x);
  }

  ll solve() {
    eprintf("u %d v %d | %lld %lld %lld %lld\n", u, v, price[0], price[1], price[2], price[3]);
    price[0] = min(price[0], price[2]);
    price[1] = min(price[1], price[3]);
    ll res0 = price[0] * ll(pos[0].size()) + price[1] * ll(pos[1].size());
    price[2] -= (price[0] + price[1]);
    price[3] -= (price[0] + price[1]);

    if (price[0] != INF && price[1] != INF) {
      price[2] = min(0LL, price[2]);
      price[3] = min(0LL, price[3]);
    }

    //eprintf("%lld %lld %lld %lld\n", price[0], price[1], price[2], price[3]);

    ll P[2] = {price[2], price[3]};

    ll res = 0;
    for (int ii = 0; ii < 2; ii++) {
      int i0 = ii;
      int i1 = ii^1;
      int L[2], R[2];
      for (int i = 0; i < 2; ++i) {
        L[i] = 0;
        R[i] = int(pos[i].size()) - 1;
      }
      int cnt0 = getK(pos[i0], L[i0], R[i0], pos[i1], L[i1], R[i1]);
      L[i0] += cnt0;
      R[i1] -= cnt0;
      int cnt1 = getK(pos[i1], L[i1], R[i1], pos[i0], L[i0], R[i0]);

      ll cur = cnt0 * P[i0] + cnt1 * P[i1];
      //eprintf("cnt2 %d cnt3 %d cur %lld\n", cnt0, cnt1, cur);

      res = min(res, cur);
    }
    eprintf("[");
    for (int i = 0; i < int(seq.size()); ++i) {
      eprintf("%d ", seq[i]);
    }
    eprintf("] = %lld\n", res0 + res);
    return res0 + res;
  }
};

vector <pii> z;
vector <Ticket> tickets;

void addTicket(int u, int v, char ch, int w) {
  bool rev = false;
  if (u > v) {
    swap(u, v);
    rev = true;
  }
  int num = lower_bound(z.begin(), z.end(), pii(u, v)) - z.begin();

  assert(ch == 'O' || ch == 'R');
  int priceNum = (rev ? 1 : 0) + (ch == 'R' ? 2 : 0);
  eprintf("u %d v %d rev %d ch %c w %d -> priceNum %d\n", u, v, rev ? 1 : 0, ch, w, priceNum);
  tickets[num].price[priceNum] = min(tickets[num].price[priceNum], (ll)w);
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n, d;
  scanf("%d%d", &n, &d);
  vector <int> a(d);
  for (int i = 0; i < d; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 1; i < d; ++i) {
    pii cur(a[i - 1], a[i]);
    if (cur.first > cur.second) {
      swap(cur.first, cur.second);
    }
    z.push_back(cur);
  }
  sort(z.begin(), z.end());
  z.erase(unique(z.begin(), z.end()), z.end());
  for (int i = 0; i < int(z.size()); ++i) {
    tickets.push_back(Ticket(z[i].first, z[i].second));
  }

  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; ++i) {
    char ch;
    int u, v, w;
    scanf("%d%d %c%d", &u, &v, &ch, &w);
    addTicket(u, v, ch, w);
  }

  for (int i = 1; i < d; ++i) {
    bool rev = false;
    pii cur(a[i - 1], a[i]);
    if (cur.first > cur.second) {
      swap(cur.first, cur.second);
      rev = true;
    }
    int num = lower_bound(z.begin(), z.end(), cur) - z.begin();
    tickets[num].addSeq(rev ? 1 : 0);
  }

  ll res = 0;
  for (int i = 0; i < int(tickets.size()); ++i) {
    res += tickets[i].solve();
  }
  printf("%lld\n", res);

  return 0;
}
