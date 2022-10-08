#include "message.h"
#include "kenneth.h"

#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

struct HV {
  int f, s;

  bool operator<(const HV &rhs) const {
    if (f != rhs.f)
      return f < rhs.f;
    return s < rhs.s;
  }

  bool operator==(const HV &x) const {
    return f == x.f && s == x.s;
  }
};

HV operator+(const HV &a, const HV &b) {
  return {(a.f + b.f) % MOD1, (a.s + b.s) % MOD2};
}

HV operator-(const HV &a, const HV &b) {
  return {(a.f - b.f + MOD1) % MOD1, (a.s - b.s + MOD2) % MOD2};
}

HV operator*(const HV &a, const HV &b) {
  return {(int) ((a.f * 1LL * b.f) % MOD1), (int) ((a.s * 1LL * b.s) % MOD2)};
}

HV bin_pow(HV a, int p) {
  HV r{1, 1};
  while (p) {
    if (p & 1) r = r * a;
    a = a * a;
    p >>= 1;
  }
  return r;
}

struct query {
  int qid;
  int pos;
  int deg;
};

int main() {
  int nodes = NumberOfNodes();
  int id = MyNodeId();

  int tot_len = 0;
  int lf, rg;
  lf = rg = -1;

  for (int i = 0; i < nodes; i++) {
    if (i == id) lf = tot_len;
    tot_len += GetPieceLength(i);
    if (i == id) rg = tot_len;
  }

  vector<int> divs;
  for (int i = 1; i * i <= tot_len; i++) {
    if (tot_len % i == 0) {
      divs.push_back(i);
      if (tot_len / i != i) {
        divs.push_back(tot_len / i);
      }
    }
  }
  sort(divs.begin(), divs.end());

  HV P{23917, 17239};
  vector<HV> prefix_res(divs.size());
  vector<HV> suffix_res(divs.size());

  {
    vector<query> prefix;
    for (int i = 0; i < (int) divs.size(); i++) {
      int prg = tot_len - divs[i] - 1;
      if (prg >= rg) {
        prefix.push_back({i, rg - 1, lf});
      } else if (prg >= lf) {
        prefix.push_back({i, prg, lf});
      }
    }

    sort(prefix.begin(), prefix.end(), [](const query &a, const query &b) { return a.pos < b.pos; });
    int ptr = 0;


    HV cur = {0, 0};
    HV curd = {1, 1};
    for (int i = lf; i < rg; i++) {
      int c = GetSignalCharacter(i);
      cur = cur + curd * HV{c, c};
      curd = curd * P;
      while (ptr < prefix.size() && prefix[ptr].pos == i) {
        prefix_res[prefix[ptr].qid] = cur * bin_pow(P, prefix[ptr].deg);
        ptr++;
      }
    }
  }

  {
    vector<query> suffix;
    for (int i = 0; i < (int) divs.size(); i++) {
      int plf = divs[i];
      if (plf <= lf) {
        suffix.push_back({i, lf, lf - plf});
      } else if (plf < rg) {
        suffix.push_back({i, plf, 0});
      }
    }

    sort(suffix.begin(), suffix.end(), [](const query &a, const query &b) { return a.pos > b.pos; });

    HV cur = {0, 0};
    int ptr = 0;
    for (int i = rg - 1; i >= lf; i--) {
      int c = GetSignalCharacter(i);
      cur = cur * P + HV{c, c};
      while (ptr < suffix.size() && suffix[ptr].pos == i) {
        suffix_res[suffix[ptr].qid] = cur * bin_pow(P, suffix[ptr].deg);
        ptr++;
      }
    }
  }

  if (id != 0) {
    for (auto x : prefix_res) {
      PutInt(0, x.f);
      PutInt(0, x.s);
    }
    for (auto x : suffix_res) {
      PutInt(0, x.f);
      PutInt(0, x.s);
    }
    Send(0);
    return 0;
  }

  for (int i = 1; i < nodes; i++) {
    Receive(i);
    for (auto &x : prefix_res) {
      HV t;
      t.f = GetInt(i);
      t.s = GetInt(i);
      x = x + t;
    }
    for (auto &x : suffix_res) {
      HV t;
      t.f = GetInt(i);
      t.s = GetInt(i);
      x = x + t;
    }
  }

  for (int i = 0; i < (int)divs.size(); i++) {
//    fprintf(stderr, "(%d, %d) == (%d, %d)?\n", prefix_res[i].f, prefix_res[i].s, suffix_res[i].f, suffix_res[i].s);
    if (prefix_res[i] == suffix_res[i]) {
      printf("%d\n", divs[i]);
      return 0;
    }
  }
  printf("%d\n", tot_len);
}
