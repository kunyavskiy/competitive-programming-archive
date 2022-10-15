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

#define taskname "invest"

using namespace std;

typedef long long int64;
typedef long double ld;

double add[1000][1000];
double t[1000][1000];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n,m,all;
	scanf("%d %d %d",&n,&m,&all);
	for (int i=0;i<n;i++)
		for (int j=0;j<=m;j++)
			scanf("%lf",&add[i][j]);
		
	
	memset(t,0,sizeof(t));
	for (int i=0;i<n;i++){
		for (int j=0;j<=all;j++)
			for (int last=0;last<=m && j+last<=all;last++)
				t[i+1][j+last]=max(t[i+1][j+last],t[i][j]+add[i][last]);
	}
	double best=0;
	for (int i=0;i<=all;i++)
		best=max(best,t[n][i]);
	cout.precision(2);
	cout<<fixed<<best<<endl;
	return 0;
} 