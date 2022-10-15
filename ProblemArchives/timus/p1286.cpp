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

ll gcd(ll a,ll b){
	return b?gcd(b,a%b):a;
}

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
    ll p,q;
    ll x1,y1;
    ll x2,y2;
    ll dx,dy;
    cin >> p >> q >> x1 >> y1 >> x2 >> y2;

    dx = abs(x1-x2);
    dy = abs(y1-y2);

    int g = gcd(abs(p-q),2*gcd(p,q));

    const int IT = 10;

    for (int i = -IT; i <= IT; i++)
    	for (int j = -IT; j <= IT; j++)
    		if ((abs(i)&1) == (abs(j)&1))
	    		for (int k = -IT; k <= IT; k++)
    				for (int l = -IT; l <= IT; l++)
			    		if ((abs(k)&1) == (abs(l)&1))
    						if (abs(dx+i*p+k*q)%g == 0 && abs(dy+j*p+l*q)%g == 0){
    							printf("YES\n");
    							return 0;
    						}
    printf("NO\n");
    				

  return 0;
}