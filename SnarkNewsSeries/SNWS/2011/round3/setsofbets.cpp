#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iterator>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "setsofbets"

using namespace std;

typedef long long int64;
typedef long double ld;

ld a[100][100];
int n,m;

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	scanf("%d %d",&m,&n);
	for (int i=0;i<m;i++)
		for (int j=0;j<n;j++)
			cin>>a[j][i];
	for (int i=0;i<n;i++)
		sort(a[i],a[i]+m);
	ld ans=0;
	for (int j=0;j<m;j++){
		ld tmp=1;
		for (int i=0;i<n;i++)
			tmp*=a[i][j];
		ans+=tmp;
	}
	cout.precision(15);
	cout<<fixed<<ans<<endl;

	return 0;
} 