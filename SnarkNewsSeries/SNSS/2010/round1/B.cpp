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

#define taskname "B"

using namespace std;

typedef long long int64;
typedef long double ld;

string complf[50];
string comprg[50];
char compc[50];
int w[50];
int f;
char t;
int n,m;

void setv(int F,char T){
	if (f!=-1){
		printf("-1\n");
		exit(0);
	}
	f=F;
	t=T;
}

int weight(string& s){
	int res=0;
	for (int i=0;i<s.size();i++)
		res+=w[s[i]-'A'];
	return res;
}

bool check(int a,int b,char c){
	if (c=='<')
		return a<b;
	if (c=='>')
		return a>b;
	return a==b;
}

bool check(){
	for (int i=0;i<n;i++){
		if (!check(weight(complf[i]),weight(comprg[i]),compc[i]))
			return false;
	}
	return true;
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
	cin>>m>>n;
	for (int i=0;i<n;i++)
		cin>>complf[i]>>compc[i]>>comprg[i];
	
	for (int i=0;i<m;i++)
		w[i]=2;
	f=-1;
	for (int i=0;i<m;i++){
		w[i]=1;
		if (check())
			setv(i,'-');
		w[i]=3;
		if (check())
			setv(i,'+');
		w[i]=2;
	}
	cout<<(char)(f+'A')<<t<<endl;
	return 0;
} 