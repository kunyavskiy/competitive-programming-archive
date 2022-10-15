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

int a[110];
int n,m;

bool check(int val){
	int sum=0;
	for (int i=0;i<n;i++)
		sum+=val/a[i] + !!(val%a[i]);
	return sum<=m;
}

int main()
{
  #ifdef LOCAL
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
	cin>>m>>n;
	for (int i=0;i<n;i++)
		cin>>a[i];
	int l=1;
	int r=int(1e+9)+100;
	for (;r-l>1;){
		int mi=(l+r)/2;
		if (check(mi))
			l=mi;
		else
			r=mi;
	}
	cout<<l-m<<endl;
    return 0;
}