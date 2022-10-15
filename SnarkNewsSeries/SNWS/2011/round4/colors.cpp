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

#define taskname "colors"

using namespace std;

typedef long long int64;
typedef long double ld;

bool t[105][105][105];
bool t1[105][105][105];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	if (n%3!=0){
		printf("NO\n");
		return 0;
	}
	int K;
	scanf("%d",&K);
	t[0][0][0]=true;
	n/=3;
	for (int it=0;it<K;it++){
		int r,g,b;
		scanf("%d %d %d",&r,&g,&b);
		for (int i=0;i<=n-r;i++)
			for (int j=0;j<=n-g;j++)
				for (int k=0;k<=n-b;k++)
					t1[i+r][j+g][k+b]|=t[i][j][k];
		for (int i=0;i<=n;i++)
			for (int j=0;j<=n;j++)
				for (int k=0;k<=n;k++)
					t[i][j][k]=t1[i][j][k];	
	}
	if (t[n][n][n])
		cout<<"YES"<<endl;
	else
		cout<<"NO"<<endl;
    return 0;
} 