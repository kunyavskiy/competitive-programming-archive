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

using namespace std;

typedef long long int64;
typedef long double ld;

/*vector<int> ans;

int64 calc(int a){
	int ans=0;
	int b=1;
	for (;(1<<b)<=a;b++)
		ans+=a/(1<<b);
	return ans;
}

int cat(int a){
	int ans=calc(a*2)-2*calc(a);
	for (int i=a+1;!(i&1);i>>=1)
		ans--;
	//cerr<<a<<" "<<ans<<endl;
	return ans==0;
}    */

int main(){  
/*	for (int i=1;ans.size()<15;i++){
		int c=cat(i);  
		cerr<<i<<" "<<ans.size()<<endl;              
		if (c==1)
			ans.pb(i);	
	}
	for (int i=0;i<15;i++)
		cerr<<ans[i]<<endl;*/
	int k;
	scanf("%d",&k);
	printf(LLD,(1LL<<k)-1);

	return 0;
} 