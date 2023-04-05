// #define _GLIBCXX_DEBUG


#include <bits/stdc++.h>

using namespace std; 

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int N = 1e5, LEN = 5e6, MAX_MEM = LEN + N;

#define sz(a) (int)(a).size()

typedef long long ll;
typedef unsigned long long ull;

const int P = max(239, rand());
struct num {
  static const int MA = 1e9 + 7, MB = 1e9 + 9;

  int a, b;

  num() { }
  num( int x ) : a(x), b(x) { }
  num( int a, int b ) : a(a), b(b) { }

  num operator + ( const num &x ) const { return num((a + x.a) % MA, (b + x.b) % MB); }
  num operator - ( const num &x ) const { return num((a + MA - x.a) % MA, (b + MB - x.b) % MB); }
  num operator * ( int x ) const { return num(((ll)a * x) % MA, ((ll)b * x) % MB); }
  num operator * ( const num &x ) const { return num(((ll)a * x.a) % MA, ((ll)b * x.b) % MB); }
  bool operator == ( const num &x ) const { return a == x.a && b == x.b; }

  explicit operator ll () const { return (ll)a * MB + b + 1; } // > 0
};

num deg[LEN + 1];

struct Seg {
    int l, r, cnt; // [l, r)
    int f() { return cnt * (r - l); }
    int len() { return r - l; }
};

char mem[MAX_MEM], *s[N];
vector<Seg> v[N];
int n, m, mpos;
vector<int> pref_ma[N], suf_ma[N], sum[N];
vector<vector<num>> pref_hash[N];

void build( int n, const char *s, vector<num> &h ) {
    h.resize(n + 1);
    h[0] = 0;
    forn(i, n)
        h[i + 1] = h[i] * num(P) + num(s[i]);
}

void solve() {
    assert(scanf("%d%d", &n, &m) == 2);
    mpos = 0;
    forn(i, n) {
        s[i] = mem + mpos;
        assert(scanf("%s", s[i]) == 1);
        int len = strlen(s[i]);
        mpos += len + 1;
        int pl = 0, pr = len;
        v[i].clear();
        while (pl < pr) {
            int l = pl, r = l + 1, cnt = 1, l1 = r, r1 = r;
            while (r1 < pr) {
                char c1 = s[i][r1], c2 = s[i][l + (r1 - l1)];
                if (c1 > c2)
                    r = ++r1, l1 = r1;
                else if (c1 == c2) {
                    ++r1;
                    if (r1 - l1 == r - l)
                        cnt++, l1 = r1;
                } else {
                    break;
                }
            }
            v[i].push_back({l, r, cnt});
            pl = l1;
        }
        // printf("i = %d : s = %s\n", i, s[i]);
        // for (auto p : v[i]) {
        //     for (int j = p.l; j < p.r; j++)
        //         printf("%c", s[i][j]);
        //     printf(" : %d\n", p.cnt);
        // }
        int vn = v[i].size();
        pref_ma[i].resize(vn + 1);
        suf_ma[i].resize(vn + 1);
        sum[i].resize(vn + 1);
        sum[i][0] = 0;
        forn(j, vn)
            sum[i][j + 1] = sum[i][j] + v[i][j].f();
        pref_ma[i][0] = 0;
        forn(j, vn)
            pref_ma[i][j + 1] = max(pref_ma[i][j], v[i][j].f());
        suf_ma[i][vn] = 0;
        for (int j = vn - 1; j >= 0; j--)
            suf_ma[i][j] = max(suf_ma[i][j + 1], v[i][j].f());
        while (pref_hash[i].size() < vn)
            pref_hash[i].push_back(vector<num>());
        forn(j, vn)
            build(v[i][j].len(), s[i] + v[i][j].l, pref_hash[i][j]);
    }
    auto greater_hash = [&]( int i, int pi, int j, int pj ) {
        int l = 0, len = min(v[i][pi].len(), v[j][pj].len()), r = len + 1;
        while (r - l > 1) {
            int m = (l + r) / 2;
            if (pref_hash[i][pi][m] == pref_hash[j][pj][m])
                l = m;
            else
                r = m;
        }
        // printf("l = %d\n", l);
        if (l == len)
            return v[i][pi].len() > v[j][pj].len();
        // printf("compare: %c %c\n", s[i][v[i][pi].l + l], s[j][v[j][pj].l + l]);
        return s[i][v[i][pi].l + l] > s[j][v[j][pj].l + l];
    };
    while (m--) {
        int i, j;
        scanf("%d%d", &i, &j), i--, j--;
        int ni = v[i].size(), nj = v[j].size();
        if (!greater_hash(j, 0, i, ni - 1)) {
            // printf("case #1\n");
            printf("%d\n", max(suf_ma[j][0], suf_ma[i][0]));
        } else {
            int l = 0, r = nj;
            // printf("case #2 nj=%d\n", nj);
            while (r - l > 1) {
                int m = (l + r) / 2;
                if (greater_hash(j, m, i, ni - 1))
                    l = m;
                else
                    r = m;
            }
            // printf("l = %d, r = %d [%d, %d + %d, %d]\n", l, r, pref_ma[i][ni - 1], v[i][ni - 1].f() , sum[j][r], suf_ma[j][r]);
            if (ni >= 2) {
                int len = v[i][ni - 1].len(), bigLen = v[i][ni - 2].len();
                if (bigLen >= len && pref_hash[i][ni - 2][len] == pref_hash[i][ni - 1][len] &&
                    greater_substr(j, 0, 0, v[j][0].len(), i, ni - 2, len, bigLen)) {
                    printf("%d\n", max(max(pref_ma[i][ni - 2], v[i][ni - 2].f() + v[i][ni - 1].f() + sum[j][r]), suf_ma[j][r]));
                    continue;

                }
            }
            printf("%d\n", max(max(pref_ma[i][ni - 1], v[i][ni - 1].f() + sum[j][r]), suf_ma[j][r]));
        }
    }
}

int main() {
    deg[0] = 1;
    forn(i, LEN)
        deg[i + 1] = deg[i] * num(P);
    int tn;
    scanf("%d", &tn);
    while (tn--)
        solve();
}
