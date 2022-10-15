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

#define taskname "A"

using namespace std;

typedef long long int64;
typedef long double ld;

int g[30];

int gr(int a){
	if (a<0)
		return 0;
	return g[a];
}

bool used[100];

void calc(){
	g[0]=0;
	for (int i=1;i<25;i++){
		memset(used,0,sizeof(used));
		for (int j=0;j<i;j++)
			used[gr(j-1)^gr(i-j-2)]=true;
		for (g[i]=0;used[g[i]];++g[i]);
	}
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
	calc();
	string s;
	int n;
	cin>>n>>s;
	int last=0;
	int grand=0;
	for (int i=0;i<=n;i++){
		if (i==n || s[i]=='X'){
			grand^=gr(i-last);
			last=i+1;
		}
	}
	if (grand!=0){
		printf("Yes\n");
		return 0;
	}
	else {
		printf("No\n");
		return 0;
	}

	return 0;
} 