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

#define taskname "e"

#ifdef LOCAL
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif

using namespace std;

typedef long long int64;
typedef long double ld;

int cost[1000];
string name[1000];

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
	for (int i=1;i<n;i++)
		cin>>cost[i];
	for (int i=0;i<n;i++)
		cin>>name[i];
	string s,t;
	cin>>s>>t;
	int num1,num2;
	for (int i=0;i<n;i++){
		if (name[i]==s)
			num1=i;
		if (name[i]==t)
			num2=i;
	}
	if (num1>num2)
		swap(num1,num2);
	int len=num2-num1;
	cout<<cost[len]<<endl;

	return 0;
} 