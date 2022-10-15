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

int c[10000];
int d[10000];
int ans[10000];
int a,b;
int n,m;

int main()
{
	freopen("holidays.in","r",stdin);
	freopen("holidays2.out","w",stdout);
	scanf("%d %d",&a,&b);
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&c[i]);

	scanf("%d",&m);
	for (int j=0;j<m;j++)
		scanf("%d",&d[j]);
	int e;
	scanf("%d",&e);
	int bestd, best;
	best = bestd = -1;
	for (int i=1;i<=a;i++){
		int y,d,wd;
		y=d=wd=1;
		int ans = 0;
		for (int j=1;j<=e;j++){
			if (wd == i || binary_search(::d,::d+m,d))
				ans++;
			d++;
			if (d==b+2 || (d==b+1 && !binary_search(c,c+n,y))){
				d=1;
				y++;
			}
			wd++;
			if (wd == a+1)
				wd = 1;
		}
		if (ans > best){
			best = ans;
			bestd = i;
		}
	}	
	cout << bestd <<" "<<best << endl;
	return 0;
}