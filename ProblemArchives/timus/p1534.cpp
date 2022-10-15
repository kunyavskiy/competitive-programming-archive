#ifndef LOCAL
    #pragma comment(linker, "/STACK:33554432")
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory.h>
#include <stack>
#define mp make_pair
#define pb push_back                     
#define setval(a,v) memset(a,v,sizeof(a))



#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
	#define M_PI 3.1415926535897932384626433832795
    #define prev prev_dsfdfgfhgfh
    #define next next_mkdlsmfdgkl
    #define hash hash_mdfdsgdhgfm
    #undef assert
    #define assert(x) if (!(x)) throw 1
    #define sqrt(x) sqrt((double)(x))
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

ll k, l, n, tmp;

int result(int x) {
    if (x > 0) return 3;
    if (x == 0) return 1;
    return 0;
}
int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

    cin >> k >> l >> n;

    tmp = min(k, n - 1);
    ll maxr = 2 * tmp + n - 1 + result(k - tmp - l);

    tmp = min(l, n - 1);
    ll minr = n - 1 - tmp + result(k + tmp - l);
    if (k + tmp - l == 1 && tmp >= 1) minr--;

    cout << maxr << ' ' << minr;
    return 0;
}