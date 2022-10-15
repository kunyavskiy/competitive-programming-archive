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
#define ld long double 
using namespace std;

ld eps=1e-7;
ld inf=1e100;

ld m;

ld calc(ld l,ld sum){
	ld in=m-2*l;
	if (in < -eps)
		return inf;
	if (sum < in+eps)
		return sum+l;
	in-=l;
	if (in < eps)
		return inf;
	int times=int((sum-m+2*l)/(m-3*l));
	while (times*(m-3*l) < (sum-m+2*l)-eps)
		++times;
	while ((times-1)*(m-3*l) > (sum-m+2*l)-eps)
		--times;
	return (2*times+1)*l+sum;
}

bool used[310];
ld d[310];

int x[310],y[310],n;

ld dest(int a,int b){
	return sqrt((x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b]));
}


int main()
{                        
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	cin>>n>>m;
	for (int i=0;i<n;i++)
		cin>>x[i]>>y[i];
	for (int i=0;i<n;i++)
		d[i]=inf;
	d[n-1]=0;
	for (;;){
		int best=-1;
		for (int i=0;i<n;i++)
			if (!used[i])
				if (best == -1 || d[best] > d[i])
					best=i;			
		if (d[best] > inf/2){
			printf("-1\n");
			return 0;
		}
		if (best == 0){
			cout.precision(15);
			cout<<fixed<<d[best]<<endl;
			return 0;
		}
		used[best]=true;
		for (int i=0;i<n;i++)
			if (!used[i])
				d[i]=min(d[i],calc(dest(best,i),d[best]));
			
	}
    return 0;
}