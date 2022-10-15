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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;


int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ld r,a;
    cin >> r >> a;

    a = a * M_PI/180;
    ld ans = r;

    int cnt = M_PI/a-1;

    ld c = 2*M_PI - cnt *2*a;

    ans += cnt * 2*r*sin(a);

//    cerr << ans << endl;

    c -= 2*a;
    ans += 2*r*sin(c/2);

//    cerr << c << endl;

    cout.precision(15);
    cout << fixed << ans << endl;

    return 0;
}