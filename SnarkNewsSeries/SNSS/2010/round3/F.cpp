#include <iostream>
#include <fstream>
#include <cassert>
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

int x[100],y[100];
char name[100];

int s(int a,int b,int c){
	int x1=x[b]-x[a];
	int x2=x[c]-x[a];
	int y1=y[b]-y[a];
	int y2=y[c]-y[a];
	return abs(x1*y2-x2*y1);
}

bool check(int a,int b,int c,int d){
	int s1=s(a,b,c);
	int s2=s(a,b,d)+s(a,c,d)+s(b,c,d);
	return s1==s2;
}

int main(){        
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++)
		scanf(" %c %d %d",&name[i],&x[i],&y[i]);
	int a,b,c;
	a=b=c=-1;
	int sabc=-10000;
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			for (int k=j+1;k<n;k++)
				{
					bool q=false;
					for (int l=0;l<n;l++)
						if (l!=i && l!=j && l!=k)
							q|=check(i,j,k,l);
					if (!q){
						int sijk=s(i,j,k);
						if (sijk > sabc){
							a=i;b=j;c=k;
							sabc=sijk;
						}
					}
				}
	assert(a!=-1);
	string ans="";
	ans+=name[a];
	ans+=name[b];
	ans+=name[c];
	sort(ans.begin(),ans.end());
	cout<<ans<<endl;
	return 0;
} 