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

#define taskname "boxes"

using namespace std;

typedef long long int64;
typedef long double ld;

int x[200000];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf("%d",&x[i]);
	sort(x,x+n);
	int ans=0;
	for (int i=0;i<n;){
		int j=i;
		for (;j<n && x[j]==x[i];j++);
		ans=max(ans,j-i);
		i=j;		
	}
	cout<<ans<<endl;
	return 0;
} 