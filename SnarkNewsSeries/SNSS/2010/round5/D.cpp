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

#define taskname "D"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int a[1000][1000];
int n;

void setval(int i,int j){
	a[i][j]=0;
	a[j][n-i-1]=2;
	a[n-i-1][n-j-1]=2;
	a[n-j-1][i]=2;	
/*	for (int i=0;i<n;i++)	
		for (int j=0;j<n;j++)
			cerr<<a[i][j]<<" \n"[j==n-1];
	cerr<<endl;*/
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
	cin>>n;
	int cnt=0;
	for (int i=0;i<n;i++)	
		for (int j=0;j<n;j++)
			a[i][j]=1;
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++){
			char c;
			cin>>c;
			if (c=='0')
				setval(i,j);
		}
	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			if (a[i][j]==1)
				setval(i,j);
	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
			printf("%d",!!a[i][j]);
		printf("\n");
	}
	return 0;
} 