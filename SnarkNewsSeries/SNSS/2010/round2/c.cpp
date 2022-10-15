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
#include <sstream>

#define mp make_pair
#define pb push_back

#define taskname "C"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int a[50][50];
int g[50][50];
int coef[50][50];
int cost[1<<11];
int res[1<<11];
int c[60];
int n,m,kol,b;


vector<int> nl[20];

void read(vector<int>& v){
	v.clear();
	string s;
	getline(cin,s);
	stringstream str(s);
	int a;
	for (;str>>a;)
		v.pb(a-1);
}


void read(int& c,vector<int>& v){
	v.clear();
	string s;
	getline(cin,s);
	stringstream str(s);
	str>>c;
	int a;
	for (;str>>a;)
		v.pb(a-1);
}


int calc(int mask){
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			g[i][j]=a[i][j];
	for (int i=0;i<kol;i++)
		if (mask & (1<<i)){
			vector<int> line=nl[i];
			int sz=line.size();
			for (int i=0;i<sz-1;i++)
			g[line[i]][line[i+1]]=g[line[i+1]][line[i]]=1;
		}		
	for (int k=0;k<n;k++)
		for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
	int ans=0;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			ans+=g[i][j]*coef[i][j];
	return ans;
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
	scanf("%d %d %d %d\n",&n,&m,&kol,&b);
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			a[i][j]=(1<<25)*(i!=j);
	for (int i=0;i<m;i++){
		vector<int> line;
		read(line);
		int sz=line.size();
		for (int i=0;i<sz-1;i++)
			a[line[i]][line[i+1]]=a[line[i+1]][line[i]]=1;
	}
	for (int i=0;i<kol;i++){
		read(c[i],nl[i]);
		cost[1<<i]=c[i];
	}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			scanf("%d ",&coef[i][j]);
	int minn=(1<<30);
	for (int i=0;i< (1<<kol) ;i++){
	    if (i!=0)
			cost[i]=cost[i&(i-1)]+cost[i&~(i-1)];
		if (cost[i]<=b)
			minn=min(minn,calc(i));
	}
	cout<<calc(0)-minn<<endl;
	return 0;
} 