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

#define taskname "oil"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

char s[100][100];

int main(){
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		for (int j=0;j<m;j++)
			scanf(" %c ",&s[i][j]);
	for (int j=0;j<m;j++){
		int cost=0;
		bool q=false;
		for (int i=0;i<n;i++){
			if (s[i][j]=='X'){
				q=true;
				break;
			}
			if (s[i][j]=='S')
				cost++;
			else
				cost+=3;	
		}
		if (!q)
			printf("N ");
		else
			printf("%d ",cost);		
	}
	printf("\n");
	return 0;
} 