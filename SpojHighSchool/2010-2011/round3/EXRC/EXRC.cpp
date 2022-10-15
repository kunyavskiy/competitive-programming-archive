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
#include <bitset>
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

bitset<500> a;

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	int t;
	cin>>t;
	for (;t;--t){
		int X,n;
		cin>>X>>n;
		for (int i=0;i<500;i++)
			a[i] = 0;
		a.set(0);
		for (int i=0;i<n;i++){
			int tmp;
			cin>>tmp;
			a=a|(a<<tmp);			
		}
		if (X<500 && a.test(X))
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}