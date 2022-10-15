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


int solve(int n,int p){
	ll f,g1,g2;

	if (n == 1)
		return 1% p;
	f = 2%p;
	g2 = 1%p;
	g1 = 2%p;
	
	for (int i = 2; i < n; i++){
		int tg = g1;

		g1 = g1 + (g2*g2)%p - (g1*g1)%p + 2 * g1;
		g1 = (g1 + p)%p;
		g2 = tg;
		f = f * (g2 + 1);
		f %= p;
	}

	return f;
}




int main(){
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif

	while (true){
		int n,p;
		scanf("%d %d",&n,&p);

		if (n == 0 && p == 0)
			return 0;

		cout<<solve(n,p)<<endl;   		
	}
  return 0;
}