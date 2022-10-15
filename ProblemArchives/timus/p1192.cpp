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

#ifndef M_PI
	#define M_PI 3.1415926535897932384626433832795
#endif

#ifdef LOCAL
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ld v,a,k;
    ld ans;
    cin >> v >> a >> k;
    ans = 0;
    a /= 180, a*= M_PI;

    ld e = v*v;

    for (int i = 0; i < 100000; i++){
    	ld y = sqrt(e)*sin(a)*2;
    	ld t = y/10;
    	ans += sqrt(e)*cos(a)*t;
    	e /= k;
    }

    cout.precision(2);
    cout << fixed << ans << endl;
  return 0;
}