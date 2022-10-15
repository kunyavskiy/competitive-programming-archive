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

#define taskname "sysaqua"

using namespace std;

typedef long long int64;
typedef long double ld;

int kol[1000];
int need[1000];

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
		scanf("%d",&kol[i]);
		int can=kol[i];
		for (int j=0;j<i;j++){
			scanf("%d",&need[j]);
			if (need[j])
				can=min(can,kol[j]/need[j]);
		}			
		for (int j=0;j<i;j++)
			kol[j]-=can*need[j];
		kol[i]=can;
	}
	for (int i=0;i<n;i++)
		cout<<kol[i]<<endl;
	return 0;
} 