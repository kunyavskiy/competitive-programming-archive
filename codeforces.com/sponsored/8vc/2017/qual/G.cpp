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
#define sz(x) ((int)((x).size()))

const int MOD = 998244353;
const int ROOT = 3;


int mmul(int a, int b) {
    return (a * 1LL * b) % MOD;
}
void madd(int& a, int b) {
    if ((a += b) >= MOD) a -= MOD;
}

int mpow(int a, int b){
    if (!b) return 1;
    if (b & 1) return (mpow(a, b-1) * 1LL * a) % MOD;
    int temp = mpow(a, b/2);
    return (temp * 1LL * temp) % MOD;
}

bool checkRoot(int x){
    return mpow(x, (MOD - 1) / 7) != 1 && mpow(x, (MOD - 1) / 17) != 1 && mpow(x, (MOD - 1) / 2) != 1;
}

// BEGIN ALGO
const int MROOT = 16;
const int MROOTP = 1<<MROOT;
int rts[MROOTP + 10], brev[MROOTP + 10];
// \emph{Don't forget to call before}
void PreCalcRoots(){
    rts[0] = 1; // ROOT is primary root for MOD
    rts[1] = mpow(ROOT, (MOD-1) / MROOTP);
    for (int i = 2; i < MROOTP; i++)
        rts[i] = mmul(rts[i-1], rts[1]);
    for (int i = 0; i < MROOTP; i++) /*BOXNEXT*/
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
        int pos = 0; /*BOXNEXT*/
        int dlt = (inv ? -1 : 1) * (1 << (MROOT - step - 1));
        for (int i = 0; i < (1<<n); i++){
            if ((i ^ (1<<step)) > i) /*BOXNEXT*/
                butterfly(a[i], a[i ^ (1<<step)], rts[pos]);
            pos = (pos + dlt) & (MROOTP-1);
        }
    }
}
vi multiply(vi a, vi b){
    int rsz = sz(a) + sz(b), rsz2 = 1;
    while (rsz2 < rsz) rsz2 *= 2;
    a.resize(rsz2); b.resize(rsz2);
    fft(a, false); fft(b, false);
    for (int i = 0; i < sz(a); i++)
        a[i] = mmul(a[i], b[i]);
    fft(a, true);
    int in = mpow(sz(a), MOD - 2);
    for (int i = 0; i < sz(a); i++)
        a[i] = mmul(a[i], in);
    return a;
}
// END ALGO

int k;

void poly_mul(vi &a, const vi &b) {
    assert((int)a.size() == (int)b.size());
    for (int i = 0; i < (int)a.size(); i++) {
        mmul(a[i], b[i]);
    }
}

void poly_add(vi &a, const vi& b) {
    assert((int)a.size() == (int)b.size());
    for (int i = 0; i < (int)a.size(); i++) {
        madd(a[i], b[i]);
    }
}

void dump(vi a[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            eprintf("[");
            for (int q = 0; q < k + 1; q++) {
                eprintf("%d ", a[i][j][q]);
            }
            eprintf("] ");
            if (j == 1) {
                eprintf("\n");
            }
        }
    }
    eprintf("\n");
}


void matrix_copy(vi a[2][2], vi b[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            assert((int)b[i][j].size() == k + 1);
            a[i][j] = b[i][j];
        }
    }
}

void matrix_mul(vi a[2][2], vi b[2][2], vi c[2][2]) {
    vi bcopy[2][2];
    vi acopy[2][2];
    matrix_copy(acopy, a);
    matrix_copy(bcopy, b);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            c[i][j] = vector<int>(1 << 16, 0);
            a[i][j].resize(1 << 16);
            b[i][j].resize(1 << 16);
            fft(a[i][j], false);
            fft(b[i][j], false);
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                vi ca = a[i][j];
                poly_mul(ca, b[j][k]);
                poly_add(c[i][k], ca);
            }
        }
    }

    int iv = mpow(c[0][0].size(), MOD - 2);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            fft(c[i][j], true);
            c[i][j].resize(k + 1);
            for (int q = 0; q <= k; q++) {
                c[i][j][q] = mmul(c[i][j][q], iv);
            }
        }
    }

    matrix_copy(a, acopy);
    matrix_copy(b, bcopy);
}

vi temp[2][2];

void matrix_pow(vi a[2][2], int n) {
    vi res[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            res[i][j] = vector<int>(k + 1, 0);
            if (i == j) {
                res[i][j][0] = 1;
            }
        }
    }
    while (n) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                assert((int)res[i][j].size() == k + 1);
                assert((int)a[i][j].size() == k + 1);
            }
        }
        if (n & 1) {
            matrix_mul(res, a, temp);
            matrix_copy(res, temp);
        }
        matrix_mul(a, a, temp);
        matrix_copy(a, temp);
        n >>= 1;
    }
    matrix_copy(a, res);
}

const int MAXN = 257000;



int facs[MAXN];
int ifacs[MAXN];

void PreCalcFacs(){
    facs[0] = ifacs[0] = 1;
    for (int i = 1; i < MAXN; i++){
        facs[i] = (facs[i-1] * 1LL * i) % MOD;
        ifacs[i] = mpow(facs[i], MOD - 2);
    }
}


int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

    PreCalcRoots();
    PreCalcFacs();

    int n;
    scanf("%d%d", &n, &k);
    vi PONE(k + 1);
    PONE[0] = 1;
    vi PX(k + 1);
    PX[1] = 1;
    vi PX1(k + 1);
    PX1[0] = PX1[1] = 1;
    vi PX0(k + 1);

    vi M[2][2];
    M[0][0] = PX1;
    M[0][1] = PX;
    M[1][0] = PONE;
    M[1][1] = PX0;

//    dump(M);

    matrix_pow(M, n);


    dump(M);
    multiply(M[1][0], PX1);
    M[1][0].resize(k + 1);
//    dump(M);
    multiply(M[1][1], PONE);
    M[1][1].resize(k + 1);
//    dump(M);
    poly_add(M[1][0], M[1][1]);
//    dump(M);

    for (int i = 1; i <= k; i++) {
        printf("%d ", M[1][0][i]);
    }

    return 0;
}
