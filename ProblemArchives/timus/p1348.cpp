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
	int x1,y1,x2,y2;
	ld x,y;
	cin >> x1 >> y1 >> x2 >> y2 >> x >> y;
	ld c;
	cin >> c;
                  
    ld d1 = sqrt((x1 - x) * (x1 - x) + (y1 - y) * (y1 - y));
    ld d2 = sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
    ld dl = 1e100;


    if ( (x - x1) * (x2 - x1) + (y - y1) * (y2 - y1) > 1e-9 && (x - x2) * (x1 - x2) + (y - y2) * (y1 - y2) > 1e-9){
        ld a = y2 - y1;
    	ld b = x1 - x2;
    	ld c = - a * x1 - b * y1;

    	dl = abs(a*x + b*y + c)/ sqrt(a*a + b*b);
    }

    ld ans2 = max(d1,d2) - c;
    ld ans1 = min(d1,min(d2,dl)) - c;

    ans1 = max(ans1,(ld)0);
    ans2 = max(ans2,(ld)0);

    cout.precision(15);

    cout << fixed << ans1 <<"\n"<<ans2 << endl;


  return 0;
}