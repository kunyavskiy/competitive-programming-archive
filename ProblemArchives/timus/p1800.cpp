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
#endif

using namespace std;

typedef long long ll;
typedef long double ld;

int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

	ld l,h,w;
	cin >> l >> h >> w;
	if (l>2*h){
		 printf("butter\n");
		 return 0;
	}
	ld tim = sqrt(2.0*(h-l/2)/(9.81*100));
	ld endw = w*tim/60.0;
	endw -= (int)endw;
	if ((endw >= 0 && endw <= 0.25) or (endw >= 0.75 and endw <= 1))
		printf("butter\n");
	else 
		printf("bread\n");

	return 0;
}