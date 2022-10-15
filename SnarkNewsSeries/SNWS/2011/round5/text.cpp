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

#define taskname "text"

using namespace std;

typedef long long int64;
typedef long double ld;

int a[300];
int b[300];

void gen(string s,int* to){
	for (int i=0;i<260;i++)
		to[i]=0;
	for (int i=0;i<s.size();i++)
		to[int(s[i])]++;
}



int main(){
	#ifndef taskname
		#error taskname is not defined
	#else
		freopen(taskname".in","r",stdin);
		freopen(taskname".out","w",stdout);
	#endif
	string s;
	cin>>s;
	gen(s,a);
	int n;
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>s;
		gen(s,b);
		bool q=true;
		for (int i=0;i<260;i++)
			if (b[i] > a[i])
				q=false;
		if (q)
			cout<<"YES\n";
		else
			cout<<"NO\n";		
	}
	return 0;
} 