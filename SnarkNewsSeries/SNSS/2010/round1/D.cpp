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


const int maxn=210000;
int a[maxn];

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i=0;i<n;i++)
		scanf("%d",&a[i]);
	int mpos=0;
	for (int i=1;i<n;i++)
		if (a[mpos]>a[i])
			mpos=i;
	for (int i=0;i<n;i++){
		if (i<=mpos && i+m>mpos && i+m<=n){
			printf("%d %d\n",i+1,i+m);
			return 0;
		}
	}
	printf("1 %d\n",m);
	return 0;
} 