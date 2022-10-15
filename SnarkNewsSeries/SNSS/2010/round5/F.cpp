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

#define taskname "F"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int a[10];

int main(){
	#ifdef LOCAL
		#ifndef taskname
			#error taskname is not defined
		#else
			freopen(taskname".in","r",stdin);
			freopen(taskname".out","w",stdout);
		#endif
	#endif
	int n;
	cin>>n;
	char c;
	for (int i=0;i<10;i++)
		a[i]=i+1;
	for (int i=0;i<n;i++){
		cin>>c;
		if (c=='W')
			rotate(a+1,a+2,a+10);
		else
			rotate(a,a+1,a+10);
	}
	for (int i=0;i<10;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	return 0;
} 