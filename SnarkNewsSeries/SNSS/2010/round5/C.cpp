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

#define taskname "C"

using namespace std;

typedef long long int64;
typedef long double ld;

ld ans[500];
ld ans1[500];
ld q[500];
int c[500];
int p;

void swap(){
	for (int i=0;i<=p;i++){
		ans[i]=ans1[i];
		ans1[i]=0;
	}
}

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
  int n;
  scanf("%d %d",&n,&p);
  for (int i=0;i<=p;i++)
  	ans[i]=1.0;
  for (int i=0;i<n;i++)
  	cin>>q[i];
  for (int i=0;i<n;i++)
  	cin>>c[i];
  for (int i=0;i<n;i++){
  	int c=::c[i];
		ld q=::q[i];
  	for (int i=0;i<=p;i++){
  		ld prob=0;
  		ld tprob=exp(-q);
  		for (int j=0;j*c<=i;j++){
  			prob+=tprob;
  			tprob*=q/(j+1);
  			ans1[i]=max(ans1[i],ans[i-j*c]*prob);
  		}
  	}
  	swap();
  }
  cout.precision(10);
	cout<<fixed<<ans[p]<<endl;
	return 0;
} 