//#include <iostream>
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
#define mp make_pair
#define pb push_back
#define sz(x) (int)(x).size()

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "G"

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
typedef vector<int> vi;

const int MOD = 40961;
const int ROOT = 3;

int mmul(int a, int b) {
    return (a * b) % MOD;
}
void madd(int& a, int b) {
    if ((a += b) >= MOD) a -= MOD;
}

int mpow(int a, int b){
  if (!b) return 1;
  if (b & 1) return (mpow(a, b-1) * a) % MOD;
  int temp = mpow(a, b/2);
  return (temp * temp) % MOD;
}

bool checkRoot(int x){
  return mpow(x, (MOD - 1) / 7) != 1 && mpow(x, (MOD - 1) / 17) != 1 && mpow(x, (MOD - 1) / 2) != 1;
}

const int MROOT = 13; 
const int MROOTP = 1<<MROOT;
int rts[MROOTP + 10], brev[MROOTP + 10];
void PreCalcRoots(){
  rts[0] = 1; 
  rts[1] = mpow(ROOT, (MOD-1) / MROOTP);
  for (int i = 2; i < MROOTP; i++)
    rts[i] = mmul(rts[i-1], rts[1]);
  for (int i = 0; i < MROOTP; i++) 
    brev[i] = (brev[i>>1]>>1) | ((i&1) << (MROOT-1));
}
inline void butterfly(int &a, int &b, int x){
  int temp = mmul(x, b); b = a;
  madd(a, temp); madd(b, MOD - temp);
}
void fft(vi &a, bool inv){
  int n = __builtin_ctz(sz(a));
  for (int i = 0; i < (1<<n); i++){
    int temp = brev[i] >> (MROOT - n);
    if (temp > i) swap(a[i], a[temp]);
  }
  for (int step = 0; step < n; step++){
    int pos = 0;
    int dlt = (inv ? -1 : 1) * (1 << (MROOT - step - 1));
    for (int i = 0; i < (1<<n); i++){
      if ((i ^ (1<<step)) > i)
        butterfly(a[i], a[i ^ (1<<step)], rts[pos]);
      pos = (pos + dlt) & (MROOTP-1);
    }
  }
  if (inv) {
      int i2n = mpow((1<<n), MOD - 2);
      for (int i = 0; i < (1<<n); i++)
          a[i] = mmul(a[i], i2n);
  }
}

const int BLOCK = 2048;

vector<int> b;
vector< vector<int> > b0, b1;
int sz;

vector<int> geteq(const vector<int>& a, int x) {
    vector<int> res(a.size());
    for (int i = 0; i < (int)a.size(); i++)
        res[i] = a[i] == x;
    return res;
}

vector<int> solve(vector<int> a) {
    assert((int)a.size() == BLOCK);
    reverse(a.begin(), a.end());
    vector<int> a0 = geteq(a, 0);
    vector<int> a1 = geteq(a, 1);
    a0.resize(sz);
    a1.resize(sz);
    fft(a0, false);
    fft(a1, false);
    vector<int> res(a.size() + b.size() + 2 * BLOCK);
    for (int j = 0; j < (int)b0.size(); j++) {
    	vector<int> temp(sz);
        for (int i = 0; i < sz; i++)
            madd(temp[i], mmul(a0[i], b1[j][i]));
        for (int i = 0; i < sz; i++)
            madd(temp[i], mmul(a1[i], b0[j][i]));
        fft(temp, true);
        for (int i = 0; i < (int)temp.size(); i++)
        	madd(res[j * BLOCK + i], temp[i]);
    }
    return vector<int>(res.begin() + a.size() - 1, res.begin() + a.size() + b.size() - 1);
}



int main(){
  #ifdef LOCAL
    assert(freopen(TASKNAME".in","r",stdin));
    assert(freopen(TASKNAME".out","w",stdout));
  #endif
    assert(checkRoot(ROOT));
    PreCalcRoots();

    vector<int> a;
    {
       static char buf[200010];
       gets(buf);
       a = vector<int>(strlen(buf));
       for (int i = 0; buf[i]; i++)
           a[i] = buf[i] - '0';
       gets(buf);
       b = vector<int>(strlen(buf));
       for (int i = 0; buf[i]; i++)
           b[i] = buf[i] - '0';
       while (a.size() % BLOCK != 0)
            a.pb(-1);
       while (b.size() % BLOCK != 0)
            b.pb(-1);
    }
    sz = 1;
    while (sz < 2 * BLOCK) sz *= 2;

    b0 = b1 = vector<vector<int>>(b.size() / BLOCK);
    for (int i = 0; i < (int)b.size() / BLOCK; i++) {
        b0[i] = geteq(vector<int>(b.begin() + i * BLOCK, b.begin() + i * BLOCK + BLOCK), 0);
        b1[i] = geteq(vector<int>(b.begin() + i * BLOCK, b.begin() + i * BLOCK + BLOCK), 1);
        b0[i].resize(sz);
        b1[i].resize(sz);
        fft(b0[i], false);
        fft(b1[i], false);
    }

    TIMESTAMP("FFT b");

    int m;
    scanf("%d",&m);
    vector<int> l(m), pos(m), r(m), ans(m);

    for (int i = 0; i < m; i++){
        int &li = l[i];
        int &ri = r[i];
        int &posi = pos[i];
        int &ansi = ans[i];
        scanf("%d%d%d",&li,&posi,&ri);
        ri += li;
        int lmax = min(ri, (li + BLOCK - 1) / BLOCK * BLOCK);
        while (li != lmax) {
            ansi += a[li] != b[posi];
            li++, posi++;
        }
        int rmin = max(li, ri / BLOCK * BLOCK);
        int epos = posi + ri - li;
        while (ri != rmin) {
            ri--, epos--;
            ansi += a[ri] != b[epos];
        }
    }      
    TIMESTAMP("BORDER");
    for (int i = 0; i < (int)a.size(); i+=BLOCK) {
        if (i / BLOCK % 5 == 0)
            TIMESTAMPf("%d", i);
        vector<int> res = solve(vector<int>(a.begin() + i, a.begin() + i + BLOCK));
        for (int j = 0; j < m; j++) {
            if (l[j] <= i && i + BLOCK <= r[j])
                ans[j] += res[pos[j] + i - l[j]];
        }
    }
    for (int i = 0; i < m; i++)
        printf("%d\n", ans[i]);
    return 0;
}