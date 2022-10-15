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

#define taskname "E"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

ld t[100][100];



int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int k,m;
	cin>>k>>m;
	for (int i=0;i<=k;i++)
		t[i][0]=1.0;
	for (int j=1;j<=m;j++)
		t[0][j]=0;
	for (int i=1;i<=k;i++)
		for (int j=1;j<=m;j++)
			t[i][j]=0.7*t[i-1][j]+0.2*t[i-1][j-1]+0.1*t[i][j-1];
	cout.precision(5);
	cout<<fixed<<t[k][m];
	return 0;
} 