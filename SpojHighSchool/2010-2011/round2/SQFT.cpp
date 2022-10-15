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

#if ( _WIN32 || __WIN32__ )
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int64 sqrt(int64 x){
	int64 y=int64(sqrt(ld(x)));
	for (;y*y<x;y++);
	for (;y*y>x;y--);
	return y;

}

void solve(int64 n){
	bool q=false;
	for (int64 a=2;(a*a-1)*(a*a-1) <= n;++a){
		if (n%(a*a-1)==0){
			int64 b=n/(a*a-1);
			int64 c=sqrt(b+1);
			if (c*c-1 == b){
				if (!q){
					printf(LLD,n);
					q=true;
				}
				printf("=("LLD"^2-1)*("LLD"^2-1)",a,c);
			}
		}
	}
	if (!q)
		printf("For n="LLD" there is no almost square factorisation.",n);
	printf("\n");
}


int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int t;
	cin>>t;
	for (int i=1;i<=t;i++){
		int64 n;
		cin>>n;
		printf("Case #%d:\n",i);
		solve(n);
	}
    return 0;
}