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

#define taskname "F"

using namespace std;

typedef long long int64;
typedef long double ld;

ld xm[3][2];
ld x[3][2];

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif

	for (int i=0;i<3;i++)
		cin>>xm[i][0]>>xm[i][1];
	for (int j=0;j<2;j++){    
		x[0][j]=+xm[0][j]+xm[1][j]-xm[2][j];
		x[1][j]=+xm[0][j]-xm[1][j]+xm[2][j];
		x[2][j]=-xm[0][j]+xm[1][j]+xm[2][j];
	}
	for (int i=0;i<3;i++){
		cout.precision(10);
		cout<<fixed<<x[i][0]<<" "<<x[i][1]<<endl;
	}	

	return 0;
} 