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


int gcd(int a,int b){
	a=abs(a);
	b=abs(b);
	while (a && b){
		int t=b;
		b=a%b;
		a=t;
	}
	return a;
}

int main()
{
  #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
  	int n;
	for (int i=1;cin>>n;i++){
		n=((n-1)/4)*2+1+((n-1)%4 != 0);
		int g=gcd(n,n-2);
		printf("Case #%d: %d/%d\n",i,-(n-2+2*(n==1))/g,n/g);
	}
    return 0;
}