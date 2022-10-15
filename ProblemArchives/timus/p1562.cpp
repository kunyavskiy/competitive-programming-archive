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
    ld a,b;
    int n;
    cin >> a >> b >> n;
    a /= 2, b/=2;
    swap(a,b);

    for (int i = 0; i < n; i++){
        ld l = -a + (2.0*a*i)/n;
        ld r = l + (2.0*a)/n;
        ld ans = (a*a*(r-l) - (r*r*r-l*l*l)/3);
        ans = ans * b/a*b/a * M_PI;
        cout.precision(15);
        cout << fixed << ans << endl;
    }


    return 0;
}