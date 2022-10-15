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

#define taskname "schedule"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int start[120];
int end[120];

int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	int n;
	scanf("%d",&n);
	for (int i=0;i<n;i++){
		int h1,m1,h2,m2;
		scanf("%d : %d - %d : %d ",&h1,&m1,&h2,&m2);
		start[i]=h1*60+m1;
		end[i]=h2*60+m2;		
//		cerr<<start[i]<<" "<<end[i]<<endl;
	}
	
	for (int i=0;i<n;i++)
		for (int j=i+1;j<n;j++)
			if (max(start[i],start[j])<min(end[i],end[j])){
//				cerr<<i<<" "<<j<<endl;
				printf("No\n");
				return 0;
			}
	printf("Yes\n");
	return 0;
} 