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
#include <cassert>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

#define taskname "sale"

using namespace std;

typedef long long int64;
typedef long double ld;

const int MAXS=1100000;

int d[1000];
int p[1000];
int sum[MAXS];
int best[MAXS];
int bpos[MAXS];
bool bad[MAXS];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	d[0]=p[0]=0;
	n++;
	for (int i=1;i<n;i++){
		int p1,p2;
		scanf("%d %d . %d",&d[i],&p1,&p2); 
		p[i]=p1*100+p2;
	}
	sort(d,d+n);
	sort(p,p+n);
	for (int I=0;I<n-1;I++){
		if (p[I]==p[I+1]){
			for (int i=I;i<n-1;i++){
				p[i]=p[i+1];
				d[i]=d[i+1];
			}
			--n;
		}
	}
	assert(p[n-1]<=MAXS);
	int ptr=0;
	for (int i=0;i<=p[n-1]+10;i++){
		if (ptr!=n-1 && p[ptr+1]==i)
			++ptr;
		sum[i]=(i*1LL*(100-d[ptr])+49)/100;			
	}
	best[p[n-1]]=sum[p[n-1]];
	bpos[p[n-1]]=p[n-1];
	bad[p[n-1]]=false;
	ptr=n-2;
	for (int i=p[n-1]-1;i>=0;--i){
		if (ptr!=0 && p[ptr]==i)
			--ptr;
		if (best[i+1] <= sum[i]){
			best[i]=best[i+1];
			bpos[i]=bpos[i+1];
			bad[i]=(p[ptr+1]<=bpos[i]);
		}
		else{
			best[i]=sum[i];
			bpos[i]=i;
			bad[i]=false;
		}
//		cerr<<i<<endl;
	}
			
	int start=-1;
	bool q=false;
	for (int i=0;i<p[n-1]+10;i++){
		if ((!bad[i]) ^ (start==-1)){
			if (start==-1){
				if (q)
					printf(", ");
				else
					q=true;
				start=i;
			}
			else{
				if (i-1!=start)
					printf("%d.%02d-%d.%02d",start/100,start%100,(i-1)/100,(i-1)%100);
				else
					printf("%d.%02d",start/100,start%100);
				start=-1;
			}
		}		
	}	
	return 0;
} 